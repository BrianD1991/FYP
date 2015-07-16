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


bool myCompare(Location *a, Location *b)
{
    if (a->getPollution()==b->getPollution()) {
        return a->getSugar()>b->getSugar();
    } else
    {
        return a->getPollution()<b->getPollution();
    }
}



int AgentMove::pickIndex(std::vector<Location*> possibleDestinations)
{
    std::sort(possibleDestinations.begin(),possibleDestinations.end(),myCompare);
    return 0;
}


