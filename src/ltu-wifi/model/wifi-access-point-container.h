/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef WIFI_ACCESS_POINT_CONTAINER_H
#define WIFI_ACCESS_POINT_CONTAINER_H

#include "ns3/ptr.h"
#include "wifi-access-point.h"
#include <vector>

namespace ns3 {

class WifiAccessPointContainer {
public:
    WifiAccessPointContainer();
    uint32_t GetN (void) const;
    Ptr<WifiAccessPoint> Get (uint32_t i) const;
    void Add (Ptr<WifiAccessPoint> ap);

protected:
    std::vector<Ptr<WifiAccessPoint> > m_aps; //!< WifiAccessPoint smart pointers
};

}

#endif /* WIFI_ACCESS_POINT_CONTAINER_H */

