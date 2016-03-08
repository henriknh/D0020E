/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef WIFI_ACCESS_POINT_H
#define WIFI_ACCESS_POINT_H

#include "ns3/node-container.h"
#include "wired-connection.h"
#include "wired-connection-container.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"

namespace ns3 {

/**
    \brief Represents a container class for a single WiFi Access Point

    This class represents a container for a single WiFi Access Point. It holds references for the nodes, interfaces and connections that makes up an access point.
*/
class WifiAccessPoint : public SimpleRefCount<WifiAccessPoint> {
public:
    /**
        Creates an access point at the provided coordinates. The same internet stack helper must be used throughout the whole topology to ensure correct routing.
    */
    WifiAccessPoint(double x, double y, double z, InternetStackHelper stack);

    /**
        Creates a CSMA connection between the two access points.

        \param Access point to create a connection to from the this object.
    */
    void ConnectWired(Ptr<WifiAccessPoint> ap);

    /**
        Create a CSMA connection between this access point and the supplied node.
        
        \param Node to connect to this access point.
    */
    void ConnectWired(Ptr<Node> nodeToConnect);

    /**
        Create a CSMA connection between this access point and all the nodes in the suppled NodeContainer. Creates a unique connection to each node.

        \param Nodes to connect.
    */
    void ConnectWired(NodeContainer nodesToConnect);

    /**
        Installs all connections and the access point. Please note that the access point is not created until this is called. 

        \param Pointer to SSID to use
        \param Pointer to channel to use
        \param Address helper used to assign IP-addresses. Same helper must be used through the whole topology
    */
    Ipv4InterfaceContainer Install(Ssid *ssid, Ptr<YansWifiChannel> channel, Ipv4AddressHelper *ip);

    /**
        Gets the associated mobility model.
    */
    Ptr<MobilityModel> GetMobilityModel();

    /**
        Gets the node which represents the access point
    */
    NodeContainer GetNode();

protected:
    /**
        Container which holds wired connection to be installed
    */
    WiredConnectionContainer wiredConnections;

    /**
        The actual Node used by the simulator
    */
    NodeContainer node;
};
}

#endif /* WIFI_ACCESS_POINT_H */

