/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_TOPOLOGY_HELPER_H
#define LTU_TOPOLOGY_HELPER_H

#include "ns3/ltu-topology.h"
#include "ns3/ltu-wifi-module.h"
#include "ns3/ltu-wall-module.h"


namespace ns3 {

class LtuTopologyHelper{
public:
    void createWifiTopology();

protected:
    LtuWifiHelper wifiHelper;
    LtuWallHelper wallHelper;
};

}

#endif /* LTU_TOPOLOGY_HELPER_H */

