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
    wifi.CreateAccessPoint(27.5, -117.5, 0);//24

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
 // Init LtuWallHelper
//1 -69
  LtuWallHelper wallhelper;

    wallhelper.CreateWall(-100, 75, -47.5, 52.5); //1 
    wallhelper.CreateWall(-100, 80, -54, 60); //2
    wallhelper.CreateWall(-55, 72.5, -52.5, 60); //3
    wallhelper.CreateWall(-55, 72.5, -57.5, 68); //4
    wallhelper.CreateWall(-62.5, 70, -57.5, 68); //5
    wallhelper.CreateWall(-54, 95, -62.5, 70); //6
    wallhelper.CreateWall(-62, 99, -54, 95); //7
    wallhelper.CreateWall(-60.5, 104, -62, 99); //8
    wallhelper.CreateWall(-60.5, 104, -40, 99); //9
    wallhelper.CreateWall(-42, 103, -40, 99);  //10
    wallhelper.CreateWall(-36, 104, -42, 103); //11
    wallhelper.CreateWall(-36, 104, -35, 100);  //12
    wallhelper.CreateWall(-27, 101, -35, 100); //13
    wallhelper.CreateWall(-27, 101, -21, 97); //14
    wallhelper.CreateWall(-21, 97, -18, 88); //15
    wallhelper.CreateWall(-18, 88, -20, 86); //16
    wallhelper.CreateWall(-23, 95, -20, 86); //17
    wallhelper.CreateWall(-30, 99, -23, 95); //18
    wallhelper.CreateWall(-30, 99, -36, 95); //19
    wallhelper.CreateWall(-36, 95, -40, 85); //20
    wallhelper.CreateWall(-40, 85, -45, 69); //21
    wallhelper.CreateWall(-45, 69, -64, -32); //22
    wallhelper.CreateWall(-64, -32, -34, 59); //23
    wallhelper.CreateWall(-57, 64, -34, 59); //24
    wallhelper.CreateWall(-38, 60, -36, 54); //25
    wallhelper.CreateWall(-47, 64, -50, 56); //26
    wallhelper.CreateWall(-50, 56, -40, 55); //27
    wallhelper.CreateWall(-40, 60, -40, 55); //28
    wallhelper.CreateWall(-47, 93, -53, 75); //29
    wallhelper.CreateWall(-47, 93, -43, 89); //30
    wallhelper.CreateWall(-43, 89, -50, 70); //31
    wallhelper.CreateWall(-53, 75, -50, 70); //32
    wallhelper.CreateWall(-40, 54, 33, 48); //33
    wallhelper.CreateWall(33, 56, 33, 48); //33
    wallhelper.CreateWall(33, 56, 39, 56); //35
    wallhelper.CreateWall(39, 56, 39, 48); //36
    wallhelper.CreateWall(39, 48, 52, 47.5); //37
    wallhelper.CreateWall(52, 47.5, 70, 15); //38
    wallhelper.CreateWall(70, 15, 74, -2); //39
    wallhelper.CreateWall(75, 4, 74, -2); //40
    wallhelper.CreateWall(82, 5, 75, 4); //41
    wallhelper.CreateWall(82, 5, 80, -2); //42
    wallhelper.CreateWall(80, -2, 83, -2); //43
    wallhelper.CreateWall(83, 1, 83, -2); //44
    wallhelper.CreateWall(83, 1, 90, 1); //45
    wallhelper.CreateWall(90, 1, 90, -5); //46
    wallhelper.CreateWall(73, -5, 90, -5); //47
    wallhelper.CreateWall(73, -5, 73, -9); //48
    wallhelper.CreateWall(73, -9, 80, -10); //49
    wallhelper.CreateWall(80, -10, 80, -15); //50
    wallhelper.CreateWall(80, -15, 73, -15); //51
    wallhelper.CreateWall(73, -15, 73, -28); //52
    wallhelper.CreateWall(73, -28, 55, -28); //53
    wallhelper.CreateWall(55, -28, 55, -25); //54
    wallhelper.CreateWall(55, -25, 69, -25); //55
    wallhelper.CreateWall(66, -7, 69, -25); //56
    wallhelper.CreateWall(52, -7, 66, -7); //57	 	
    wallhelper.CreateWall(52, -7, 52, -2); //58
    wallhelper.CreateWall(52, -2, 68, -2); //59
    wallhelper.CreateWall(68, 15, 68, -2); //60
    wallhelper.CreateWall(50, 44, 68, 15); //61	
    wallhelper.CreateWall(9, 45, 50, 44); //62
    wallhelper.CreateWall(-53, 52, 2, 45); //63
    wallhelper.CreateWall(9, 45, 18, 19); //64
    wallhelper.CreateWall(18, 19, 24, 10); //65
    wallhelper.CreateWall(24, 19, 24, 15); //66
    wallhelper.CreateWall(24, 15, 15, 15); //67	 
    wallhelper.CreateWall(15, 15, 15, -35); //68
    wallhelper.CreateWall(2, 45, 12, 30); //69			
			
	

  wallhelper.InstallWalls();
  NS_LOG_INFO("Walls installed.");
    wifi.InstallAll();
}



}

