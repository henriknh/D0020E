/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef WIRED_CONNECTION_CONTAINER_H
#define WIRED_CONNECTION_CONTAINER_H

#include "ns3/ptr.h"
#include "wired-connection.h"
#include <vector>

namespace ns3 {

class WiredConnectionContainer {
public:
    WiredConnectionContainer();
    uint32_t GetN (void) const;
    Ptr<WiredConnection> Get (uint32_t i) const;
    void Add (Ptr<WiredConnection> node);

protected:
    std::vector<Ptr<WiredConnection> > m_conns; //!< Wired Connection smart pointers
};

}

#endif /* WIRED_CONNECTION_CONTAINER_H */

