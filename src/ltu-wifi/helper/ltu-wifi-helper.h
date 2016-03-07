/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_WIFI_HELPER_H
#define LTU_WIFI_HELPER_H

#include "ns3/ltu-wifi.h"
#include "ns3/node-container.h"
#include "ns3/wifi-module.h"
#include "ns3/wifi-access-point.h"
#include "ns3/wifi-access-point-container.h"
#include "ns3/propagation-loss-model.h"
#include <string>

namespace ns3 {

/**
    Helper class to easily create WiFi topologies. Create topology first and then call InstallAll to create the Nodes. After the InstallAll-call the topology acts as a normal topology consisting of Nodes.
*/
class LtuWifiHelper {
public:
    LtuWifiHelper();
    ~LtuWifiHelper ();//Destructor

    /**
        Sets the SSID for the network. This call can be left out and a default SSID will be used
    */
    void SetSsid(std::string ssid);

    /**
        Creates an access point at the supplied coordinates, InstallAll must be called when all nodes in the topology has been created.

        \param Position for the access point on the x axis
        \param Position for the access point on the y axis
        \param Position for the access point on the z-axis. If walls are to be used then z must be non-zero.
    */
    Ptr<WifiAccessPoint> CreateAccessPoint(double x, double y, double z);

    /**
        Creates a stationary wireless client at the supplied coordinates, InstallAll must be called when all nodes in the topology has been created.

        \param Position for the client on the x axis
        \param Position for the client on the y axis
        \param Position for the client on the z-axis. If walls are to be used then z must be non-zero.
    */
    NodeContainer CreateClient(double x, double y, double z);

    /**
        Creates a mobile wireless client at the supplied coordinates, InstallAll must be called when all nodes in the topology has been created. The client will move randomly within the boundary specified by deltaX and deltaY where the x and y coordinates are in the middle of the boundary.

        \param Initial position for the client on the x axis
        \param Initial position for the client on the y axis
        \param Initial position for the client on the z-axis. The client does not move by default on the z-axis. If walls are to be used then z must be non-zero.
        \param Width of the boundary
        \param Height of the boundary
    */
    NodeContainer CreateClient(double x, double y, double z, double deltaX, double deltaY);


    /**
        Creates a mobile wireless client at the supplied coordinates, InstallAll must be called when all nodes in the topology has been created. The client will move randomly within the boundary specified by deltaX and deltaY where the x and y coordinates are in the middle of the boundary. The client moves at the speed supplied.

        \param Initial position for the client on the x axis
        \param Initial position for the client on the y axis
        \param Initial position for the client on the z-axis. The client does not move by default on the z-axis. If walls are to be used then z must be non-zero.
        \param Width of the boundary
        \param Height of the boundary
        \param Movement speed of the client
    */
    NodeContainer CreateClient(double x, double y, double z, double deltaX, double deltaY, double speed);

    /**
        Installs the topology in other words creates all nodes, assigns IP-addresses et.c.
    */
    void InstallAll();

    /**
        Installs the topology in other words creates all nodes, assigns IP-addresses et.c. Also adds nodes to building helper and sets the specified propagation loss model for all nodes.

        \param Loss model to install on all nodes in the topology
    */
    void InstallAll(Ptr<PropagationLossModel> propagationLossModel);

    /**
        Returns the access point stored at the supplied index
    */
    Ptr<WifiAccessPoint> GetAP(int index);

    /**
        Return the IP-address of the wireless client on the index supplied. Please note that wired and wireless clients are indexed separately. IP-addresses are only accessible after InstallAll has been called.
    */
    Ipv4Address GetWifiClientIP(int index);

    /**
        Return the IP-address of the wired client on the index supplied. Please note that wired and wireless clients are indexed separately. IP-addresses are only accessible after InstallAll has been called.
    */
    Ipv4Address GetWiredClientIP(int index);

    /**
        Return the IP-address of the access point on the index supplied. IP-addresses are only accessible after InstallAll has been called.
    */
    Ipv4Address GetApIP(int index);

    /**
        Creates a stationary wired client at the specified coordinates. A wired client is a normal Node stored in a NodeContainer. By using this call routing between normal nodes and the wireless topology is ensured.
        
        \param Position for the client on the x axis
        \param Position for the client on the y axis
        \param Position for the client on the z-axis. If walls are to be used then z must be non-zero.
    */
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

