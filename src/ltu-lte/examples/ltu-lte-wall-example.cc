/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/ltu-lte-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-helper.h"
#include "ns3/epc-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/config-store.h"

using namespace ns3;


int 
main (int argc, char *argv[])
{
  bool verbose = true;
  CommandLine cmd;
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);

  cmd.Parse (argc,argv);

  if (verbose)
    {
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }

  /*--Topology generation starts here--*/

  LtuLteHelper lte;//Helper used for nodes, connectivity and topology
  LtuWallHelper walls;//Helper used to create and store walls

  //Add a wall at x=0 and from y=-100 to y=100
  walls.CreateWall(0, -100, 0, 100);

  //Create a base station on the left side of the wall
  lte.CreateENB(-50, 0, 1);

  //Create a stationary client (User Equipment) on the right side of the wall (can be moved to the right side of the wall in pyViz using mousewheel)
  NodeContainer ue;
  ue = lte.CreateUE(25, 0, 1);
 
  //Add a remote host used as a server to send data continously to the client
  NodeContainer skyNet;
  skyNet.Create(1);

  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install(skyNet);
  (skyNet.Get(0)->GetObject<ConstantPositionMobilityModel>())->SetPosition(Vector(0, -100, 1));
  
  InternetStackHelper internet;
  internet.Install(skyNet);    

  lte.SetInternetNode(skyNet.Get(0));//Connect remote host to the LTE-network
  lte.InstallAll(internet, walls.GetWallsContainer());//Install the LTE-network with the supplied walls

  /*--Topology generation ends here, application set up below--*/

  uint16_t dlPort = 1234;
  uint16_t ulPort = 2000;
  uint16_t otherPort = 3000;
  ApplicationContainer clientApps;
  ApplicationContainer serverApps;

  PacketSinkHelper dlPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), dlPort));
  PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), ulPort));
  PacketSinkHelper packetSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), otherPort));
  serverApps.Add (dlPacketSinkHelper.Install (ue.Get(0)));
  serverApps.Add (ulPacketSinkHelper.Install (skyNet));
  serverApps.Add (packetSinkHelper.Install (ue.Get(0)));

  UdpClientHelper dlClient (lte.GetUeIP(0), dlPort);
  dlClient.SetAttribute ("Interval", TimeValue (MilliSeconds(500)));
  dlClient.SetAttribute ("MaxPackets", UintegerValue(1000000));

  UdpClientHelper ulClient (lte.GetInternetNodeIP(), ulPort);
  ulClient.SetAttribute ("Interval", TimeValue (MilliSeconds(500)));
  ulClient.SetAttribute ("MaxPackets", UintegerValue(1000000));

  UdpClientHelper client (lte.GetUeIP(0), otherPort);
  client.SetAttribute ("Interval", TimeValue (MilliSeconds(500)));
  client.SetAttribute ("MaxPackets", UintegerValue(1000000));

  clientApps.Add (dlClient.Install (skyNet));
  clientApps.Add (ulClient.Install (ue.Get(0)));
  clientApps.Add (client.Install (ue.Get(0)));

  serverApps.Start (Seconds (0.01));
  clientApps.Start (Seconds (0.01));


    
  Simulator::Stop (Seconds (300.0));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
