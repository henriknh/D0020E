/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-base-station-container.h"
#include "ltu-base-station.h"
#include "ns3/log.h"


namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("LtuBaseStationContainer");

LtuBaseStationContainer::LtuBaseStationContainer() {
    
}

uint32_t 
LtuBaseStationContainer::GetN (void) const
{
  return m_eNBs.size ();
}

Ptr<LtuBaseStation> 
LtuBaseStationContainer::Get (uint32_t i) const
{
  return m_eNBs[i];
}

void 
LtuBaseStationContainer::Add (Ptr<LtuBaseStation> eNB)
{
  m_eNBs.push_back (eNB);
}

}

