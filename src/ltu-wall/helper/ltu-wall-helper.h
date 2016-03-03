/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_WALL_HELPER_H
#define LTU_WALL_HELPER_H

#include "ns3/hybrid-wall-propagation-loss-model.h"

namespace ns3 {

class LtuWallHelper : public SimpleRefCount<LtuWallHelper> 
{       
public:
  LtuWallHelper ();
  ~LtuWallHelper ();
  Ptr<Wall> CreateWall(double x0, double y0, double x1, double y1);
  Ptr<Wall> GetWall(int i);
  Ptr<LtuWallContainer> GetWallsContainer();
  int GetN(void);
  void InstallWalls();
  Ptr<HybridWallPropagationLossModel> GetLossModel();


protected:
  Ptr<HybridWallPropagationLossModel> propagationLossModel;
  LtuWallContainer walls;
};




} // namespace ns-3

#endif /* LTU_WALL_HELPER_H */

