/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "wifi-access-point-container.h"
#include "wifi-access-point.h"
#include "ns3/log.h"


namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("WifiAccessPointContainer");

WifiAccessPointContainer::WifiAccessPointContainer() {
    
}

uint32_t 
WifiAccessPointContainer::GetN (void) const
{
  return m_aps.size ();
}

Ptr<WifiAccessPoint> 
WifiAccessPointContainer::Get (uint32_t i) const
{
  return m_aps[i];
}

void 
WifiAccessPointContainer::Add (Ptr<WifiAccessPoint> ap)
{
  m_aps.push_back (ap);
}

}

