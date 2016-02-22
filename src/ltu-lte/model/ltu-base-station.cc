/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-base-station.h"
#include "ns3/log.h"
#include "ns3/mobility-module.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LtuBaseStation");

LtuBaseStation::LtuBaseStation(double x, double y, double z) {
	this->node.Create(1);//Create node
    MobilityHelper mobility;
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install(this->node);
    (this->node.Get(0)->GetObject<ConstantPositionMobilityModel>())->SetPosition(Vector(x, y, z));
}

}
