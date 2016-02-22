/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_BASE_STATION_CONTAINER_H
#define LTU_BASE_STATION_CONTAINER_H

#include "ns3/ptr.h"
#include "ltu-base-station.h"
#include <vector>

namespace ns3 {

class LtuBaseStationContainer {
public:
    LtuBaseStationContainer();
    uint32_t GetN (void) const;
    Ptr<LtuBaseStation> Get (uint32_t i) const;
    void Add (Ptr<LtuBaseStation> eNB);

protected:
    std::vector<Ptr<LtuBaseStation> > m_eNBs; //!< LtuBaseStation smart pointers
};

}

#endif /* LTU_BASE_STATION_CONTAINER_H */

