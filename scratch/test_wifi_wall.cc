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

//Wall
#include <ns3/hybrid-wall-propagation-loss-model.h>
#include <ns3/buildings-helper.h>




#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store.h"
#include <ns3/buildings-helper.h>
#include <ns3/hybrid-buildings-propagation-loss-model.h>
#include <ns3/hybrid-wall-propagation-loss-model.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/ltu-wifi.h>

#include <iomanip>
#include <string>
#include <vector>





using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("LeifiTestar");

int 
main (int argc, char *argv[])
{
  bool verbose = true;
  CommandLine cmd;
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);

  cmd.Parse (argc,argv);

  if (verbose)
    {
      LogComponentEnable("LeifiTestar", LOG_LEVEL_INFO);
      LogComponentEnable("WifiAccessPoint", LOG_LEVEL_INFO);
      LogComponentEnable("WiredConnection", LOG_LEVEL_INFO);
      LogComponentEnable("WiredConnectionContainer", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }


  // CREATE MUTTER WOOPING BUKLDING 
  Ptr<Building> building1 = CreateObject<Building> ();
  building1->SetBoundaries (Box (-100, 100, 5, 15, -200.0, 200));
  building1->SetBuildingType (Building::Residential);
  building1->SetExtWallsType (Building::ConcreteWithoutWindows);
  building1->SetNFloors (1); //1 floor per every 4th height

  // PROGATATION WALL LOSS MODEL LELELE
  Ptr<MobilityBuildingInfo> mbuildingInfo = CreateObject<MobilityBuildingInfo> ();
  Ptr<HybridWallPropagationLossModel> lossModel = CreateObject<HybridWallPropagationLossModel>();
  lossModel->SetAttribute ("ShadowSigmaOutdoor", DoubleValue (7.0));
  lossModel->SetAttribute ("ShadowSigmaIndoor", DoubleValue (10.0));
  lossModel->SetAttribute ("ShadowSigmaExtWalls", DoubleValue (5.0));
  
  lossModel->SetAttribute ("Los2NlosThr", DoubleValue (1.0));




  LtuWifiHelper wifi;
  wifi.SetSsid("GruvNET");//Optional


  Ptr<WifiAccessPoint> ap1 = wifi.CreateAccessPoint(0, 0, 1);
  Ptr<WifiAccessPoint> ap2 = wifi.CreateAccessPoint(100, 0, 1);
  ap1->ConnectWired(ap2);

  NodeContainer wifiClients = wifi.CreateClient(25, 25, 1, 50, 50, 10);
  wifiClients.Add(wifi.CreateClient(100, 25, 1, 50, 50, 5));

  //wifi.InstallAll();//Without building
  wifi.InstallAll(lossModel);//With building

  Ptr<MobilityModel> mm;
  int containerSize = wifiClients.GetN();
  for(int i = 0; i < containerSize; i++) {
        mm = wifiClients.Get(i)->GetObject<MobilityModel>();
        //mm->AggregateObject(mbuildingInfo);
        //BuildingsHelper::MakeConsistent(mm);
  }

  /*mm = ap1->GetMobilityModel();
  mm->AggregateObject (mbuildingInfo);
  BuildingsHelper::MakeConsistent(mm);
  mm = ap2->GetMobilityModel();
  mm->AggregateObject (mbuildingInfo);
  BuildingsHelper::MakeConsistent(mm);*/
  
  NodeContainer allNodes;
  allNodes.Add(wifiClients);
  allNodes.Add(ap1->GetNode());
  allNodes.Add(ap2->GetNode());
  
  BuildingsHelper building;
  building.Install(allNodes);


  Address dest;
  std::string protocol;
  dest = InetSocketAddress (wifi.GetWifiClientIP(1), 1025);
  protocol = "ns3::UdpSocketFactory";

  OnOffHelper onoff = OnOffHelper (protocol, dest);
  onoff.SetConstantRate (DataRate ("500kb/s"));
  ApplicationContainer apps = onoff.Install (wifiClients.Get(0));
  apps.Start (Seconds (0.5));
  //apps.Stop (Seconds (300.0));

  AnimationInterface anim ("wall-animation.xml");

  //Simulator::Stop (Seconds (300.0));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
