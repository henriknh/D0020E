/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_WALL_HELPER_H
#define LTU_WALL_HELPER_H

#include "ns3/ltu-wall.h"
#include <ns3/object.h>

namespace ns3 {

class LtuWallHelper
{       
public:
  
  /** 
   * Constructor
   */
  LtuWallHelper ();

  /** 
   * Destructor
   */  
  ~LtuWallHelper ();
  
  // inherited from Object
  /**
   *  Register this type.
   *  \return The object TypeId.
   */
  //static TypeId GetTypeId (void);
  
  void CreateWall (uint64_t x1, uint64_t y1, uint64_t z1, uint64_t x2, uint64_t y2, uint64_t z2);
};




} // namespace ns-3

#endif /* LTU_WALL_HELPER_H */

