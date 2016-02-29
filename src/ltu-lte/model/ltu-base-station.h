/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_BASE_STATION_H
#define LTU_BASE_STATION_H


#include "ns3/node-container.h"
#include "x2-connection-container.h"

namespace ns3 {

class LtuBaseStation : public SimpleRefCount<LtuBaseStation> {
public:
    LtuBaseStation(double x, double y, double z);
    NodeContainer GetNode();
    void ConnectBaseStationX2(Ptr<LtuBaseStation> baseStationToConnect);
    void Install();

protected:
    NodeContainer node;
    X2ConnectionContainer x2Connections;
};
}

#endif /* LTU_BASE_STATION_H */

