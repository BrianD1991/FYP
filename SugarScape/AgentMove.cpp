//
//  AgentMove.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 16/07/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "AgentMove.h"
#include <algorithm>

AgentMove::AgentMove(World *s)
:AgentBasicMove(s)
{
    //our work is done
}


/**
 myCompare compares two locations to see whcih is best
 
 if they equal in pollution levels pick location with most sugar
 else pick least polluted
 
 @param a :pointer to location
 @param b :pointer to location
 @returns true if a better than b
 @exception none
 */
bool myCompare(Location *a, Location *b)
{
    if (a->getPollution()==b->getPollution()) {
        return a->getWealth()>b->getWealth();//I am assuming we will only be checking empty locations
    } else
    {
        return a->getPollution()<b->getPollution();
    }
}


/**
 pickIndex returns best location to move to
 
 Sorts vector of possible destinations and picks highest ranking one
 @param possibleDestinations :vector of possible destinations
 @returns index of first destination in sorted vector (the best)
 @exception none
 */
int AgentMove::pickIndex(std::vector<Location*> possibleDestinations)
{
    int best=0;
    for (int i=0; i<possibleDestinations.size(); ++i) {
        if (myCompare(possibleDestinations[i], possibleDestinations[best])) {
            best=i;
        }
    }
    //std::sort(possibleDestinations.begin(),possibleDestinations.end(),myCompare);
    return best;
}


