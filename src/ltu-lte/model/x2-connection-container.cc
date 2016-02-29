/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "x2-connection-container.h"
#include "x2-connection.h"
#include "ns3/log.h"


namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("X2ConnectionContainer");

X2ConnectionContainer::X2ConnectionContainer() {
    
}

uint32_t 
X2ConnectionContainer::GetN (void) const
{
  return m_conns.size ();
}

Ptr<X2Connection> 
X2ConnectionContainer::Get (uint32_t i) const
{
  return m_conns[i];
}

void 
X2ConnectionContainer::Add (Ptr<X2Connection> connection)
{
  m_conns.push_back (connection);
}

}

