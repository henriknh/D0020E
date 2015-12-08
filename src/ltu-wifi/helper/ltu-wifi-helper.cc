/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-wifi-helper.h"
#include "ns3/log.h"
namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LtuWifiHelper");

LtuWifiHelper::~LtuWifiHelper()
{
    //Destructor
}

NodeContainer
LtuWifiHelper::CreateAccessPoint(std::string ssid, int x, int y, int z)
{
    //TODO: Fix, below just to be able to compile
    //Create access point and return
    NodeContainer node;
    node.Create (1);
    return node;
}

NodeContainer
LtuWifiHelper::CreateClient(int x, int y, int z)
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

