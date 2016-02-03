/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */




#include <cmath>
#include <math.h>

#include "ns3/core-module.h"
#include <ns3/hybrid-buildings-propagation-loss-model.h>
#include "ns3/log.h"
#include "ns3/mobility-model.h"
#include "ns3/double.h"
#include "ns3/pointer.h"
#include "ns3/okumura-hata-propagation-loss-model.h"
#include "ns3/itu-r-1411-los-propagation-loss-model.h"
#include "ns3/itu-r-1411-nlos-over-rooftop-propagation-loss-model.h"
#include "ns3/itu-r-1238-propagation-loss-model.h"
#include "ns3/kun-2600-mhz-propagation-loss-model.h"
#include <ns3/mobility-building-info.h>
#include "ns3/enum.h"
#include <ns3/buildings-helper.h>
#include <ns3/constant-position-mobility-model.h>

#include <ns3/hybrid-wall-propagation-loss-model.h>

#define PI 3.14159265

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
HybridWallPropagationLossModel::~HybridWallPropagationLossModel (){}

double HybridWallPropagationLossModel::GetLoss (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const
{
 
  //NS_ASSERT_MSG ((a->GetPosition ().z >= 0) && (b->GetPosition ().z >= 0), "HybridBuildingsPropagationLossModel does not support underground nodes (placed at z < 0)");
 
  double distance = a->GetDistanceFrom (b);

  // get the MobilityBuildingInfo pointers
  Ptr<MobilityBuildingInfo> a1 = a->GetObject<MobilityBuildingInfo> ();
  Ptr<MobilityBuildingInfo> b1 = b->GetObject<MobilityBuildingInfo> ();
  //NS_ASSERT_MSG ((a1 != 0) && (b1 != 0), "HybridBuildingsPropagationLossModel only works with MobilityBuildingInfo");








        //http://stackoverflow.com/questions/7586063/how-to-calculate-the-angle-between-a-line-and-the-horizontal-axis
        //http://gamedev.stackexchange.com/questions/48119/how-do-i-calculate-how-an-object-will-move-from-one-point-to-another

  int step = 0;
  int deltaX = b->GetPosition ().x - a->GetPosition ().x;
  int deltaY = b->GetPosition ().y - a->GetPosition ().y;
  double angle = atan2(deltaY, deltaX) * 180 / PI;
  double sumX = 0;
  double sumY = 0;

  while(step <= distance) {
  
        // Calculate next position
    double dx = (double) (cos((angle * PI)/180) * 1);
    double dy = (double) (sin((angle * PI)/180) * 1);

    sumX += dx; 
    sumY += dy;
    if(sumX > deltaX) {
        sumX = deltaX;
    }
    if(sumY > deltaY) {
        sumY = deltaY;
    }
        
    NS_LOG_INFO("STEP TEST\tsumX: " << sumX << "\tsumY: " << sumY <<"\tangle: " << angle << "\tstep: " << step); 

    // Create temp point 1 step further
    Ptr<ConstantPositionMobilityModel> temp = CreateObject<ConstantPositionMobilityModel> ();
    temp->SetPosition (Vector (sumX, sumY, 1.0));
      
    temp->AggregateObject (a1); // operation usually done by BuildingsHelper::Install
    BuildingsHelper::MakeConsistent (temp);

    // Do check if inside
    Ptr<MobilityBuildingInfo> temp1 = temp->GetObject<MobilityBuildingInfo> ();    
    if(!temp1->IsOutdoor()) {
      return 99999.0;
    }  

    step++;
  }

         






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

} // namespace ns3





/*int pos_a = a->GetPosition ().x;
  int pos_b = b->GetPosition ().x;
  while(pos_a <= pos_b)   {
        
      Ptr<ConstantPositionMobilityModel> temp = CreateObject<ConstantPositionMobilityModel> ();
      temp->SetPosition (Vector (pos_a, 0.0, 1.0));
      
      temp->AggregateObject (a1); // operation usually done by BuildingsHelper::Install
      //BuildingsHelper::MakeConsistent (a1);
      BuildingsHelper::MakeConsistent (temp);


      Ptr<MobilityBuildingInfo> temp1 = temp->GetObject<MobilityBuildingInfo> ();
      NS_LOG_INFO("index: " << pos_a << "\tIsOutdoor: " << temp1->IsOutdoor());
        

        if(!temp1->IsOutdoor()) {
                return 99999.0;
}
      
      ++pos_a;
}*/
