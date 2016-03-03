/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-lte-helper.h"
#include "ns3/core-module.h"
#include "ns3/lte-module.h"
#include "ns3/ltu-base-station.h"
#include "ns3/ltu-base-station-container.h"
#include "ns3/mobility-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/config-store.h"
#include "ns3/internet-module.h"
#include <string>
#include <sstream>
#include "ns3/ltu-wall-module.h"
#include "ns3/buildings-helper.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("LtuLteHelper");

LtuLteHelper::LtuLteHelper() {
    this->lteHelper = CreateObject<LteHelper> ();
    this->epcHelper = CreateObject<PointToPointEpcHelper> ();//Creates the whole EPC-middleware so we don't have to worry about that
    this->lteHelper->SetEpcHelper (this->epcHelper);

    this->lteHelper->SetHandoverAlgorithmType ("ns3::A2A4RsrqHandoverAlgorithm");
    this->lteHelper->SetHandoverAlgorithmAttribute ("ServingCellThreshold",
                                                    UintegerValue (30));
    this->lteHelper->SetHandoverAlgorithmAttribute ("NeighbourCellOffset",
                                                    UintegerValue (1));

    this->p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
    this->p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
    this->p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.010)));
}
LtuLteHelper::~LtuLteHelper () {}//Destructor

Ptr<LtuBaseStation>
LtuLteHelper::CreateENB(double x, double y, double z) {
    LtuBaseStation *eNB = new LtuBaseStation(x, y, z);
    Ptr<LtuBaseStation> eNB_Ptr;
    eNB_Ptr = Ptr<LtuBaseStation>(eNB);
    this->eNBs.Add(eNB_Ptr);
    return eNB_Ptr;
}

NodeContainer
LtuLteHelper::CreateUE(double x, double y, double z) {
    NodeContainer ue;
    ue.Create(1);

    MobilityHelper mobility;
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install(ue);
    (ue.Get(0)->GetObject<ConstantPositionMobilityModel>())->SetPosition(Vector(x, y, z));

    this->UEs.Add(ue);
    return ue;
}

NodeContainer
LtuLteHelper::CreateUE(double x, double y, double z, double deltaX, double deltaY) {
    return CreateUE(x, y, z, deltaX, deltaY, 1.0);
}

NodeContainer
LtuLteHelper::CreateUE(double x, double y, double z, double deltaX, double deltaY, double speed) {
    NodeContainer ue;
    ue.Create(1);

    MobilityHelper mobility;
    std::stringstream speedStream;
    speedStream << speed;

    mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                               "Mode", StringValue ("Time"),
                               "Time", StringValue ("1s"),
                               "Speed", StringValue ("ns3::ConstantRandomVariable[Constant=" + speedStream.str() + "]"));
    mobility.Install(ue);
    (ue.Get(0)->GetObject<RandomWalk2dMobilityModel>())->SetAttribute("Bounds", RectangleValue (Rectangle (x - (deltaX / 2.0), x + (deltaX / 2.0), y - (deltaY / 2.0), y + (deltaY / 2.0))));
    (ue.Get(0)->GetObject<RandomWalk2dMobilityModel>())->SetAttribute("Position", VectorValue(Vector(x, y, z)));
    
    this->UEs.Add(ue);
    return ue;
}

void
LtuLteHelper::SetInternetNode(Ptr<Node> internetNode) {
    this->remoteHost = internetNode;
}


Ipv4Address
LtuLteHelper::GetUeIP(int index) {
    return this->ueIPs.GetAddress(index);
}

Ipv4Address
LtuLteHelper::GetInternetNodeIP() {
    return this->internetNodeIP;
}

Ptr<LtuBaseStation>
LtuLteHelper::GetENB(int index) {
    return this->eNBs.Get(index);
}

Ptr<Node>
LtuLteHelper::GetUE(int index) {
    return this->UEs.Get(index);
}

void
LtuLteHelper::InstallAll(InternetStackHelper internet) {
    InternalInstallAll(internet, 0, false);
}

void LtuLteHelper::InstallAll(InternetStackHelper internet, Ptr<LtuWallContainer> walls) {
    InternalInstallAll(internet, walls, true);
}

void
LtuLteHelper::InternalInstallAll(InternetStackHelper internet, Ptr<LtuWallContainer> walls, bool installWalls) {
    if(installWalls) {
        this->lteHelper->SetPathlossModelType("ns3::HybridWallPropagationLossModel");
        this->lteHelper->SetPathlossModelAttribute("Walls", PointerValue(walls));
    }

    //Connect external host to PDN Gateway (PGW)
    Ptr<Node> pgw = this->epcHelper->GetPgwNode ();

    NetDeviceContainer internetDevice;
    internetDevice = this->p2ph.Install(pgw, this->remoteHost);

    //Assign IP-addresses
    Ipv4AddressHelper ipv4h;
    ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
    Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevice);
    this->internetNodeIP = internetIpIfaces.GetAddress (1);

    Ipv4StaticRoutingHelper ipv4RoutingHelper;
    Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (this->remoteHost->GetObject<Ipv4> ());
    remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);//Set route from remote host so that all traffic routed to 7.X.X.X goes into LTE-network

    NodeContainer allNodes;
    allNodes.Add(this->UEs);

    NodeContainer eNBNodes;
    int eNBCount = this->eNBs.GetN();
    for(int i = 0; i < eNBCount; i++) {
        eNBNodes.Add(this->eNBs.Get(i)->GetNode());
        allNodes.Add(this->eNBs.Get(i)->GetNode());
        //this->eNBs.Get(i)->Install(this->lteHelper);//Installs X2 interface used for handovers. EPC must be enabled before.
    }

    NetDeviceContainer enbLteDevs = this->lteHelper->InstallEnbDevice(eNBNodes);
    NetDeviceContainer ueLteDevs = this->lteHelper->InstallUeDevice(this->UEs);
    
    //Set IP-addresses for UEs and install IP-stack
    internet.Install (this->UEs);
    this->ueIPs = this->epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueLteDevs));

    //Set up default routes and gateway for all UEs
    int ueCount = this->UEs.GetN();
    for(int i = 0; i < ueCount; i++) {
        Ptr<Node> ueNode = this->UEs.Get(i);
        Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
        ueStaticRouting->SetDefaultRoute (this->epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

    //Let all UEs auto attach using idle mode initial cell procedure
    this->lteHelper->Attach(ueLteDevs);

    for(int i = 0; i < eNBCount; i++) {
        this->eNBs.Get(i)->Install(this->lteHelper);//Installs X2 interface used for handovers. EPC must be enabled before.
    }

    if(installWalls) {
        BuildingsHelper building;
        building.Install(allNodes);
    }

    /*if(lossModel != 0) {
        //Get spectrum channel and call AddPropagationLossModel
        int ueDevsCount = ueLteDevs.GetN();
        int enbDevsCount = enbLteDevs.GetN();
        for(int i = 0; i < ueDevsCount; i++) {
            Ptr<MultiModelSpectrumChannel> channel = Ptr((MultiModelSpectrumChannel)(ueLteDevs.Get(i)->GetChannel()*));
            if(channel != 0) {
                channel->AddPropagationLossModel(lossModel);
            }
        }
    }*/
}

}
