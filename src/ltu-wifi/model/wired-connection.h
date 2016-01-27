/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef WIRED_CONNECTION_H
#define WIRED_CONNECTION_H

#include "ns3/node-container.h"

namespace ns3 {

class WiredConnection : public SimpleRefCount<WiredConnection> {
public:
    WiredConnection(Ptr<Node> firstNode, Ptr<Node> secondNode);
    void Connect();//TODO: Probably needs some arguments

protected:
	NodeContainer nodes;
	bool isConnected;
};

}

#endif /* WIRED_CONNECTION_H */

