/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-base-station.h"
#include "ltu-base-station-container.h"
#include "ns3/log.h"
#include "ns3/mobility-module.h"
#include "ns3/node-container.h"
#include "ns3/lte-module.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LtuBaseStation");

LtuBaseStation::LtuBaseStation(double x, double y, double z) {
	this->node.Create(1);//Create node
    MobilityHelper mobility;
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install(this->node);
    (this->node.Get(0)->GetObject<ConstantPositionMobilityModel>())->SetPosition(Vector(x, y, z));
}

NodeContainer
LtuBaseStation::GetNode() {
    return this->node;
}

void
LtuBaseStation::Install(Ptr<LteHelper> lteHelper) {
    int numberOfX2Connections = this->x2Connections.GetN();
    for(int i = 0; i < numberOfX2Connections; i++) {
        this->x2Connections.Get(i)->Connect(lteHelper);
    }
}

void
LtuBaseStation::ConnectX2(Ptr<LtuBaseStation> baseStationToConnect)
{
    X2Connection *conn = new X2Connection(this->node.Get(0), baseStationToConnect->node.Get(0));
    Ptr<X2Connection> connPtr = Ptr<X2Connection>(conn);
    this->x2Connections.Add(connPtr);
    baseStationToConnect->x2Connections.Add(connPtr);
}

}
