//
//  ReadAction.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "ReadAction.h"

ReadAction::ReadAction(World* theWorld):Action(theWorld){
    
}
ReadAction::~ReadAction(void){
    
}
/**
 * Forms exclusive Group
 * @param loc :Location to apply rule to
 * @return Pointer to group
 * @exception none
 */
group* ReadAction::formGroup(Location* loc){
    return nullptr;
}

/**
 * Performs a read only action across entire lattice sequentially
 * @see Action.h
 * @return number of actions performed
 * @exception none
 */
bool ReadAction::run(int startX, int startY, int size){
    Location* Lattice=sim->getLattice();
    int dim=sim->getSize();
    //Perform action
#pragma omp parallel for
    for (int i=startX; i<startX+size; ++i) {
        for (int k=startY; k<startY+size; ++k) {
            executeAction(&Lattice[i*dim+k],nullptr);
        }
    }
    return true;
    
}

/**
 * Performs a read only action across entire lattice concurrently
 * @see Action.h
 * @return number of actions performed
 * @exception none
 */
bool ReadAction::concurrentRun(void){
    int size=sim->getSize();
    return run(0,0,size);
}

