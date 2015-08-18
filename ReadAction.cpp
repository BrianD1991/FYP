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
    //Perform action
    for (int i=startX; i<startX+size; ++i) {
        for (int k=startY; k<startY+size; ++k) {
            executeAction(&Lattice[i*size+k],nullptr);
        }
    }
    //Update everyone
    for (int i=startX; i<startX+size; ++i) {
        for (int k=startY; k<startY+size; ++k) {
            Lattice[i*size+k].sync();
            if (Lattice[i*size+k].hasAgent()) {
                Lattice[i*size+k].getAgent()->sync();
            }
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
    Location* Lattice=sim->getLattice();
    //Perform action
#pragma omp for
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            executeAction(&Lattice[i*size+k],nullptr);
        }
    }
    //Update everyone
#pragma omp for
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            Lattice[i*size+k].sync();
            if (Lattice[i*size+k].hasAgent()) {
                Lattice[i*size+k].getAgent()->sync();
            }
        }
    }
    return true;
    
}

