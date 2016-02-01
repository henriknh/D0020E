/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "wifi-access-point.h"
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/log.h"
#include "ns3/bridge-module.h"


namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("WifiAccessPoint");

WifiAccessPoint::WifiAccessPoint(double x, double y, double z, InternetStackHelper stack) {
    this->node.Create(1);
    stack.Install(this->node);
    MobilityHelper mobility;
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install(this->node);
    (this->node.Get(0)->GetObject<ConstantPositionMobilityModel>())->SetPosition(Vector(x, y, z));
}

void
WifiAccessPoint::ConnectWired(Ptr<Node> nodeToConnect) {
    WiredConnection *conn = new WiredConnection(this->node.Get(0), nodeToConnect);
    Ptr<WiredConnection> connPtr = Ptr<WiredConnection>(conn);
    this->wiredConnections.Add(connPtr);
}

void
WifiAccessPoint::ConnectWired(Ptr<WifiAccessPoint> ap) {
    WiredConnection *conn = new WiredConnection(this->node.Get(0), ap->node.Get(0));
    Ptr<WiredConnection> connPtr = Ptr<WiredConnection>(conn);
    this->wiredConnections.Add(connPtr);
    ap->wiredConnections.Add(connPtr);
}

Ipv4InterfaceContainer
WifiAccessPoint::Install(Ssid *ssid, Ptr<YansWifiChannel> channel, Ipv4AddressHelper *ip) {
    //Install WiFi
    YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
    wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);
    WifiHelper wifi = WifiHelper::Default ();
    NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
    wifiPhy.SetChannel (channel);
    wifiMac.SetType ("ns3::ApWifiMac",
                     "Ssid", SsidValue (*ssid));
    NetDeviceContainer device;
    device = wifi.Install (wifiPhy, wifiMac, this->node.Get (0));

    //Install CSMA
    int size = this->wiredConnections.GetN();
    for (int i = 0; i < size; i++) {
        this->wiredConnections.Get(i)->Connect();
    }

    //Install bridge on all netdevices except LoopbackNetDevice (refer to bug #1487 in bugzilla)
    NetDeviceContainer bridgeDevices;
    int numberOfDevices = this->node.Get(0)->GetNDevices();
    for(int i = 1; i < numberOfDevices; i++) {//Loopback is at 0, therefore start at 1
        bridgeDevices.Add(this->node.Get(0)->GetDevice(i));
    }
    
    BridgeHelper bridge;
    NetDeviceContainer bridgeDevice = bridge.Install(this->node.Get(0), bridgeDevices);
    return ip->Assign(bridgeDevice);//IP is only set on the bridge, not the other interfaces
}

}

