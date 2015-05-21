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
bool WriteAction::run(int startX, int startY, int size){
    Location** Lattice=sim->getLattice();
    
    std::vector<group*> proposedGroups, ExclusiveGroups;
    int remaining=size*size;
    while (remaining>0) {
//Part One: Form group proposals
        for (int i=startX; i<startX+size; ++i ) {
            for (int k=startY; k<startY+size; ++k) {
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
    
    return true;
    
}

bool WriteAction::concurrentRun(void){
    int sectionSize=sim->getMaxVision();
    /*!< construct tile set - tile contains 9 sections - 3 each side*/
    int tileDim=3*sectionSize;
    int tileNum=sim->getSize()/tileDim;/*!< Assume size%tileDim==0 */
#pragma omp for
    for (int xTile=0; xTile<tileNum; ++xTile) {
#pragma omp for
        for (int yTile=0; yTile<tileNum; ++yTile) {
            //sequentally run through each tile
            for (int i=0; i<3; ++i) {
                for (int k=0; k<3; ++k) {
                    run(xTile+i*sectionSize,yTile+k*sectionSize,sectionSize);
                }
            }
        }
    }
    
    return true;
}

