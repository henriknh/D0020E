/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef X2_CONNECTION_H
#define X2_CONNECTION_H

#include "ns3/node-container.h"
#include "ns3/lte-module.h"

namespace ns3 {

/**
    Class which represents a connection between two base stations using the X2-interface used for LTE handover. Ensures that the connection is only installed once.
*/
class X2Connection : public SimpleRefCount<X2Connection> {
public:
    /**
        Instantiates a new connection between the two supplied nodes
    */
    X2Connection(Ptr<Node> firstNode, Ptr<Node> secondNode);

    /**
        Installs the connection
    */
    void Connect(Ptr<LteHelper> lteHelper);

protected:
	NodeContainer nodes;
	bool isConnected;
};

}

#endif /* X2_CONNECTION_H */

