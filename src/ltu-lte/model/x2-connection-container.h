/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef X2_CONNECTION_CONTAINER_H
#define X2_CONNECTION_CONTAINER_H

#include "ns3/ptr.h"
#include "x2-connection.h"
#include <vector>

namespace ns3 {

/**
    A container for X2 connections
*/
class X2ConnectionContainer {
public:
    /**
        Instantiates a new container and sets up internal structures
    */
    X2ConnectionContainer();
   
    /**
        Gets the number of connections currently stored in the container
    */
    uint32_t GetN (void) const;

    /**
        Gets the connection stored at the provided index
    */
    Ptr<X2Connection> Get (uint32_t i) const;

    /**
        Adds a new connection to the container
    */
    void Add (Ptr<X2Connection> node);

protected:
    /**
        Internal storage
    */
    std::vector<Ptr<X2Connection> > m_conns; //!< X2 Connection smart pointers
};

}

#endif /* X2_CONNECTION_CONTAINER_H */

