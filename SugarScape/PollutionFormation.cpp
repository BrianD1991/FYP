//
//  PollutionFormation.cpp
//  SugarScape
//
//  Created by Joseph Kehoe on 12/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "PollutionFormation.h"

PollutionFormation::PollutionFormation(World *s):IndependentAction(s){
    //EMPTY
}
bool PollutionFormation::executeAction(Location *loc, group *){
    if (loc->hasAgent()) {//agent present implies pollution created
        int currPollution=loc->getPollution();
        currPollution+=loc->getAgent()->getMetabolism()*sim->getConsumption();//amount metabolised
        currPollution+=loc->getAgent()->getAmountEaten()*sim->getProduction();
        loc->setPollution(currPollution);
        return true;
    }
    return false;//no agent here so nothing to do
}
