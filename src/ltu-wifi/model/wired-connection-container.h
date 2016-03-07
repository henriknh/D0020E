/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef WIRED_CONNECTION_CONTAINER_H
#define WIRED_CONNECTION_CONTAINER_H

#include "ns3/ptr.h"
#include "wired-connection.h"
#include <vector>

namespace ns3 {

/**
    Container which stores wired connections to be installed
*/
class WiredConnectionContainer {
public:
    /**
        Instantiates a new container with all the internal structure set up accordingly
    */
    WiredConnectionContainer();

    /**
        Gets the number of connections stored in the container
    */
    uint32_t GetN (void) const;

    /**
        Gets the connection at the supplied index
    */
    Ptr<WiredConnection> Get (uint32_t i) const;

    /**
        Adds a wired connection to the container, since smart pointers are used the object won't be removed unless the container is removed as well
    */
    void Add (Ptr<WiredConnection> node);

protected:
    /**
        Internal storage
    */
    std::vector<Ptr<WiredConnection> > m_conns; //!< Wired Connection smart pointers
};

}

#endif /* WIRED_CONNECTION_CONTAINER_H */

