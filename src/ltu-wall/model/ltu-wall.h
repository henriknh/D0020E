/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_WALL_H
#define LTU_WALL_H

#include <ns3/node-container.h>

namespace ns3 {

/**
 * \brief Holds information of a wall
 *
 * Stores 2 coordinates that represent a wall.
 *
 */

class Wall : public SimpleRefCount<Wall> {
public:


/**
 * Constructor that creates a wall of 2 coordinates.
 * 
 * \param 2 coordinates of a wall
 */
Wall(double x0, double y0, double x1, double y1);


/**
 * Recieve an array that is a reference variable with size 4.
 * Coordinates of a wall is stored in the array and "returned".
 * The reason we use reference variable is a limitation in NS3.
 * 
 * \param reference of array with size 4
 */
void GetPosition(double (&array)[4]);


private:
  double x0;
  double y0;
  double x1;
  double y1;
};

} // ns3

#endif /* LTU_WALL_H */

