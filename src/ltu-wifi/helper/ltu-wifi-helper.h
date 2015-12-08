/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_WIFI_HELPER_H
#define LTU_WIFI_HELPER_H

#include "ns3/ltu-wifi.h"
#include "ns3/node-container.h"
#include <string>

namespace ns3 {

class LtuWifiHelper {
public:
    ~LtuWifiHelper ();//Destructor

    NodeContainer CreateAccessPoint(std::string ssid, int x, int y, int z);
    NodeContainer CreateClient(int x, int y, int z);
    void ConnectClientToWirelessNetwork(NodeContainer client, std::string ssid);
};

}

#endif /* LTU_WIFI_HELPER_H */

