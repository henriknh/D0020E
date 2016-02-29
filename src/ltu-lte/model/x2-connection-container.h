/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef X2_CONNECTION_CONTAINER_H
#define X2_CONNECTION_CONTAINER_H

#include "ns3/ptr.h"
#include "x2-connection.h"
#include <vector>

namespace ns3 {

class X2ConnectionContainer {
public:
    X2ConnectionContainer();
    uint32_t GetN (void) const;
    Ptr<X2Connection> Get (uint32_t i) const;
    void Add (Ptr<X2Connection> node);

protected:
    std::vector<Ptr<X2Connection> > m_conns; //!< X2 Connection smart pointers
};

}

#endif /* X2_CONNECTION_CONTAINER_H */

