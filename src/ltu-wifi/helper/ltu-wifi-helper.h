/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_WIFI_HELPER_H
#define LTU_WIFI_HELPER_H

#include "ns3/ltu-wifi.h"
#include "ns3/node-container.h"
#include "ns3/wifi-module.h"
#include "ns3/wifi-access-point.h"
#include "ns3/wifi-access-point-container.h"
#include <string>

namespace ns3 {

class LtuWifiHelper {
public:
    LtuWifiHelper();
    ~LtuWifiHelper ();//Destructor

    void SetSsid(std::string ssid);
    Ptr<WifiAccessPoint> CreateAccessPoint(double x, double y, double z);
    NodeContainer CreateClient(double x, double y, double z);
    NodeContainer CreateClient(double x, double y, double z, double deltaX, double deltaY);
    NodeContainer CreateClient(double x, double y, double z, double deltaX, double deltaY, double speed);
    void InstallAll();
    Ptr<WifiAccessPoint> GetAP(int index);
    Ipv4Address GetWifiClientIP(int index);
    Ipv4Address GetWiredClientIP(int index);
    Ipv4Address GetApIP(int index);
    NodeContainer CreateWiredClient(double x, double y, double z);

protected:
    Ssid ssid;
    NodeContainer clients;
    NodeContainer wifiClients;
    NodeContainer wiredClients;
    WifiAccessPointContainer accessPoints;
    InternetStackHelper stack;
    Ipv4InterfaceContainer wifiClientIps;
    Ipv4InterfaceContainer wiredClientIps;
    Ipv4InterfaceContainer accessPointIps;
};

}

#endif /* LTU_WIFI_HELPER_H */

