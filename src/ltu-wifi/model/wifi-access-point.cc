/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "wifi-access-point.h"
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/log.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("WifiAccessPoint");
//                 |
//        Rank 0   |   Rank 1
// - --------------|----------------------------
//   Wifi ipAddressWireless
//  
//    *    *
// ...|   | ipAddressinternal
// ...n   n0 -------------- n1  n...
//          point-to-point |    |...
//                                   ================
//                                     ipAddressWired

WifiAccessPoint::WifiAccessPoint(double x, double y, double z, std::string ssid, std::string ipAddressWireless, std::string netmaskWireless, std::string ipAddressWired, std::string netmaskWired, std::string ipAddressInternal, std::string netmaskInternal)
{
    this->p2pNodes.Create(2);//An access point consists of two nodes which is connected internally as a point to point link.
    this->apNode = this->p2pNodes.Get(0);
    this->wiredNodes = this->p2pNodes.Get(1);

    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
    pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

    NetDeviceContainer p2pDevices;
    p2pDevices = pointToPoint.Install (this->p2pNodes);

    CsmaHelper csma;
    csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
    csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

    NetDeviceContainer csmaDevices;
    csmaDevices = csma.Install (this->wiredNodes);

    YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
    YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
    phy.SetChannel (channel.Create ());

    WifiHelper wifi = WifiHelper::Default ();
    wifi.SetRemoteStationManager ("ns3::AarfWifiManager");

    NqosWifiMacHelper mac = NqosWifiMacHelper::Default ();
    mac.SetType ("ns3::ApWifiMac",
                   "Ssid", SsidValue (ssid));

    NetDeviceContainer apDevice;
    apDevice = wifi.Install (phy, mac, this->apNode);

    //Access point can't move thus we assign it to ConstantPositionMobilityModel
    MobilityHelper mobility;
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install (apNode);
    (apNode.Get(0) -> GetObject<ConstantPositionMobilityModel>()) -> SetPosition(Vector(x, y, z));//Set the actual position (x, y, z)

    InternetStackHelper stack;
    stack.Install(this->apNode);
    stack.Install(this->wiredNodes);

    Ipv4AddressHelper address;

    address.SetBase (ipAddressInternal.c_str(), netmaskInternal.c_str());
    Ipv4InterfaceContainer p2pInterfaces;
    p2pInterfaces = address.Assign (p2pDevices);

    this->wiredAddress.SetBase (ipAddressWired.c_str(), netmaskWired.c_str());
    this->wiredInterfaces = wiredAddress.Assign (csmaDevices);

    this->wirelessAddress.SetBase (ipAddressWireless.c_str(), netmaskWireless.c_str());
    this->wirelessAddress.Assign (apDevice);

    //Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
}

WifiAccessPoint::~WifiAccessPoint()
{
    //Maybe do something at destruction??!?!?
}

void
WifiAccessPoint::ConnectWired(NodeContainer nodeToConnect)
{
    this->wiredNodes.Add(nodeToConnect);
    CsmaHelper csma;
    csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
    csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

    NetDeviceContainer csmaDevice;
    csmaDevice = csma.Install (nodeToConnect);

    InternetStackHelper stack;
    stack.Install(nodeToConnect);

    this->wiredInterfaces.Add(this->wiredAddress.Assign (csmaDevice));

    //Ipv4GlobalRoutingHelper::RecomputeRoutingTables ();
}

NodeContainer
WifiAccessPoint::GetAllNodes()
{
    NodeContainer nodes;
    nodes.Add(this->apNode);
    nodes.Add(this->wiredNodes);
    return nodes;
}

Ipv4Address 
WifiAccessPoint::GetWiredIpAddress(int index)
{
    return this->wiredInterfaces.GetAddress(index);
}

}

