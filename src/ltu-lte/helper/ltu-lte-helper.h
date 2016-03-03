/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_LTE_HELPER_H
#define LTU_LTE_HELPER_H

#include "ns3/core-module.h"
#include "ns3/lte-module.h"
#include "ns3/ltu-base-station.h"
#include "ns3/ltu-base-station-container.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/ltu-wall-module.h"

namespace ns3 {

class LtuLteHelper {
public:
    LtuLteHelper();
    ~LtuLteHelper ();//Destructor

    Ptr<LtuBaseStation> CreateENB(double x, double y, double z);
    NodeContainer CreateUE(double x, double y, double z);
    NodeContainer CreateUE(double x, double y, double z, double deltaX, double deltaY);
    NodeContainer CreateUE(double x, double y, double z, double deltaX, double deltaY, double speed);
    void SetInternetNode(Ptr<Node> internetNode);
    void InstallAll(InternetStackHelper internet);
    void InstallAll(InternetStackHelper internet, Ptr<LtuWallContainer> walls);
    Ipv4Address GetUeIP(int index);
    Ipv4Address GetInternetNodeIP();
    Ptr<LtuBaseStation> GetENB(int index);
    Ptr<Node> GetUE(int index);

protected:
    LtuBaseStationContainer eNBs;
    NodeContainer UEs;
    Ptr<Node> remoteHost;
    Ptr<LteHelper> lteHelper;
    Ptr<PointToPointEpcHelper>  epcHelper;
    PointToPointHelper p2ph;
    Ipv4InterfaceContainer ueIPs;
    Ipv4Address internetNodeIP;
    void InternalInstallAll(InternetStackHelper internet, Ptr<LtuWallContainer> walls, bool installWalls);
};

}

#endif /* LTU_LTE_HELPER_H */

