/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef WIRED_CONNECTION_H
#define WIRED_CONNECTION_H

#include "ns3/node-container.h"

namespace ns3 {

/**
    Represents a wired connection between two nodes. The class is used to ensure that a single connection is only installed once. This makes is easier to just loop over all nodes and run Install for each node.
*/
class WiredConnection : public SimpleRefCount<WiredConnection> {
public:
    /**
        Instantiates a connection between the two nodes.
    */
    WiredConnection(Ptr<Node> firstNode, Ptr<Node> secondNode);

    /**
        Installs the connection
    */
    void Connect();

protected:
    /**
        Internal storage for nodes
    */
	NodeContainer nodes;
    
    /**
        Used to just install the connection once
    */
	bool isConnected;
};

}

#endif /* WIRED_CONNECTION_H */

