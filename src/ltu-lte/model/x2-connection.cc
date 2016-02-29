/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "x2-connection.h"
#include "ns3/node-container.h"
#include "ns3/log.h"
#include <string>
#include "ns3/csma-module.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("X2Connection");

X2Connection::X2Connection(Ptr<Node> firstNode, Ptr<Node> secondNode) {
    this->isConnected = false;
    this->nodes.Add(firstNode);
    this->nodes.Add(secondNode);
}

void
X2Connection::Connect() {
    NS_LOG_INFO("Connecting nodes");
}

}
