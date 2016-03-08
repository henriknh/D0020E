/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_WALL_HELPER_H
#define LTU_WALL_HELPER_H

#include "ns3/hybrid-wall-propagation-loss-model.h"

namespace ns3 {

/**
 * \brief Creates walls and handles loss when signals intersect with walls.
 *
 * Helper class of LtuWall. Functions to create wall and 
 * handle wall in diffrent ways. The way to use this helper 
 * class is to create all wanted walls. Then call the 
 * InstallWalls-function. If Wifi or LTE is used you can 
 * grab the propagationLossModel by using GetLossModel-function. 
 *
 */

class LtuWallHelper : public SimpleRefCount<LtuWallHelper> 
{       
public:

/**
 * Construktor of LtuWallHelper. Creates a instance 
 * of HybridWallPropagationLossModel.
 */
LtuWallHelper ();


/**
 * Destructor of LtuWallHelper.
 */
~LtuWallHelper ();


/**
 * Creates a wall by two points send in as arguments.
 * x0 and y0 describes position of point1 and x1 and y1 
 * describes position of point2. The walls is stored in 
 * a LtuWallContainer variable
 * 
 * \param Two coordinates
 *
 * \return Created wall
 */
Ptr<Wall> CreateWall(double x0, double y0, double x1, double y1);


/**
 * Index as parameter and return Wall with that index 
 * in LtuWallContainer
 * 
 * \param Index of wanted wall
 *
 * \return Wall
 */
Ptr<Wall> GetWall(int i);


/**
 * Return a NS3 SmartPointer of LtuWallContainer that hold all walls
 *
 * \return NS3 SmartPointer of LtuWallContainer
 */
Ptr<LtuWallContainer> GetWallsContainer();


/**
 * Return size of LtuWallContainer
 * 
 * \return size of LtuWallContainer
 */
int GetN(void);


/**
 * Installs a pointer of LtuWallContainer in HybridWallPropagationLossModel
 */
void InstallWalls();


/**
 * Return a NS3 SmartPointer of HybridWallPropagationLossModel
 * 
 * \return NS3 SmartPointer of HybridWallPropagationLossModel
 */
Ptr<HybridWallPropagationLossModel> GetLossModel();


protected:

Ptr<HybridWallPropagationLossModel> propagationLossModel;
LtuWallContainer walls;
};




} // namespace ns-3

#endif /* LTU_WALL_HELPER_H */

