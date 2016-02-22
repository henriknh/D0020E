/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-lte-helper.h"
#include "ns3/core-module.h"
#include "ns3/lte-module.h"
#include "ns3/ltu-base-station.h"
#include "ns3/ltu-base-station-container.h"
#include "ns3/mobility-module.h"
#include <string>
#include <sstream>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LtuLteHelper");

LtuLteHelper::LtuLteHelper() {}
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
LtuLteHelper::ConnectInternetNode(NodeContainer internetNode) {
    //TODO
}

void
LtuLteHelper::InstallAll() {
    //TODO
}

}
