/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef X2_CONNECTION_H
#define X2_CONNECTION_H

#include "ns3/node-container.h"

namespace ns3 {

class X2Connection : public SimpleRefCount<X2Connection> {
public:
    X2Connection(Ptr<Node> firstNode, Ptr<Node> secondNode);
    void Connect();//TODO: Probably needs some arguments

protected:
	NodeContainer nodes;
	bool isConnected;
};

}

#endif /* X2_CONNECTION_H */

