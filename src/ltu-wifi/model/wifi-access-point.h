/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef WIFI_ACCESS_POINT_H
#define WIFI_ACCESS_POINT_H

#include <string>
#include "ns3/node-container.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-address.h"

namespace ns3 {

class WifiAccessPoint {
public:
    WifiAccessPoint(double x, double y, double z, std::string ssid, std::string ipAddressWireless, std::string netmaskWireless, std::string ipAddressWired, std::string netmaskWired, std::string ipAddressInternal, std::string netmaskInternal);
    ~WifiAccessPoint();
    void ConnectWired(NodeContainer nodeToConnect);
    NodeContainer GetAllNodes();
    Ipv4Address GetWiredIpAddress(int index);

protected:
    NodeContainer apNode;
    NodeContainer p2pNodes;
    NodeContainer wiredNodes;
    Ipv4AddressHelper wiredAddress;
    Ipv4AddressHelper wirelessAddress;
    Ipv4InterfaceContainer wiredInterfaces;
};

}

#endif /* WIFI_ACCESS_POINT_H */

