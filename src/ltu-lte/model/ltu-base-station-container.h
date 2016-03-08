/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_BASE_STATION_CONTAINER_H
#define LTU_BASE_STATION_CONTAINER_H

#include "ns3/ptr.h"
#include "ltu-base-station.h"
#include <vector>

namespace ns3 {

/**
    A container class for base stations
*/
class LtuBaseStationContainer {
public:
    /**
        Instantiates a new container and sets up internal structures
    */
    LtuBaseStationContainer();

    /**
        Gets the number of base stations currently stored in the container
    */
    uint32_t GetN (void) const;

    /**
        Gets the base station at the index supplied
    */
    Ptr<LtuBaseStation> Get (uint32_t i) const;

    /**
        Adds a base station to the container
    */
    void Add (Ptr<LtuBaseStation> eNB);

protected:
    /**
        Internal storage
    */
    std::vector<Ptr<LtuBaseStation> > m_eNBs; //!< LtuBaseStation smart pointers
};

}

#endif /* LTU_BASE_STATION_CONTAINER_H */

