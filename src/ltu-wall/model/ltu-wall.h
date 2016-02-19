/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef LTU_WALL_H
#define LTU_WALL_H

#include "ns3/ptr.h"
#include <vector>
#include "ns3/node-container.h"

namespace ns3 {


class Wall : public SimpleRefCount<Wall> {
public:
  Wall(double x0, double y0, double x1, double y1);
  void GetPosition(double (&array)[4]);
private:
  double x0;
  double y0;
  double x1;
  double y1;
};





}

#endif /* LTU_WALL_H */

