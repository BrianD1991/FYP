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
int IndependentAction::run(void){
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


