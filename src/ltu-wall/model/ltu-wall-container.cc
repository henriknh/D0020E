/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include <ns3/ltu-wall-container.h>


namespace ns3 {

LtuWallContainer::LtuWallContainer() {}

TypeId
LtuWallContainer::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::LtuWallContainer");
  return tid;
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

