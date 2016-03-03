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

//LTU Wall
#include <ns3/ltu-wall-helper.h>

//LTU Wifi
#include <ns3/ltu-wifi.h>






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

  // Instanziate LtuWallHelper 
  LtuWallHelper wallhelper;

  wallhelper.CreateWall(0, 5, 100, 5);

  wallhelper.InstallWalls();

  LtuWifiHelper wifi;
  wifi.SetSsid("GruvNET");//Optional


  Ptr<WifiAccessPoint> ap1 = wifi.CreateAccessPoint(0, 0, 1);
  Ptr<WifiAccessPoint> ap2 = wifi.CreateAccessPoint(100, 0, 1);
  ap1->ConnectWired(ap2);

  NodeContainer wifiClients = wifi.CreateClient(25, 25, 1, 50, 50, 10);
  wifiClients.Add(wifi.CreateClient(100, 25, 1, 50, 50, 5));

  //wifi.InstallAll();//Without building
  wifi.InstallAll(wallhelper.GetLossModel());//With wall


  Address dest;
  std::string protocol;
  dest = InetSocketAddress (wifi.GetWifiClientIP(1), 1025);
  protocol = "ns3::UdpSocketFactory";

  OnOffHelper onoff = OnOffHelper (protocol, dest);
  onoff.SetConstantRate (DataRate ("500kb/s"));
  ApplicationContainer apps = onoff.Install (wifiClients.Get(0));
  apps.Start (Seconds (0.5));
  apps.Stop (Seconds (40.0));

  AnimationInterface anim ("wall-animation.xml");

  Simulator::Stop (Seconds (19.5));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
