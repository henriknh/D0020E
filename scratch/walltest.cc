/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
* Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
*
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
*
* Author: Marco Miozzo <marco.miozzo@cttc.es>
*/

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

#include "walltest.h"
#include <ns3/ltu-wall-helper.h>

using namespace ns3;
using std::vector;

int
main (int argc, char *argv[])
{
  NS_LOG_COMPONENT_DEFINE ("Walltest");
  LogComponentEnable("Walltest", LOG_LEVEL_INFO);
  LogComponentEnable("HybridBuildingsPropagationLossModel", LOG_LEVEL_INFO);
  LogComponentEnable("HybridWallPropagationLossModel", LOG_LEVEL_INFO);
  
  // ???
  CommandLine cmd;
  cmd.Parse(argc, argv);
  ConfigStore inputConfig;
  inputConfig.ConfigureDefaults ();
  cmd.Parse (argc, argv);



  // Init LtuWallHelper
  LtuWallHelper wallhelper;


  // Create walls
  for(int i = 0; i < 9999999; i++)
  {
    wallhelper.CreateWall(5, 5, 6, 5); // Does not intersect
  }
  wallhelper.CreateWall(5, 5, 15, 5); // Last does intersect
  NS_LOG_INFO("Walls created.");


  // Install walls to LossModel
  wallhelper.InstallWalls();
  NS_LOG_INFO("Walls installed.");


  // Point 1
  Ptr<ConstantPositionMobilityModel> mmEnb = CreateObject<ConstantPositionMobilityModel> ();
  mmEnb->SetPosition (Vector (10.0, 0.0, 1));
  Ptr<MobilityBuildingInfo> buildingInfoEnb = CreateObject<MobilityBuildingInfo> ();
  mmEnb->AggregateObject (buildingInfoEnb); // operation usually done by BuildingsHelper::Install
  BuildingsHelper::MakeConsistent (mmEnb);


  // Point 2
  Ptr<ConstantPositionMobilityModel> mmUe = CreateObject<ConstantPositionMobilityModel> ();
  mmUe->SetPosition (Vector (10, 10, 1));
  Ptr<MobilityBuildingInfo> buildingInfoUe = CreateObject<MobilityBuildingInfo> ();
  mmUe->AggregateObject (buildingInfoUe); // operation usually done by BuildingsHelper::Install
  BuildingsHelper::MakeConsistent (mmUe);

  
  // Get loss
  double loss = wallhelper.GetLossModel()->GetLoss (mmEnb, mmUe);


  // Print result
  NS_LOG_INFO ("Pos_a: " << mmEnb->GetPosition() << "\tPos_b: " << mmUe->GetPosition() << "\tLoss: " << loss);
   
    
  Simulator::Destroy ();
  
}
