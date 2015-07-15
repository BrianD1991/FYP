//
//  AgentReplacement.cpp
//  SugarScape
//
//  Created by Joseph kehoe on 07/07/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "AgentReplacement.h"


AgentReplacement::AgentReplacement(World *s)
    :WriteAction(s)
{
    //our work is done!
}

bool AgentReplacement::executeAction(Location *loc, group *grp)
{
    if (loc->hasAgent()) {
        Agent* theAgent=loc->getAgent();
        if (theAgent->isDead()) {
            //remove from location
            loc->setAgent(nullptr);
            //add to new location
            grp->getMembers()[0]->setAgent(theAgent);
            //update agent attributes to new ones
            theAgent->setAge(0);
        } else {
            //agent not dead so remove all links to dead agents
            //check for links to dead children and remove them
            for(auto ag:theAgent->getChildren())
            {
                if (ag->isDead()) {
                    theAgent->removeChild(ag);
                }
            }
            //remove loans with dead agents
            theAgent->removeDeadLoans();
            //remove dead parents
            theAgent->removeDeadFather();
            theAgent->removeDeadMother();
        }
        return true;
    }else{
        return false;/*!< no agent present so did nothing */
    }
  
}

group* AgentReplacement::formGroup(Location *loc)
{
    if (loc->hasAgent()) {
        if (loc->getAgent()->isDead()) {
            group *grp= new group();
            grp->setRank(1);
            grp->setActiveParticipants(1);
            grp->setPrimeMover(loc);
            if (freeSlots.size()==0) {//spawn at current location
                grp->push_back(loc);
            } else {
                int index=sim->getRnd(0, (int)freeSlots.size());
                if (freeSlots[index]->isDone()) {//slot taken spawn in place
                    grp->push_back(loc);
                } else{
                    grp->push_back(freeSlots[index]);
                }
            }
            return grp;
        }
    }
    return nullptr;//no dead agent here so do nothing

}

bool AgentReplacement::run(int startX, int startY, int size)
{
    populateFreeSlots();
    return WriteAction::run(startX, startY, size);
}

bool AgentReplacement::concurrentRun(void)
{
    populateFreeSlots();
    return WriteAction::concurrentRun();
}

unsigned long AgentReplacement::populateFreeSlots()
{
    freeSlots.clear();
    Location** loc= sim->getLattice();
    int dim=sim->getSize();
    for (int i=0; i<dim; ++i) {
        for (int k=0; k<dim; ++k) {
            if (loc[i][k].hasAgent()==false) freeSlots.push_back(&loc[i][k]);
        }
    }
    return freeSlots.size();
}