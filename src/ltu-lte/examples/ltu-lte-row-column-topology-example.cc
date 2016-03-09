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

  //Configure topology here
  int width = 3;		//Number of nodes in x-axis
  int height = 3;		//Number of nodes in y-axis
  int distance = 250;	//Distance between nodes


  int currentIndex = 0;
  double top = -(distance * ((height - 1) / 2.0));
  double left = -(distance * ((width - 1) / 2.0));

  //Set up base stations (Evolved Node B)
  LtuLteHelper lte;
  for(int h = 0; h < height; h++) {
    for(int w = 0; w < width; w++) {
        Ptr<LtuBaseStation> eNB;
        eNB = lte.CreateENB(left + distance * w, top + distance * h, 1);//Create a new base station at the current coordinates
        
        //Connect adjacent base stations to allow handover. Handover can only be done directly to base stations which are connected using X2-interface
        if(w > 0) {
            eNB->ConnectX2(lte.GetENB(currentIndex - 1));//Connect to base station to the left if not left-most column

            //if(h > 0) {
            //    eNB->ConnectX2(lte.GetENB(currentIndex - 1 - width));//Connect diagonal
            //}
        }

        if(h > 0) {
            eNB->ConnectX2(lte.GetENB(currentIndex - width));//Connect to above base station if not top-most row
        }

        currentIndex++;
    }
  }

  //Set up a mobile LTE-client, also known as User Equipment.
  NodeContainer ue;
  ue.Add(lte.CreateUE(0, 0, 1, distance * (height - 1), distance * (width - 1), 50.0));//Mobile client
  //ue.Add(lte.CreateUE(100, 100, 1));//Stationary client

  //Set up "the internet", i.e. a normal node which will act as a remote server
  NodeContainer skyNet;
  skyNet.Create(1);

  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install(skyNet);
  (skyNet.Get(0)->GetObject<ConstantPositionMobilityModel>())->SetPosition(Vector(0, -100, 1));
  
  InternetStackHelper internet;
  internet.Install(skyNet);

  lte.SetInternetNode(skyNet.Get(0));//This connects the internet node to the LTE-network by adding a CSMA-link between the node and the LTE-network's PDN Gateway (PGW)

  //Install the LTE-network. The helper provided must be the same as the one used to install the remote host node.
  lte.InstallAll(internet);

  /*--Topology generation ends here, application setup below--*/

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

  //UdpClientHelper ulClient (lte.GetUeIP(1), ulPort);//Use a UE as server
  UdpClientHelper ulClient (lte.GetInternetNodeIP(), ulPort);//Use remote host as server
  ulClient.SetAttribute ("Interval", TimeValue (MilliSeconds(500)));
  ulClient.SetAttribute ("MaxPackets", UintegerValue(1000000));

  UdpClientHelper client (lte.GetUeIP(0), otherPort);
  client.SetAttribute ("Interval", TimeValue (MilliSeconds(500)));
  client.SetAttribute ("MaxPackets", UintegerValue(1000000));

  //clientApps.Add (dlClient.Install (ue.Get(1)));//Use UE as server
  clientApps.Add (dlClient.Install (skyNet));//Use remote host as server
  clientApps.Add (ulClient.Install (ue.Get(0)));
  clientApps.Add (client.Install (ue.Get(0)));

  serverApps.Start (Seconds (0.01));
  clientApps.Start (Seconds (0.01));


    
  Simulator::Stop (Seconds (300.0));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
