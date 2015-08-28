//
//  IndependentAction.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "IndependentAction.h"

IndependentAction::IndependentAction(World* theWorld):Action(theWorld){
    
}
IndependentAction::~IndependentAction(void){
    
}

/**
 * Forms exclusive Group for Growback- No group involved so returns null pointer
 * @param currLocation :Location to apply rule to
 * @return Pointer to group
 * @exception none
 */
group* IndependentAction::formGroup(Location *currLocation){
    return nullptr;
}
/**
 * Performs action on entire lattice
 * @see Action
 * @return number of actions performed
 * @exception none
 */
bool IndependentAction::run(int startX, int startY, int size){
    Location* Lattice=sim->getLattice();
    //Perform action
#pragma omp for
    for (int i=startX; i<startX+size; ++i) {
        for (int k=startY; k<startY+size; ++k) {
            executeAction(&Lattice[i*size+k],nullptr);
        }
    }
    sim->sync();
    return true;

}
/**
 * Performs action on entire lattice concurrently
 * @see Action
 * @return number of actions performed
 * @exception none
 */
bool IndependentAction::concurrentRun(void){
    int size=sim->getSize();
    Location* Lattice=sim->getLattice();
    //Perform action
#pragma omp for
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            executeAction(&Lattice[i*size+k],nullptr);
        }
    }
    //Update everyone
    sim->sync();
    return true;
    
}


