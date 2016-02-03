/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-wifi-helper.h"
#include "ns3/wifi-access-point.h"
#include "ns3/wifi-access-point-container.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/wifi-module.h"
#include "ns3/log.h"
#include "ns3/propagation-loss-model.h"
#include <string>
#include <sstream>

#define DEFAULT_WIFI_SSID "DefaultWifi"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LtuWifiHelper");

LtuWifiHelper::LtuWifiHelper() {
    this->ssid = Ssid(DEFAULT_WIFI_SSID);
}

LtuWifiHelper::~LtuWifiHelper () {
}

void
LtuWifiHelper::SetSsid(std::string ssid) {
    this->ssid = Ssid(ssid);
}

Ptr<WifiAccessPoint>
LtuWifiHelper::CreateAccessPoint(double x, double y, double z) {
    WifiAccessPoint *ap = new WifiAccessPoint(x, y, z, this->stack);
    Ptr<WifiAccessPoint> apPtr;
    apPtr = Ptr<WifiAccessPoint>(ap);
    this->accessPoints.Add(apPtr);
    return apPtr;
}

NodeContainer
LtuWifiHelper::CreateClient(double x, double y, double z) {
    NodeContainer client;
    client.Create(1);

    this->stack.Install(client);
    MobilityHelper mobility;
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install(client);
    (client.Get(0)->GetObject<ConstantPositionMobilityModel>())->SetPosition(Vector(x, y, z));

    this->clients.Add(client);
    return client;
}

NodeContainer
LtuWifiHelper::CreateClient(double x, double y, double z, double deltaX, double deltaY) {
    return CreateClient(x, y, z, deltaX, deltaY, 1.0);
}

NodeContainer
LtuWifiHelper::CreateClient(double x, double y, double z, double deltaX, double deltaY, double speed) {
    NodeContainer client;
    client.Create(1);

    this->stack.Install(client);
    MobilityHelper mobility;
    /*mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                   "MinX", DoubleValue (x),
                                   "MinY", DoubleValue (y),
                                   "MinZ", DoubleValue (z),
                                   "DeltaX", DoubleValue (1.0),
                                   "DeltaY", DoubleValue (1.0),
                                   "GridWidth", UintegerValue (1),
                                   "LayoutType", StringValue ("RowFirst"));*/

    std::stringstream speedStream;
    speedStream << speed;

    mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                               "Mode", StringValue ("Time"),
                               "Time", StringValue ("1s"),
                               "Speed", StringValue ("ns3::ConstantRandomVariable[Constant=" + speedStream.str() + "]"));
    mobility.Install(client);
    (client.Get(0)->GetObject<RandomWalk2dMobilityModel>())->SetAttribute("Bounds", RectangleValue (Rectangle (x - (deltaX / 2.0), x + (deltaX / 2.0), y - (deltaY / 2.0), y + (deltaY / 2.0))));
    (client.Get(0)->GetObject<RandomWalk2dMobilityModel>())->SetAttribute("Position", VectorValue(Vector(x, y, z)));
    
    this->clients.Add(client);
    this->wifiClients.Add(client);
    return client;
}

void
LtuWifiHelper::InstallAll() {
    this->InstallAll(0);
}

void 
LtuWifiHelper::InstallAll(Ptr<PropagationLossModel> propagationLossModel) {
    //Set upp helpers
    Ipv4AddressHelper *ip = new Ipv4AddressHelper();
    ip->SetBase("192.168.0.0", "255.255.255.0");//TODO: Create a setter

    YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
    Ptr<YansWifiChannel> channel = wifiChannel.Create();
    if(propagationLossModel != 0) {
        channel->SetPropagationLossModel(propagationLossModel);
    }

    //Install all access points
    int numberOfAccessPoints = this->accessPoints.GetN();
    for(int i = 0; i < numberOfAccessPoints; i++) 
    {
        this->accessPointIps.Add(this->accessPoints.Get(i)->Install(&this->ssid, channel, ip));
    }

    //Install all wifi clients
    int numberOfWifiClients = this->wifiClients.GetN();
    for(int i = 0; i < numberOfWifiClients; i++) 
    {
        YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
        wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO); 
        WifiHelper wifi = WifiHelper::Default ();
        NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
        wifiPhy.SetChannel (channel);
        wifiMac.SetType ("ns3::StaWifiMac",
                         "Ssid", SsidValue (this->ssid),
                         "ActiveProbing", BooleanValue (true));
        NetDeviceContainer stationDevice;
        stationDevice = wifi.Install (wifiPhy, wifiMac, this->wifiClients.Get(i));
        this->wifiClientIps.Add(ip->Assign (stationDevice));
    }

    //Install all wired clients
    int numberOfWiredClients = this->wiredClients.GetN();
    for(int i = 0; i < numberOfWiredClients; i++) 
    {
        //Since wired connections has already been installed by AP we only need to assign an IP
        NetDeviceContainer wiredDevice;
        wiredDevice.Add(this->wiredClients.Get(i)->GetDevice(1));//Loopback is 0, thus CSMA must be 1
        this->wiredClientIps.Add(ip->Assign (wiredDevice));
    }

}

NodeContainer
LtuWifiHelper::CreateWiredClient(double x, double y, double z) {
    NodeContainer client;
    client.Create(1);

    this->stack.Install(client);
    MobilityHelper mobility;
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install(client);
    (client.Get(0)->GetObject<ConstantPositionMobilityModel>())->SetPosition(Vector(x, y, z));

    this->clients.Add(client);
    this->wiredClients.Add(client);
    return client;
}

Ptr<WifiAccessPoint>
LtuWifiHelper::GetAP(int index) {
    return this->accessPoints.Get(index);
}

Ipv4Address
LtuWifiHelper::GetApIP(int index) {
    return this->accessPointIps.GetAddress(index);
}

Ipv4Address
LtuWifiHelper::GetWifiClientIP(int index) {
    return this->wifiClientIps.GetAddress(index);
}

Ipv4Address
LtuWifiHelper::GetWiredClientIP(int index) {
    return this->wiredClientIps.GetAddress(index);
}

}

