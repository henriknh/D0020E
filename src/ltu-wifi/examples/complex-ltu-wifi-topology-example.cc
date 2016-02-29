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
#include "ns3/applications-module.h"
#include "ns3/ltu-wifi-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("LtuWifiComplexTopologyExample");

int 
main (int argc, char *argv[])
{
  bool verbose = true;
  CommandLine cmd;
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);

  cmd.Parse (argc,argv);

  if (verbose)
    {
      LogComponentEnable("LtuWifiComplexTopologyExample", LOG_LEVEL_INFO);
      LogComponentEnable("WifiAccessPoint", LOG_LEVEL_INFO);
      LogComponentEnable("WiredConnection", LOG_LEVEL_INFO);
      LogComponentEnable("WiredConnectionContainer", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }

  /**** Topology generation starts here ****/

  LtuWifiHelper wifi;//Instantiate a new helper

  wifi.SetSsid("MyLittleWifiNetwork");//Optional

  //Below loops adds rows of access points, this could have been done by "hand" but it's easier with loops
  for(int i = 0; i < 5; i++) {
    Ptr<WifiAccessPoint> ap = wifi.CreateAccessPoint(100*i, 0, 0);//Create new access point
    if(i > 0) {
        ap->ConnectWired(wifi.GetAP(i - 1));//Connect with a wire to the previous access point
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

  wifi.GetAP(2)->ConnectWired(wifi.GetAP(7));//Connect row one to row two
  wifi.GetAP(7)->ConnectWired(wifi.GetAP(12));//Connect row two to row three

  NodeContainer wiredClients = wifi.CreateWiredClient(-25, 0, 0);//Creates a stationary wired client, e.g. a server
  wifi.GetAP(0)->ConnectWired(wiredClients);//Connect to top left access point

  //Create some mobile WiFi-clients
  NodeContainer wifiClients = wifi.CreateClient(300, 150, 0, 300, 300, 20);
  wifiClients.Add(wifi.CreateClient(25, 25, 0, 50, 50, 10));
  wifiClients.Add(wifi.CreateClient(100, 50, 0, 200, 150, 35));
  wifiClients.Add(wifi.CreateClient(200, 75, 100, 50, 100, 5));
  wifiClients.Add(wifi.CreateClient(200, 100, 0, 100, 100));

  wifi.InstallAll();//This must be called after all nodes has been added.

  /**** Topology generation ends here, application set up below ****/

  Address dest;
  std::string protocol;
  dest = InetSocketAddress (wifi.GetWiredClientIP(0), 1025);//Send packets to the stationary wired client
  protocol = "ns3::UdpSocketFactory";

  OnOffHelper onoff = OnOffHelper (protocol, dest);
  onoff.SetConstantRate (DataRate ("500kb/s"));
  ApplicationContainer apps = onoff.Install (wifiClients.Get(0));//Send packets from the first WiFi-client added
  apps.Start (Seconds (0.5));
  apps.Stop (Seconds (300.0));

  Simulator::Stop (Seconds (300.0));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
