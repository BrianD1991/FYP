//
//  Growback.cpp
//  SugarScape
//
//  Created by Joseph Kehoe on 11/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "Growback.h"


Growback::Growback(World *sim):IndependentAction(sim){
    
}

bool Growback::executeAction(Location * place,group*){
    
    place->setSugar(sim->getSugarGrowth());
    return true;
    
}



