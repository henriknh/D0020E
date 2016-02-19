/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */


#include <ns3/ltu-wall.h>
#include <ns3/core-module.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LtuWall");

Wall::Wall (double x0, double y0, double x1, double y1) {
  this->x0 = x0;
  this->y0 = y0;
  this->x1 = x1;
  this->y1 = y1;
}

void
Wall::GetPosition(double (&array)[4]) {
  array[0] = this->x0;
  array[1] = this->y0;
  array[2] = this->x1;
  array[3] = this->y1;
}

} // ns3

