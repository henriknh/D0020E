/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_WALL_CONTAINER_H
#define LTU_WALL_CONTAINER_H

#include <ns3/ltu-wall.h>
#include <vector>

namespace ns3 {

class LtuWallContainer {
public:
    LtuWallContainer();
    uint32_t GetN (void) const;
    Ptr<Wall> Get (uint32_t i) const;
    void Add (Ptr<Wall> w);

protected:
    std::vector<Ptr<Wall> > m_walls; //!< Wall smart pointers
};

} // ns3

#endif /* LTU_WALL_CONTAINER_H */

