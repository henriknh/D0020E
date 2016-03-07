/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef WIFI_ACCESS_POINT_CONTAINER_H
#define WIFI_ACCESS_POINT_CONTAINER_H

#include "ns3/ptr.h"
#include "wifi-access-point.h"
#include <vector>

namespace ns3 {

/**
    Container for multiple WiFi access points
*/
class WifiAccessPointContainer {
public:
    /**
        Sets up internal structures for the container
    */
    WifiAccessPointContainer();

    /**
        Gets the number of items currently in the container
    */
    uint32_t GetN (void) const;

    /**
        Gets the access point at the specified index
    */
    Ptr<WifiAccessPoint> Get (uint32_t i) const;

    /**
        Adds an access point to the container
    */
    void Add (Ptr<WifiAccessPoint> ap);

protected:
    /**
        Internal storage of access points
    */
    std::vector<Ptr<WifiAccessPoint> > m_aps; //!< WifiAccessPoint smart pointers
};

}

#endif /* WIFI_ACCESS_POINT_CONTAINER_H */

