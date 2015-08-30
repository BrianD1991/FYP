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

/**
 * Sugar grows back at a rate set by the World object
 * @param place :the location we are applying rule to
 * @param group - not required for this action. Is a nullptr
 * @see Growback Rule
 * @return true
 * @exception none
 */
bool Growback::executeAction(Location * place,group*){
    
    place->setSugar(place->getSugar()+sim->getSugarGrowth());
    return true;
    
}



