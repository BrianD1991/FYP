//
//  SeasonalGrowback.cpp
//  SugarScape
//
//  Created by Joseph Kehoe on 11/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "SeasonalGrowback.h"


SeasonalGrowback::SeasonalGrowback(World *sim):IndependentAction(sim){
    
}

/**
 * Seasonal Growback Rule - Growback with winter and summer growing rates
 * @param place :location we are running rule on
 * @param group - not required for this rule
 * @see Seasonal Growback Rule
 * @return true
 * @exception none
 */
bool SeasonalGrowback::executeAction(Location * place, group *){
    if ((sim->getStep()/sim->getSeasonLength())%2==0) {//summer top half
        if (place->getX()*2<sim->getSize()) {
            place->setSugar(sim->getSugarGrowth());
        } else {
            place->setSugar(sim->getSugarGrowth()/sim->getWinterRate());
        }
    } else {//winter top half
        if (place->getX()*2<sim->getSize()) {
            place->setSugar(sim->getSugarGrowth()/sim->getWinterRate());
        } else {
            place->setSugar(sim->getSugarGrowth());
        }
    }
    return true;
    
}


