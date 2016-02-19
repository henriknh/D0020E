/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */

#include <ns3/core-module.h>
#include <ns3/okumura-hata-propagation-loss-model.h>
#include <ns3/itu-r-1411-los-propagation-loss-model.h>
#include <ns3/itu-r-1411-nlos-over-rooftop-propagation-loss-model.h>
#include <ns3/itu-r-1238-propagation-loss-model.h>
#include <ns3/kun-2600-mhz-propagation-loss-model.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/hybrid-wall-propagation-loss-model.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("HybridWallPropagationLossModel");

NS_OBJECT_ENSURE_REGISTERED (HybridWallPropagationLossModel);

HybridWallPropagationLossModel::HybridWallPropagationLossModel ()
{
  m_okumuraHata = CreateObject<OkumuraHataPropagationLossModel> ();
  m_ituR1411Los = CreateObject<ItuR1411LosPropagationLossModel> ();
  m_ituR1411NlosOverRooftop = CreateObject<ItuR1411NlosOverRooftopPropagationLossModel> ();
  m_ituR1238 = CreateObject<ItuR1238PropagationLossModel> ();
  m_kun2600Mhz = CreateObject<Kun2600MhzPropagationLossModel> ();
  
}
HybridWallPropagationLossModel::~HybridWallPropagationLossModel () {}

double HybridWallPropagationLossModel::GetLoss (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const
{ 
  Ptr<Wall> w;
  double wall_pos[4];

  for(unsigned int i = 0; i < walls->GetN(); i++) {
    
    w = walls->Get(i);
    w->GetPosition(wall_pos);

    double p0_x = a->GetPosition ().x;
    double p0_y = a->GetPosition ().y;
    double p1_x = b->GetPosition ().x;
    double p1_y = b->GetPosition ().y;
    double p2_x = wall_pos[0];
    double p2_y = wall_pos[1];
    double p3_x = wall_pos[2];
    double p3_y = wall_pos[3];

    if(get_wall_intersection(p0_x, p0_y, p1_x, p1_y, p2_x, p2_y, p3_x, p3_y)) {
      NS_LOG_INFO("Number of loops: " << i);
      return 999999;
    }
  }




  NS_ASSERT_MSG ((a->GetPosition ().z >= 0) && (b->GetPosition ().z >= 0), "HybridBuildingsPropagationLossModel does not support underground nodes (placed at z < 0)");
 
  double distance = a->GetDistanceFrom (b);

  // get the MobilityBuildingInfo pointers
  Ptr<MobilityBuildingInfo> a1 = a->GetObject<MobilityBuildingInfo> ();
  Ptr<MobilityBuildingInfo> b1 = b->GetObject<MobilityBuildingInfo> ();
  NS_ASSERT_MSG ((a1 != 0) && (b1 != 0), "HybridBuildingsPropagationLossModel only works with MobilityBuildingInfo");

  double loss = 0.0;

  if (a1->IsOutdoor ())
    {
      if (b1->IsOutdoor ())
        {
          if (distance > 1000)
            {
              NS_LOG_INFO (this << a->GetPosition ().z << b->GetPosition ().z << m_rooftopHeight);
              if ((a->GetPosition ().z < m_rooftopHeight)
                  && (b->GetPosition ().z < m_rooftopHeight))
                {
                  loss = ItuR1411 (a, b);
                  //NS_LOG_INFO (this << " 0-0 (>1000): below rooftop -> ITUR1411 : " << loss);
                }
              else
                {
                  // Over the rooftop tranmission -> Okumura Hata
                  loss = OkumuraHata (a, b);
                  //NS_LOG_INFO (this << " O-O (>1000): above rooftop -> OH : " << loss);
                }
            }
          else
            {
              // short range outdoor communication
              loss = ItuR1411 (a, b);
              //NS_LOG_INFO (this << " 0-0 (<1000) Street canyon -> ITUR1411 : " << loss);
            }
        }
      else
        {
          // b indoor
          if (distance > 1000)
            {
              if ((a->GetPosition ().z < m_rooftopHeight)
                  && (b->GetPosition ().z < m_rooftopHeight))
                {                  
                  loss = ItuR1411 (a, b) + ExternalWallLoss (b1) + HeightLoss (b1);
                  //NS_LOG_INFO (this << " 0-I (>1000): below rooftop -> ITUR1411 : " << loss);
                }
              else
                {
                  loss = OkumuraHata (a, b) + ExternalWallLoss (b1);
                  //NS_LOG_INFO (this << " O-I (>1000): above the rooftop -> OH : " << loss);
                }
            }
          else
            {
              loss = ItuR1411 (a, b) + ExternalWallLoss (b1) + HeightLoss (b1);
              //NS_LOG_INFO (this << " 0-I (<1000) ITUR1411 + BEL : " << loss);
            }
        } // end b1->isIndoor ()
    }
  else
    {
      // a is indoor
      if (b1->IsIndoor ())
        {
          if (a1->GetBuilding () == b1->GetBuilding ())
            {
              // nodes are in same building -> indoor communication ITU-R P.1238
              loss = ItuR1238 (a, b) + InternalWallsLoss (a1, b1);;
              //NS_LOG_INFO (this << " I-I (same building) ITUR1238 : " << loss);

            }
          else
            {
              // nodes are in different buildings
              loss = ItuR1411 (a, b) + ExternalWallLoss (a1) + ExternalWallLoss (b1);
              //NS_LOG_INFO (this << " I-I (different) ITUR1238 + 2*BEL : " << loss);
            }
        }
      else
        {
          // b is outdoor
          if (distance > 1000)
            {
              if ((a->GetPosition ().z < m_rooftopHeight)
                  && (b->GetPosition ().z < m_rooftopHeight))
                {
                  loss = ItuR1411 (a, b) + ExternalWallLoss (a1) + HeightLoss (a1);
                  //NS_LOG_INFO (this << " I-O (>1000): down rooftop -> ITUR1411 : " << loss);
                }
              else
                {
                  // above rooftop -> OH
                  loss = OkumuraHata (a, b) + ExternalWallLoss (a1) + HeightLoss (a1);
                  //NS_LOG_INFO (this << " =I-O (>1000) over rooftop OH + BEL + HG: " << loss);
                }
            }
          else
            {
              loss = ItuR1411 (a, b) + ExternalWallLoss (a1)  + HeightLoss (a1);
              //NS_LOG_INFO (this << " I-O (<1000)  ITUR1411 + BEL + HG: " << loss);
            }
        } // end b1->IsIndoor ()
    } // end a1->IsOutdoor ()

  loss = std::max (loss, 0.0);

  return loss;

}





/*
 *      PRIVATE FUNCTIONS FROM HYBRID BUILDINGS PROPAGATION LOSS MODEL
 */

double
HybridWallPropagationLossModel::OkumuraHata (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const
{
  if (m_frequency <= 2.3e9)
    {
      return m_okumuraHata->GetLoss (a, b);
    }
  else
    {
      return m_kun2600Mhz->GetLoss (a, b);
    }
}

double
HybridWallPropagationLossModel::ItuR1411 (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const
{
  if (a->GetDistanceFrom (b) < m_itu1411NlosThreshold)
    {
      return (m_ituR1411Los->GetLoss (a, b));
    }
  else
    {
      return (m_ituR1411NlosOverRooftop->GetLoss (a, b));
    }
}

double
HybridWallPropagationLossModel::ItuR1238 (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const
{
  return m_ituR1238->GetLoss (a,b);
}

char
HybridWallPropagationLossModel::get_wall_intersection(double p0_x, double p0_y, double p1_x, double p1_y, 
    double p2_x, double p2_y, double p3_x, double p3_y) const
{
  double s1_x, s1_y, s2_x, s2_y;
  s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
  s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

  double s, t;
  s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
  t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

  if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
  {
    // Collision detected
    return 1;
  }

  return 0; // No collision
}

void
HybridWallPropagationLossModel::InstallWalls(LtuWallContainer *walls)
{
  this->walls = walls;
}


} // namespace ns3






