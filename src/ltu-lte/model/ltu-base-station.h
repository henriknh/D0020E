/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_BASE_STATION_H
#define LTU_BASE_STATION_H

namespace ns3 {

class LtuBaseStation : public SimpleRefCount<LtuBaseStation> {
public:
    LtuBaseStation(double x, double y, double z);

protected:
    NodeContainer node;
};
}

#endif /* LTU_BASE_STATION_H */

