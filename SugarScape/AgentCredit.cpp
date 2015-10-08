//
//  AgentCredit.cpp
//  SScapeGUI
//
//  Created by Joseph kehoe on 08/10/2015.
//  Copyright (c) 2015 Joseph Kehoe. All rights reserved.
//

#include "AgentCredit.h"


AgentCredit::AgentCredit(World* sim):IterativeWriteAction(sim){
    //our work is done
}


bool AgentCredit::executeAction(Location *loc, group *grp){
    return false;
}

/**
 * Returns group containing agent we can give loan to (a borrower) if one exists
 
 returns nullptr if location is empty.
 Otherwise it returns a group contaiing our location and location of borrowing agent.
 If there are no available borrowers then return a group
 containing only us.
 
 @param loc :location we are forming group for
 @returns pointer to group or nullptr
 @exception none
 */
group* AgentCredit::formGroup(Location *loc){
    if (loc->hasAgent()) {
        if (loc->getAgent()->canLoan()) {
            Agent *me=loc->getAgent();
            Agent *borrower=nullptr;
            group *grp= new group();/*!< create group */
            grp->setRank(1);
            grp->setActiveParticipants(1);
            grp->setPrimeMover(loc);
            for (int i=0; i<4 && borrower==nullptr; ++i) {/*!< find a borrower first */
                
                if (me->getAvail(i) && suitable(loc->getCardinal(i))==true) {
                    borrower=loc->getCardinal(i)->getAgent();
                }
                me->markNeighbour(i);
            }
            if (borrower==nullptr) {/*!< no borrower available return empty group */
                return grp;
            }
            grp->push_back(borrower->getLocation());/*!< if I get here then all is fine create group */
            return grp;
        }
    }
    return nullptr;//no male agent here so do nothing
}

/**
 participationCount
 
 We only count agents who can give loans as participants for this rule
 @param startX :x-coordinate of top left of grid
 @param startY :y-coordinate of top left of grid
 @param dimSize :width and height of grid
 @returns number of participants as int
 @exception none
 */
int AgentCredit::participantCount(int startX, int startY, int dimSize)
{
    int pcount=0;
    Agent *theAgent=nullptr;
#pragma omp parallel for privare(theAgent)
    for (int i=startX; i<startX+dimSize; ++i) {
        for (int k=startY; k<startY+dimSize; ++k) {
            theAgent=sim->getAgent(std::pair<int,int>(i, k));
            if (theAgent!=nullptr) {
                if (theAgent->canLoan() && theAgent->allDone()==false){
                    ++pcount;
                }
            }
        }
    }
    return pcount;
}

bool AgentCredit::suitable(Location *loc){
    if (loc->hasAgent() && loc->getAgent()->wantsLoan()) {
        return true;
    }
    return false;
}
