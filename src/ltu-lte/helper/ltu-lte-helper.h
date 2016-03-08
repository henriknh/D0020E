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

/**
    A helper class used to build LTE topologies easily. Ensures routing and handover correctly.
*/
class LtuLteHelper {
public:
    LtuLteHelper();
    ~LtuLteHelper ();//Destructor

    /**
        Creates a base station (Evolved Node B) at the supplied coordinates.
    
        \param X coordinate of the base station
        \param Y coordinate of the base station
        \param Z coordinate of the base station, if walls are used then Z must be non-zero
    */
    Ptr<LtuBaseStation> CreateENB(double x, double y, double z);

    /**
        Creates a stationary client (user equipment) at the supplied coordinates
    
        \param X coordinate of the client
        \param Y coordinate of the client
        \param Z coordinate of the client, if walls are used then Z must be non-zero
    */
    NodeContainer CreateUE(double x, double y, double z);

    /**
        Creates a mobile client (user equipment) at the supplied coordinates which moves randomly within the boundary. Initial coordinates represents the middle of the boundary.
    
        \param X coordinate for the initial position of the client
        \param Y coordinate for the initial position of the client
        \param Z coordinate for the initial position of the client, if walls are used then Z must be non-zero
        \param Width of the boundary box
        \param Height of the boundary box
    */
    NodeContainer CreateUE(double x, double y, double z, double deltaX, double deltaY);

    /**
        Creates a mobile client (user equipment) at the supplied coordinates which moves randomly within the boundary at the supplied speed. Initial coordinates represents the middle of the boundary.
    
        \param X coordinate for the initial position of the client
        \param Y coordinate for the initial position of the client
        \param Z coordinate for the initial position of the client, if walls are used then Z must be non-zero
        \param Width of the boundary box
        \param Height of the boundary box
        \param Speed of the client
    */
    NodeContainer CreateUE(double x, double y, double z, double deltaX, double deltaY, double speed);

    /**
        Sets the first node of the internet which connects to the PGW (PDN Gateway)
    */
    void SetInternetNode(Ptr<Node> internetNode);

    /**
        Installs all nodes, sets up IP-addresses et.c.

        \param Helper to use when installing nodes. Must be the same helper object used as on the other non-LTE network nodes, e.g. the internet node.
    */
    void InstallAll(InternetStackHelper internet);

    /**
        Installs all nodes, sets up IP-addresses et.c.. Assigns a propagation loss model using the supplied walls.

        \param Helper to use when installing nodes. Must be the same helper object used as on the other non-LTE network nodes, e.g. the internet node.
        \param Container of walls used as restrictions of signal propagation
    */
    void InstallAll(InternetStackHelper internet, Ptr<LtuWallContainer> walls);

    /**
        Gets the IP-address of the client (User Equipment) stored at the supplied index. IP-addresses are only available after InstallAll has been called
    */
    Ipv4Address GetUeIP(int index);

    /**
        Gets the IP-address of the internet node. IP-addresses are only available after InstallAll has been called
    */
    Ipv4Address GetInternetNodeIP();

    /**
        Gets base station (Evolved Node B) stored at the supplied index
    */
    Ptr<LtuBaseStation> GetENB(int index);

    /**
        Gets the client (User Equipment) stored at the supplied index
    */
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

