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


int ReadAction::run(void){
    int size=sim->getSize();
    Location** Lattice=sim->getLattice();
    //Perform action
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            executeAction(&Lattice[i][k]);
        }
    }
    //Update everyone
    for (int i=0; i<size; ++i) {
        for (int k=0; k<size; ++k) {
            Lattice[i][k].sync();
            if (Lattice[i][k].hasAgent()) {
                Lattice[i][k].getAgent()->sync();
            }
        }
    }
    return 1;
    
}

