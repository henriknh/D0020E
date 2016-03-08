/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_BASE_STATION_H
#define LTU_BASE_STATION_H


#include "ns3/node-container.h"
#include "ns3/lte-module.h"
#include "x2-connection-container.h"

namespace ns3 {

/**
    Represents a wrapper for an evolved node B (LTE Base Station).
*/
class LtuBaseStation : public SimpleRefCount<LtuBaseStation> {
public:
    /**
        Creates internal structures which represents a base station
    */
    LtuBaseStation(double x, double y, double z);

    /**
        Gets the internal node used for the base station
    */
    NodeContainer GetNode();

    /**
        Creates a connection using the X2-interface between two base station. X2 allows for handover between the base stations.
    */
    void ConnectX2(Ptr<LtuBaseStation> baseStationToConnect);

    /**
        Installs the interface, connection et.c.
    */
    void Install(Ptr<LteHelper> lteHelper);

protected:
    NodeContainer node;
    X2ConnectionContainer x2Connections;
};
}

#endif /* LTU_BASE_STATION_H */

