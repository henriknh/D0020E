/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef WIFI_ACCESS_POINT_H
#define WIFI_ACCESS_POINT_H

#include "ns3/node-container.h"
#include "wired-connection.h"
#include "wired-connection-container.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"

namespace ns3 {

class WifiAccessPoint : public SimpleRefCount<WifiAccessPoint> {
public:
    WifiAccessPoint(double x, double y, double z, InternetStackHelper stack);
    void ConnectWired(Ptr<WifiAccessPoint> ap);
    void ConnectWired(Ptr<Node>);
    Ipv4InterfaceContainer Install(Ssid *ssid, Ptr<YansWifiChannel> channel, Ipv4AddressHelper *ip);

protected:
    WiredConnectionContainer wiredConnections;
    NodeContainer node;
};
}

#endif /* WIFI_ACCESS_POINT_H */

