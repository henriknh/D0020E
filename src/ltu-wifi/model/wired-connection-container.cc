/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "wired-connection-container.h"
#include "wired-connection.h"
#include "ns3/log.h"


namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("WiredConnectionContainer");

WiredConnectionContainer::WiredConnectionContainer() {
    
}

uint32_t 
WiredConnectionContainer::GetN (void) const
{
  return m_conns.size ();
}

Ptr<WiredConnection> 
WiredConnectionContainer::Get (uint32_t i) const
{
  return m_conns[i];
}

void 
WiredConnectionContainer::Add (Ptr<WiredConnection> connection)
{
  m_conns.push_back (connection);
}

}

