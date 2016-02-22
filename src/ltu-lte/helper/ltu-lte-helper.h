/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_LTE_HELPER_H
#define LTU_LTE_HELPER_H

#include "ns3/core-module.h"
#include "ns3/lte-module.h"
#include "ns3/ltu-base-station.h"
#include "ns3/ltu-base-station-container.h"

namespace ns3 {

class LtuLteHelper {
public:
    LtuLteHelper();
    ~LtuLteHelper ();//Destructor

    Ptr<LtuBaseStation> CreateENB(double x, double y, double z);
    NodeContainer CreateUE(double x, double y, double z);
    NodeContainer CreateUE(double x, double y, double z, double deltaX, double deltaY);
    NodeContainer CreateUE(double x, double y, double z, double deltaX, double deltaY, double speed);
    void ConnectInternetNode(NodeContainer internetNode);
    void InstallAll();

protected:
    LtuBaseStationContainer eNBs;
    NodeContainer UEs;
    NodeContainer internetNodes;
    PointToPointEpcHelper epcHelper;
    LteHelper lteHelper;
};

}

#endif /* LTU_LTE_HELPER_H */

