/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-topology-helper.h"
#include "ns3/ltu-wifi-module.h"

namespace ns3 {

void LtuTopologyHelper::createWifiTopology(){

//7 < 4 < 3 < 1 < 2
//7 < 5 < 6
//7 < 8 < 9 < 12 < 13 < 16
//8 < 10 < 11 < 15 < 20 < 24 < 23 < 19 < 18 < 17
//15 < 14
//20 < 21
//19 < 22
LtuWifiHelper wifi;
wifi.CreateAccessPoint(-53.3, 97.5, 0);//AP= 1 Index = AP-1
wifi.CreateAccessPoint(-42.5, 95, 0);//2
wifi.CreateAccessPoint(-57.5, 75, 0);//3
wifi.CreateAccessPoint(-52.5, 62.5, 0);//4
wifi.CreateAccessPoint(-37.5, 65, 0);//5
wifi.CreateAccessPoint(-36.6, 60, 0);//6
wifi.CreateAccessPoint(-57.5, 57.5, 0);//7
wifi.CreateAccessPoint(5, 47.5, 0);//8
wifi.CreateAccessPoint(50, 45, 0);//9
wifi.CreateAccessPoint(12.5, 38.3, 0);//10
wifi.CreateAccessPoint(13.3, 0, 0);//11
wifi.CreateAccessPoint(70, -2.5, 0);//12
wifi.CreateAccessPoint(70, -7.5, 0);//13
wifi.CreateAccessPoint(-26.6, -35.5, 0);//14
wifi.CreateAccessPoint(13.3, -37.5, 0);//15
wifi.CreateAccessPoint(77.5, -35, 0);//16
wifi.CreateAccessPoint(-65, -77.5, 0);//17
wifi.CreateAccessPoint(-57.5, -90, 0);//18
wifi.CreateAccessPoint(-17.5, -92.5, 0);//19
wifi.CreateAccessPoint(10, -92.5, 0);//20
wifi.CreateAccessPoint(50, -95, 0);//21
wifi.CreateAccessPoint(-26.6, -102.5, 0);//22
wifi.CreateAccessPoint(0, -102.5, 0);//23
wifi.CreateAccessPoint(-27.5, -117.5, 0);//24

//Connecting 7 < 4 < 3 < 1 < 2
wifi.GetAP(3)->ConnectWired(wifi.GetAP(6)); //AP 7<4
wifi.GetAP(2)->ConnectWired(wifi.GetAP(3));//AP 4<3
wifi.GetAP(0)->ConnectWired(wifi.GetAP(3));//AP 3<1
wifi.GetAP(1)->ConnectWired(wifi.GetAP(0));//AP 1<2

//Connecting 7 < 5 < 6
wifi.GetAP(4)->ConnectWired(wifi.GetAP(6)); //AP 7 < 5
wifi.GetAP(5)->ConnectWired(wifi.GetAP(4)); //AP 5 < 6

//Connecting 7 < 8 < 9 < 12 < 13 < 16
wifi.GetAP(7)->ConnectWired(wifi.GetAP(6)); //AP 7 < 8
wifi.GetAP(8)->ConnectWired(wifi.GetAP(7)); //AP 8 < 9
wifi.GetAP(11)->ConnectWired(wifi.GetAP(8)); //AP 9 < 12
wifi.GetAP(12)->ConnectWired(wifi.GetAP(11)); //AP 12 < 13
wifi.GetAP(15)->ConnectWired(wifi.GetAP(12)); //AP 13 < 16

//Connecting 8 < 10 < 11 < 15 < 20 < 24 < 23 < 19 < 18 < 17
wifi.GetAP(9)->ConnectWired(wifi.GetAP(7)); //AP 8 < 10
wifi.GetAP(10)->ConnectWired(wifi.GetAP(9)); //AP 10 < 11
wifi.GetAP(14)->ConnectWired(wifi.GetAP(10)); //AP 11 < 15
wifi.GetAP(19)->ConnectWired(wifi.GetAP(14)); //AP 15 < 20
wifi.GetAP(23)->ConnectWired(wifi.GetAP(19)); //AP 20 < 24
wifi.GetAP(22)->ConnectWired(wifi.GetAP(23)); //AP 24 < 23
wifi.GetAP(18)->ConnectWired(wifi.GetAP(22)); //AP 23 < 19
wifi.GetAP(17)->ConnectWired(wifi.GetAP(18)); //AP 19 < 18
wifi.GetAP(16)->ConnectWired(wifi.GetAP(17)); //AP 18 < 17

//Connecting 15 < 14
wifi.GetAP(13)->ConnectWired(wifi.GetAP(14)); //AP 15 < 14

//Connecting 20 < 21
wifi.GetAP(20)->ConnectWired(wifi.GetAP(19)); //AP 20 < 21

//Connecting 19 < 22
wifi.GetAP(21)->ConnectWired(wifi.GetAP(18)); //AP 19 < 22

wifi.InstallAll();

  //AnimationInterface anim ("Topology-animation.xml");

  //Simulator::Stop (Seconds (300.0));
  //Simulator::Run ();
 // Simulator::Destroy ();

}



}

