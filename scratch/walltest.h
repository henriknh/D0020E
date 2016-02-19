#ifndef LIST_H
#define LIST_H

using namespace ns3;

#include "ns3/buildings-propagation-loss-model.h"

class Walltest : public BuildingsPropagationLossModel {
public:
	//void insert(Link * link);
	//Link * remove();
	int size;	// Tillgänglighetsdeklaration,
	//List::print;	// ger medlemmarna size och print synlig (public) tillgänglighet 
};			// eftersom det skyddade (proteted) arvet annars gjort dem skyddade. 

#endif
