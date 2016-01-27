/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "wired-connection.h"
#include "ns3/node-container.h"
#include "ns3/log.h"
#include <string>
#include "ns3/csma-module.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("WiredConnection");

WiredConnection::WiredConnection(Ptr<Node> firstNode, Ptr<Node> secondNode) {
    this->isConnected = false;
    this->nodes.Add(firstNode);
    this->nodes.Add(secondNode);
}

void
WiredConnection::Connect() {
    if(this->isConnected == false) {
        NS_LOG_INFO("Connecting nodes");

        CsmaHelper csma;
        csma.Install(this->nodes);

        this->isConnected = true;
    }
    else
    {
        NS_LOG_INFO("Already connected!");
    }
}

}
