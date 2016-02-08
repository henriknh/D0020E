#include "ns3/ltu-topology-helper.h"
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/ltu-wifi-module.h"
#include "ns3/netanim-module.h"
#include <iostream>

using namespace ns3;

int
main (int argc, char *argv[])
{
	
	LtuTopologyHelper mineTopology;
	mineTopology.createWifiTopology();
	AnimationInterface anim ("LtuTopology-animation.xml");

	Simulator::Stop (Seconds (300.0));
	Simulator::Run ();
	Simulator::Destroy ();
}
