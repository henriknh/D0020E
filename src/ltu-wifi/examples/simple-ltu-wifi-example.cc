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

NS_LOG_COMPONENT_DEFINE ("LtuWifiSimpleExample");

int 
main (int argc, char *argv[])
{
  bool verbose = true;
  CommandLine cmd;
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);

  cmd.Parse (argc,argv);

  if (verbose)
    {
      LogComponentEnable("LtuWifiSimpleExample", LOG_LEVEL_INFO);
      LogComponentEnable("WifiAccessPoint", LOG_LEVEL_INFO);
      LogComponentEnable("WiredConnection", LOG_LEVEL_INFO);
      LogComponentEnable("WiredConnectionContainer", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }

  /**** Topology generation starts here ****/

  LtuWifiHelper wifi;//Instantiate a new helper

  Ptr<WifiAccessPoint> ap = wifi.CreateAccessPoint(-100, 0, 1);//Create new access point at coordinates (x, y, z) -100, 0 and 1
  Ptr<WifiAccessPoint> ap2 = wifi.CreateAccessPoint(100, 0, 1);//Create another access point

  ap->ConnectWired(ap2);//Connect the two access point together by a wire

  NodeContainer clients = wifi.CreateClient(100, 25, 1, 100, 50, 5);//Create a mobile wifi client which can move withing a 100x500 meter box with a speed of 5
  clients.Add(wifi.CreateClient(-100, 25, 1));//Add another client but this one is a stationary wifi client

  wifi.InstallAll();//This must be called after all nodes has been added.

  /**** Topology generation ends here, application set up below ****/

  Address dest;
  std::string protocol;
  dest = InetSocketAddress (wifi.GetWifiClientIP(1), 1025);
  protocol = "ns3::UdpSocketFactory";

  OnOffHelper onoff = OnOffHelper (protocol, dest);
  onoff.SetConstantRate (DataRate ("500kb/s"));
  ApplicationContainer apps = onoff.Install (clients.Get(0));
  apps.Start (Seconds (0.5));
  apps.Stop (Seconds (60.0));

  Simulator::Stop (Seconds (60.0));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
