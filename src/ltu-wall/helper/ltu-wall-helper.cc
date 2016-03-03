/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include <ns3/core-module.h>
#include <ns3/ltu-wall-helper.h>
#include <ns3/log.h>
#include "ns3/hybrid-wall-propagation-loss-model.h"

using namespace std;

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LtuWallHelper");

//NS_OBJECT_ENSURE_REGISTERED (LtuWallHelper);


LtuWallHelper::LtuWallHelper () 
{
  NS_LOG_FUNCTION (this);
  
  propagationLossModel = CreateObject<HybridWallPropagationLossModel> ();
}

LtuWallHelper::~LtuWallHelper ()
{
  NS_LOG_FUNCTION (this);
}

Ptr<Wall>
LtuWallHelper::CreateWall(double x0, double y0, double x1, double y1)
{
    Wall *w = new Wall(x0, y0, x1, y1);
    Ptr<Wall> wPtr;
    wPtr = Ptr<Wall>(w);
    this->walls.Add(wPtr);
    return wPtr;
}

Ptr<Wall>
LtuWallHelper::GetWall(int i)
{
  return this->walls.Get(i);
}


Ptr<LtuWallContainer>
LtuWallHelper::GetWallsContainer()
{
  Ptr<LtuWallContainer> wallsPointer;
  wallsPointer = Ptr<LtuWallContainer>(&this->walls);
  return wallsPointer;
}

int
LtuWallHelper::GetN(void)
{
   return walls.GetN();
}

void
LtuWallHelper::InstallWalls()
{
  Ptr<LtuWallContainer> wallsPointer;
  wallsPointer = Ptr<LtuWallContainer>(&this->walls);
  this->propagationLossModel->InstallWalls(wallsPointer);
}

Ptr<HybridWallPropagationLossModel> 
LtuWallHelper::GetLossModel()
{
  return this->propagationLossModel;
}


} // NS3

