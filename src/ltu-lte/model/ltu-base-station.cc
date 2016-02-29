/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-base-station.h"
#include "ltu-base-station-container.h"
#include "ns3/log.h"
#include "ns3/mobility-module.h"
#include "ns3/node-container.h"

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
LtuBaseStation::Install() {
    
}

void
LtuBaseStation::ConnectBaseStationX2(Ptr<LtuBaseStation> baseStationToConnect)
{
    
}

}