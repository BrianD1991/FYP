//
//  WriteAction.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "WriteAction.h"

WriteAction::WriteAction(World* theWorld):Action(theWorld){
    
}
WriteAction::~WriteAction(void){
    
}
int WriteAction::run(void){
    int size=sim->getSize();
    Location** Lattice=sim->getLattice();
    
    std::vector<group*> proposedGroups, ExclusiveGroups;
    int remaining=size*size;
    while (remaining>0) {
        //Part One: Form group proposals
        for (int i=0; i<size; ++i ) {
            for (int k=0; k<size; ++k) {
                proposedGroups.push_back(formGroup(&Lattice[i][k]));
            }
        }
        //Part Two: Sort proposed groups
        std::sort(proposedGroups.begin(), proposedGroups.end(), group::compare);
        //Part Three: Find Exclusive Groups
        for(auto grp:proposedGroups){
            bool exclusive=true;
            std::vector<Location*> members=grp->getMembers();
            for(auto loc:members){//any agents in group already taken?
                if (loc->isDone()) {
                    exclusive=false;
                }
            }
            if (exclusive) {//all agents in group are free!
                ExclusiveGroups.push_back(grp);
                for(auto loc:members){
                    loc->markDone();
                    --remaining;
                }
            }
        }
        
    }//While
    //Exclusive Groups all formed here. Apply actions
    for(auto grp:ExclusiveGroups){
        std::vector<Location*> members=grp->getMembers();
        for(auto loc:members){
            executeAction(loc);
        }
    }
    //update states
    for(auto grp:ExclusiveGroups){
        std::vector<Location*> members=grp->getMembers();
        for(auto loc:members){
            loc->sync();
            if (loc->hasAgent()) {
                loc->getAgent()->sync();
            }
        }
    }
    
    return -1;
    
}

