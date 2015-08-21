//
//  Diffusion.cpp
//  SugarScape
//
//  Created by Joseph Kehoe on 12/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "Diffusion.h"


Diffusion::Diffusion(World *s):ReadAction(s){
    //EMPTY
}

bool Diffusion::executeAction(Location *loc, group *){
    int size=sim->getSize();
    if (sim->getStep() % sim->getPollutionRate()==0) {
        Location* lattice=sim->getLattice();
        int diffusedPollution= lattice[((loc->getX()+1)%size)*size+loc->getY()].getPollution()
                            +lattice[((loc->getX()-1)%size)*size+loc->getY()].getPollution()
                            +lattice[loc->getX()*size+(loc->getY()+1)%size].getPollution()
                            +lattice[loc->getX()*size+(loc->getY()-1)%size].getPollution();
        loc->setPollution(diffusedPollution/4);
        return true;
    }else{
        return false;
    }
    
}

