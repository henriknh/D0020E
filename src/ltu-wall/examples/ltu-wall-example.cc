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


/*

Creates a wall
                                   
        =========================              =   Wall

*/



using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Test_wifi_wall");

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

  // Instantiate LtuWallHelper 
  LtuWallHelper wallhelper;
  // Create a wall
  wallhelper.CreateWall(-100, 5, 100, 5); 
  // Installs walls in LossModel
  wallhelper.InstallWalls();


  // Setup of Simulator and runs it
  Simulator::Stop (Seconds (5.0));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}
