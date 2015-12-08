/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ltu-wall-helper.h"
#include <ns3/log.h>

using namespace std;

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LtuWallHelper");

//NS_OBJECT_ENSURE_REGISTERED (LtuWallHelper);


LtuWallHelper::LtuWallHelper () 
{
  NS_LOG_FUNCTION (this);
}

LtuWallHelper::~LtuWallHelper ()
{
  NS_LOG_FUNCTION (this);
}

/*TypeId
LtuWallHelper::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::LtuWallHelper")
    .SetParent<LtuWall> ()
    .SetGroupName("LtuWall")
    .AddConstructor<LtuWallHelper> ()
    ;
  return tid;
}*/


void LtuWallHelper::CreateWall (uint64_t x1, uint64_t y1, uint64_t z1, uint64_t x2, uint64_t y2, uint64_t z2)
{
  
}


}

