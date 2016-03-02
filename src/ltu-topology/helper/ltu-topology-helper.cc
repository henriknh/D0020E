/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-topology-helper.h"
#include "ns3/ltu-wifi-module.h"
#include "ns3/ltu-wall-module.h"

namespace ns3 {

void LtuTopologyHelper::createWifiTopology(){
    //7 < 4 < 3 < 1 < 2
    //7 < 5 < 6
    //7 < 8 < 9 < 12 < 13 < 16
    //8 < 10 < 11 < 15 < 20 < 24 < 23 < 19 < 18 < 17
    //15 < 14
    //20 < 21
    //19 < 22
    this->wifiHelper.CreateAccessPoint(-53.3, 97.5, 1);//AP= 1 Index = AP-1
    this->wifiHelper.CreateAccessPoint(-42.5, 95, 1);//2
    this->wifiHelper.CreateAccessPoint(-57.5, 75, 1);//3
    this->wifiHelper.CreateAccessPoint(-52.5, 62.5, 1);//4
    this->wifiHelper.CreateAccessPoint(-37.5, 65, 1);//5
    this->wifiHelper.CreateAccessPoint(-36.6, 60, 1);//6
    this->wifiHelper.CreateAccessPoint(-57.5, 57.5, 1);//7
    this->wifiHelper.CreateAccessPoint(5, 47.5, 1);//8
    this->wifiHelper.CreateAccessPoint(50, 45, 1);//9
    this->wifiHelper.CreateAccessPoint(12.5, 38.3, 1);//10
    this->wifiHelper.CreateAccessPoint(13.3, 0, 1);//11
    this->wifiHelper.CreateAccessPoint(70, -2.5, 1);//12
    this->wifiHelper.CreateAccessPoint(70, -7.5, 1);//13
    this->wifiHelper.CreateAccessPoint(-26.6, -35.5, 1);//14
    this->wifiHelper.CreateAccessPoint(13.3, -37.5, 1);//15
    this->wifiHelper.CreateAccessPoint(77.5, -35, 1);//16
    this->wifiHelper.CreateAccessPoint(-65, -77.5, 1);//17
    this->wifiHelper.CreateAccessPoint(-57.5, -90, 1);//18
    this->wifiHelper.CreateAccessPoint(-17.5, -92.5, 1);//19
    this->wifiHelper.CreateAccessPoint(10, -92.5, 1);//20
    this->wifiHelper.CreateAccessPoint(50, -95, 1);//21
    this->wifiHelper.CreateAccessPoint(-26.6, -102.5, 1);//22
    this->wifiHelper.CreateAccessPoint(0, -102.5, 1);//23
    this->wifiHelper.CreateAccessPoint(27.5, -117.5, 1);//24

    //Connecting 7 < 4 < 3 < 1 < 2
    this->wifiHelper.GetAP(3)->ConnectWired(this->wifiHelper.GetAP(6)); //AP 7<4
    this->wifiHelper.GetAP(2)->ConnectWired(this->wifiHelper.GetAP(3));//AP 4<3
    this->wifiHelper.GetAP(0)->ConnectWired(this->wifiHelper.GetAP(3));//AP 3<1
    this->wifiHelper.GetAP(1)->ConnectWired(this->wifiHelper.GetAP(0));//AP 1<2

    //Connecting 7 < 5 < 6
    this->wifiHelper.GetAP(4)->ConnectWired(this->wifiHelper.GetAP(6)); //AP 7 < 5
    this->wifiHelper.GetAP(5)->ConnectWired(this->wifiHelper.GetAP(4)); //AP 5 < 6

    //Connecting 7 < 8 < 9 < 12 < 13 < 16
    this->wifiHelper.GetAP(7)->ConnectWired(this->wifiHelper.GetAP(6)); //AP 7 < 8
    this->wifiHelper.GetAP(8)->ConnectWired(this->wifiHelper.GetAP(7)); //AP 8 < 9
    this->wifiHelper.GetAP(11)->ConnectWired(this->wifiHelper.GetAP(8)); //AP 9 < 12
    this->wifiHelper.GetAP(12)->ConnectWired(this->wifiHelper.GetAP(11)); //AP 12 < 13
    this->wifiHelper.GetAP(15)->ConnectWired(this->wifiHelper.GetAP(12)); //AP 13 < 16

    //Connecting 8 < 10 < 11 < 15 < 20 < 24 < 23 < 19 < 18 < 17
    this->wifiHelper.GetAP(9)->ConnectWired(this->wifiHelper.GetAP(7)); //AP 8 < 10
    this->wifiHelper.GetAP(10)->ConnectWired(this->wifiHelper.GetAP(9)); //AP 10 < 11
    this->wifiHelper.GetAP(14)->ConnectWired(this->wifiHelper.GetAP(10)); //AP 11 < 15
    this->wifiHelper.GetAP(19)->ConnectWired(this->wifiHelper.GetAP(14)); //AP 15 < 20
    this->wifiHelper.GetAP(23)->ConnectWired(this->wifiHelper.GetAP(19)); //AP 20 < 24
    this->wifiHelper.GetAP(22)->ConnectWired(this->wifiHelper.GetAP(23)); //AP 24 < 23
    this->wifiHelper.GetAP(18)->ConnectWired(this->wifiHelper.GetAP(22)); //AP 23 < 19
    this->wifiHelper.GetAP(17)->ConnectWired(this->wifiHelper.GetAP(18)); //AP 19 < 18
    this->wifiHelper.GetAP(16)->ConnectWired(this->wifiHelper.GetAP(17)); //AP 18 < 17

    //Connecting 15 < 14
    this->wifiHelper.GetAP(13)->ConnectWired(this->wifiHelper.GetAP(14)); //AP 15 < 14

    //Connecting 20 < 21
    this->wifiHelper.GetAP(20)->ConnectWired(this->wifiHelper.GetAP(19)); //AP 20 < 21

    //Connecting 19 < 22
    this->wifiHelper.GetAP(21)->ConnectWired(this->wifiHelper.GetAP(18)); //AP 19 < 22


    //1 -69
    this->wallHelper.CreateWall(-100, 75, -47.5, 52.5); //1 
    this->wallHelper.CreateWall(-100, 80, -54, 60); //2
    this->wallHelper.CreateWall(-55, 72.5, -52.5, 60); //3
    this->wallHelper.CreateWall(-55, 72.5, -57.5, 68); //4
    this->wallHelper.CreateWall(-62.5, 70, -57.5, 68); //5
    this->wallHelper.CreateWall(-54, 95, -62.5, 70); //6
    this->wallHelper.CreateWall(-62, 99, -54, 95); //7
    this->wallHelper.CreateWall(-60.5, 104, -62, 99); //8
    this->wallHelper.CreateWall(-60.5, 104, -40, 99); //9
    this->wallHelper.CreateWall(-42, 103, -40, 99);  //10
    this->wallHelper.CreateWall(-36, 104, -42, 103); //11
    this->wallHelper.CreateWall(-36, 104, -35, 100);  //12
    this->wallHelper.CreateWall(-27, 101, -35, 100); //13
    this->wallHelper.CreateWall(-27, 101, -21, 97); //14
    this->wallHelper.CreateWall(-21, 97, -18, 88); //15
    this->wallHelper.CreateWall(-18, 88, -20, 86); //16
    this->wallHelper.CreateWall(-23, 95, -20, 86); //17
    this->wallHelper.CreateWall(-30, 99, -23, 95); //18
    this->wallHelper.CreateWall(-30, 99, -36, 95); //19
    this->wallHelper.CreateWall(-36, 95, -40, 85); //20
    this->wallHelper.CreateWall(-40, 85, -45, 69); //21
    this->wallHelper.CreateWall(-45, 69, -64, -32); //22
    this->wallHelper.CreateWall(-64, -32, -34, 59); //23
    this->wallHelper.CreateWall(-57, 64, -34, 59); //24
    this->wallHelper.CreateWall(-38, 60, -36, 54); //25
    this->wallHelper.CreateWall(-47, 64, -50, 56); //26
    this->wallHelper.CreateWall(-50, 56, -40, 55); //27
    this->wallHelper.CreateWall(-40, 60, -40, 55); //28
    this->wallHelper.CreateWall(-47, 93, -53, 75); //29
    this->wallHelper.CreateWall(-47, 93, -43, 89); //30
    this->wallHelper.CreateWall(-43, 89, -50, 70); //31
    this->wallHelper.CreateWall(-53, 75, -50, 70); //32
    this->wallHelper.CreateWall(-40, 54, 33, 48); //33
    this->wallHelper.CreateWall(33, 56, 33, 48); //33
    this->wallHelper.CreateWall(33, 56, 39, 56); //35
    this->wallHelper.CreateWall(39, 56, 39, 48); //36
    this->wallHelper.CreateWall(39, 48, 52, 47.5); //37
    this->wallHelper.CreateWall(52, 47.5, 70, 15); //38
    this->wallHelper.CreateWall(70, 15, 74, -2); //39
    this->wallHelper.CreateWall(75, 4, 74, -2); //40
    this->wallHelper.CreateWall(82, 5, 75, 4); //41
    this->wallHelper.CreateWall(82, 5, 80, -2); //42
    this->wallHelper.CreateWall(80, -2, 83, -2); //43
    this->wallHelper.CreateWall(83, 1, 83, -2); //44
    this->wallHelper.CreateWall(83, 1, 90, 1); //45
    this->wallHelper.CreateWall(90, 1, 90, -5); //46
    this->wallHelper.CreateWall(73, -5, 90, -5); //47
    this->wallHelper.CreateWall(73, -5, 73, -9); //48
    this->wallHelper.CreateWall(73, -9, 80, -10); //49
    this->wallHelper.CreateWall(80, -10, 80, -15); //50
    this->wallHelper.CreateWall(80, -15, 73, -15); //51
    this->wallHelper.CreateWall(73, -15, 73, -28); //52
    this->wallHelper.CreateWall(73, -28, 55, -28); //53
    this->wallHelper.CreateWall(55, -28, 55, -25); //54
    this->wallHelper.CreateWall(55, -25, 69, -25); //55
    this->wallHelper.CreateWall(66, -7, 69, -25); //56
    this->wallHelper.CreateWall(52, -7, 66, -7); //57	 	
    this->wallHelper.CreateWall(52, -7, 52, -2); //58
    this->wallHelper.CreateWall(52, -2, 68, -2); //59
    this->wallHelper.CreateWall(68, 15, 68, -2); //60
    this->wallHelper.CreateWall(50, 44, 68, 15); //61	
    this->wallHelper.CreateWall(9, 45, 50, 44); //62
    this->wallHelper.CreateWall(-53, 52, 2, 45); //63
    this->wallHelper.CreateWall(9, 45, 18, 19); //64
    this->wallHelper.CreateWall(18, 19, 24, 10); //65
    this->wallHelper.CreateWall(24, 19, 24, 15); //66
    this->wallHelper.CreateWall(24, 15, 15, 15); //67	 
    this->wallHelper.CreateWall(15, 15, 15, -35); //68
    this->wallHelper.CreateWall(2, 45, 12, 30); //69
    this->wallHelper.CreateWall(12, 30, 12, -35); // 70
    this->wallHelper.CreateWall(-38, -37.5, 10, -37.5); // 71
    this->wallHelper.CreateWall(-38, -37.5, -38, -36.5); // 72
    this->wallHelper.CreateWall(-38, -36.5, 10, -36.5); // 73
    this->wallHelper.CreateWall(10, -37.5, 10, -85); // 74
    this->wallHelper.CreateWall(18.5, -37.5, 18.5, -85); // 75
    this->wallHelper.CreateWall(18.5, -37.5, 100, -37.5); // 76
    this->wallHelper.CreateWall(18.5, -36.5, 100, -36.5); // 77
    this->wallHelper.CreateWall(100, -37.5, 100, -36.5); // 78
    this->wallHelper.CreateWall(18.5, -85, 20, -89); // 79
    this->wallHelper.CreateWall(20, -89, 36, -101); // 80
    this->wallHelper.CreateWall(36, -101, 60, -92); // 81
    this->wallHelper.CreateWall(60, -92, 60, -95); // 82
    this->wallHelper.CreateWall(60, -95, 52, -98); // 83
    this->wallHelper.CreateWall(52, -98, 58, -108); // 84
    this->wallHelper.CreateWall(58, -107, 52, -110); // 85
    this->wallHelper.CreateWall(52, -108, 50.5, -105); // 86
    this->wallHelper.CreateWall(50.5, -105, 45, -107); // 87
    this->wallHelper.CreateWall(49, -110, 45, -110); // 88
    this->wallHelper.CreateWall(49, -110, 40, -104); // 89
    this->wallHelper.CreateWall(40, -104.5, 35, -104.5); // 90
    this->wallHelper.CreateWall(48, -97, 44, -101); // 91
    this->wallHelper.CreateWall(48, -97.3, 49.5, -102.5); // 92
    this->wallHelper.CreateWall(49.5, -101, 45, -105); // 93
    this->wallHelper.CreateWall(44, -101, 45, -105); // 94
    this->wallHelper.CreateWall(35, -104.5, 32, -115.3); // 95
    this->wallHelper.CreateWall(32, -115.3, 20, -118); // 96
    this->wallHelper.CreateWall(20, -118, -12, -95); // 97
    this->wallHelper.CreateWall(-12, -95, -20, -95); // 98
    this->wallHelper.CreateWall(-20, -95, -25, -100); // 99
    this->wallHelper.CreateWall(-25, -100, -25, -110); // 100
    this->wallHelper.CreateWall(-25, -110, -10, -114.5); // 101
    this->wallHelper.CreateWall(-10, -114.5, -10, -115.5); // 102
    this->wallHelper.CreateWall(-10, -115.5, -25, -112); // 103
    this->wallHelper.CreateWall(-25, -112, -23.5, -95); // 104
    this->wallHelper.CreateWall(-25.3, -95, -45, -91); // 105
    this->wallHelper.CreateWall(-45, -91, -48.3, -96); // 106
    this->wallHelper.CreateWall(-48.3, -96, -56.5, -96); // 107
    this->wallHelper.CreateWall(-56.5, -96, -58, -105); // 108
    this->wallHelper.CreateWall(-58, -105, -62, -105); // 109
    this->wallHelper.CreateWall(-62, -105, -62, -88); // 110
    this->wallHelper.CreateWall(-62, -88, -68, -80); // 111
    this->wallHelper.CreateWall(-68, -80, -45, -48); // 112
    this->wallHelper.CreateWall(-45, -48, -41, -48); // 113
    this->wallHelper.CreateWall(-41, -48, -41, -48); // 114
    this->wallHelper.CreateWall(-68, -80, -60, -85); // 115
    this->wallHelper.CreateWall(-60, -85, -10, -93); // 116
    this->wallHelper.CreateWall(-10, -93, 20, -115); // 117
    this->wallHelper.CreateWall(20, -115, 30, -114); // 118
    this->wallHelper.CreateWall(30, -114, 29, -100); // 119
    this->wallHelper.CreateWall(29, -100, 3, -94); // 120
    this->wallHelper.CreateWall(3, -94, 3, -90); // 121
    this->wallHelper.CreateWall(3, -94, 10, -85); // 122
    this->wallHelper.CreateWall(-55, -80, -90, -50); // 123
    this->wallHelper.CreateWall(-90, -50, -50, -95); // 124
    this->wallHelper.CreateWall(-50, -95, -55, -95); // 125
    this->wallHelper.CreateWall(-55, -95, -55, -80); // 126		
			
    this->wallHelper.InstallWalls();
    this->wifiHelper.InstallAll(this->wallHelper.GetLossModel());
}



}

