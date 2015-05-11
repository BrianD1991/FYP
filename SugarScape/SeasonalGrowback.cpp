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

bool SeasonalGrowback::executeAction(Location * place){
    
    place->setSugar(sim->getSugarGrowth()/sim->getWinterRate());
    return true;
    
}


