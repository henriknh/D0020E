/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-wifi-helper.h"
#include "ns3/wifi-access-point.h"
#include "ns3/mobility-module.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LtuWifiHelper");

LtuWifiHelper::~LtuWifiHelper()
{
    //Destructor
}

NodeContainer
LtuWifiHelper::CreateAccessPoint(std::string ssid, double x, double y, double z)
{
    //Create access point and return
    NodeContainer apNode;
    apNode.Create (1);

    //Access point can't move thus we assign it to ConstantPositionMobilityModel
    MobilityHelper mobility;
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install (apNode);
    (apNode.Get(0) -> GetObject<ConstantPositionMobilityModel>()) -> SetPosition(Vector(x, y, z));//Set the actual position (x, y, z)

    //Set ssid and stuff
    
    return apNode;
}

NodeContainer
LtuWifiHelper::CreateClient(double x, double y, double z)
{
    //TODO: Fix, below just to be able to compile
    //Create wifi client and return
    NodeContainer node;
    node.Create (1);
    return node;
}

void
LtuWifiHelper::ConnectClientToWirelessNetwork(NodeContainer client, std::string ssid)
{
    //Connect the supplied client (node) to the provided SSID.
}

}

