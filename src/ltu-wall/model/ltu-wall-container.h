/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_WALL_CONTAINER_H
#define LTU_WALL_CONTAINER_H

#include <ns3/ltu-wall.h>
#include <vector>

namespace ns3 {

/**
 * \brief Container class that hold Walls
 *
 * Stores Walls in a Vector. Functions to get size, 
 * get Wall at position i, and to add a Wall.
 *
 */

class LtuWallContainer : public Object {
public:

LtuWallContainer();


/**
 * Get size of container.
 * 
 * \return size
 */
uint32_t GetN (void) const;


/**
 * Get Wall at position i
 * 
 * \param index of wanted wall
 * 
 * \return Wall
 */
Ptr<Wall> Get (uint32_t i) const;


/**
 * Function to add Wall to container.
 * 
 * \param Wall
 */
void Add (Ptr<Wall> w);


static TypeId GetTypeId (void);

protected:
    std::vector<Ptr<Wall> > m_walls; //!< Wall smart pointers
};

} // ns3

#endif /* LTU_WALL_CONTAINER_H */

