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
#include "ns3/wifi-access-point.h"
#include "ns3/ltu-wifi-helper.h"
#include "ns3/netanim-module.h"
#include <iostream>

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

  LtuWifiHelper wifi;
  wifi.SetSsid("GruvNET");//Optional

  for(int i = 0; i < 5; i++) {
    Ptr<WifiAccessPoint> ap = wifi.CreateAccessPoint(100*i, 0, 0);
    if(i > 0) {
        ap->ConnectWired(wifi.GetAP(i - 1));
    }
  }

  for(int i = 0; i < 5; i++) {
    Ptr<WifiAccessPoint> ap = wifi.CreateAccessPoint(100*i, 200, 0);
    if(i > 0) {
        ap->ConnectWired(wifi.GetAP(i + 4));
    }
  }

  for(int i = 0; i < 5; i++) {
    Ptr<WifiAccessPoint> ap = wifi.CreateAccessPoint(100*i, 400, 0);
    if(i > 0) {
        ap->ConnectWired(wifi.GetAP(i + 9));
    }
  }
  wifi.GetAP(2)->ConnectWired(wifi.GetAP(7));
  wifi.GetAP(7)->ConnectWired(wifi.GetAP(12));

  NodeContainer wifiClients = wifi.CreateClient(225, 175, 0, 300, 300, 20);
  wifiClients.Add(wifi.CreateClient(25, 25, 0, 50, 50, 10));
  wifiClients.Add(wifi.CreateClient(100, 50, 0, 200, 150, 35));
  wifiClients.Add(wifi.CreateClient(200, 75, 100, 50, 100, 5));
  wifiClients.Add(wifi.CreateClient(200, 100, 0, 100, 100));

  wifi.InstallAll();

  Address dest;
  std::string protocol;
  dest = InetSocketAddress (wifi.GetClientIP(1), 1025);
  protocol = "ns3::UdpSocketFactory";

  OnOffHelper onoff = OnOffHelper (protocol, dest);
  onoff.SetConstantRate (DataRate ("500kb/s"));
  ApplicationContainer apps = onoff.Install (wifiClients.Get(0));
  apps.Start (Seconds (0.5));
  apps.Stop (Seconds (300.0));

  AnimationInterface anim ("labtest2-animation.xml");

  Simulator::Stop (Seconds (300.0));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
