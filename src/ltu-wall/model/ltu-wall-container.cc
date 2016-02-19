/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-wall-container.h"
#include "ltu-wall.h"
#include "ns3/log.h"


namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("LtuWallContainer");

LtuWallContainer::LtuWallContainer() {
    
}

uint32_t 
LtuWallContainer::GetN (void) const
{
  return m_walls.size ();
}

Ptr<Wall> 
LtuWallContainer::Get (uint32_t i) const
{
  return m_walls[i];
}

void 
LtuWallContainer::Add (Ptr<Wall> w)
{
  m_walls.push_back (w);
}

}

