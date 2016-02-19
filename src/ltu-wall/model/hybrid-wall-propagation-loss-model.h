/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Marco Miozzo  <marco.miozzo@cttc.es>
 *         Nicola Baldo <nbaldo@cttc.es>
 * 
 */

#ifndef HYBRID_WALL_PROPAGATION_LOSS_MODEL_H_
#define HYBRID_WALL_PROPAGATION_LOSS_MODEL_H_

#include <ns3/hybrid-buildings-propagation-loss-model.h>
#include <ns3/ltu-wall-container.h>

namespace ns3 {

class HybridWallPropagationLossModel : public HybridBuildingsPropagationLossModel
{
public:
  HybridWallPropagationLossModel ();
  ~HybridWallPropagationLossModel ();
  virtual double GetLoss (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const;
  void InstallWalls(LtuWallContainer *walls);

private: 
  double OkumuraHata (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const;
  double ItuR1411 (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const;
  double ItuR1238 (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const;
  char get_wall_intersection(double p0_x, double p0_y, double p1_x, double p1_y, 
    double p2_x, double p2_y, double p3_x, double p3_y) const;

  Ptr<OkumuraHataPropagationLossModel> m_okumuraHata;
  Ptr<ItuR1411LosPropagationLossModel> m_ituR1411Los;
  Ptr<ItuR1411NlosOverRooftopPropagationLossModel> m_ituR1411NlosOverRooftop;
  Ptr<ItuR1238PropagationLossModel> m_ituR1238;
  Ptr<Kun2600MhzPropagationLossModel> m_kun2600Mhz;

  double m_itu1411NlosThreshold; ///< in meters (switch Los -> NLoS)
  double m_rooftopHeight;
  double m_frequency;
  LtuWallContainer *walls;

};

} // ns3

#endif /* HYBRID_WALL_PROPAGATION_LOSS_MODEL_H_ */
