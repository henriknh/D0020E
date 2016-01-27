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
    void InstallAll();

protected:
    Ssid ssid;
    NodeContainer clients;
    WifiAccessPointContainer accessPoints;
    InternetStackHelper stack;
};

}

#endif /* LTU_WIFI_HELPER_H */

