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


/**
 executeAction Replaces Agent with new agent.
 
 Agent to be replaced is primeMover in group. New location is other member of group
 Other location could be same as current location (if there were no free locations)
 Also does bookkeeping, updating living agents by removing links to dead agents
 We must ensure we call this for every agent not just dead agents so formGroup must return a valid group 
 even if the agent is not being replaced
 
 @param loc :pointer to location of agent to be replaced
 @param grp :Group containing new location for replacement
 @returns true if agent is replaced
 @exception none
 */
bool AgentReplacement::executeAction(Location *loc, group *grp)
{
    if (loc->hasAgent()) {
        Agent* theAgent=loc->getAgent();
        if (theAgent->isDead()) {
            loc->setAgent(nullptr);/*!< remove from current location */
            grp->getMembers()[0]->setAgent(theAgent);/*!< add to new location */
            theAgent->reincarnate(grp->getMembers()[0]->getPosition());/*!<update agent attributes to new ones */
            std::cout << "REPLACEMENT"<< loc->getPosition().first<<"," <<loc->getPosition().second << "->" <<grp->getMembers()[0]->getPosition().first <<grp->getMembers()[0]->getPosition().second <<std::endl;
        } else {/*!< agent not dead so remove all links to newly dead agents */
            for(auto ag:theAgent->getChildren())/*!< check for links to dead children and remove them */
            {
                if (ag->isDead()) {
                    theAgent->removeChild(ag);
                }
            }
            theAgent->removeDeadLoans();/*!< remove loans with dead agents */
            theAgent->removeDeadFather();/*!< remove father if dead */
            theAgent->removeDeadMother();/*!< remove mother if dead */
        }
        return true;
    }else{
        return false;/*!< no agent present so did nothing */
    }
  
}

/**
 formGroup forms a group of two - the primeMover and the location of its replacement
 
 If the agent is not being replaced we from a group of one. This is to ensure every agent runs execute action
 Only try find frree slot twice. On second block just spawn in place. Would be better if we kept trying but
 This would require updating the free slots list to remove all slots marked done.
 
 @param loc :location we are examining
 @returns pointer to group object -nullptr if location contains no agent or if agent is not due for replacement
 @exception none
 */
group* AgentReplacement::formGroup(Location *loc)
{
    if (loc->hasAgent()) {
        group *grp= new group();/*!< create group */
        grp->setRank(1);
        grp->setActiveParticipants(1);
        grp->setPrimeMover(loc);
        if (loc->getAgent()->isDead()) {
            if (freeSlots.size()==0) {/*!< spawn at current location */
                grp->push_back(loc);
            } else { /*!< spawn at new random empty location */
                int index=sim->getRnd(0, (int)freeSlots.size()-1);
                if (freeSlots[index]->isDone()) {//slot not free
                    grp->push_back(loc);
                } else{
                    grp->push_back(freeSlots[index]);
                }
            }
            return grp;
        }else{
            return grp;/*!< return group with no new location  */
        }
    }
    return nullptr;//no dead agent here so do nothing

}

/**
 run now gets list of all free slots before running the replacement rule
 @param startX :top left corner X - coordinate
 @param startY :top left corner Y - coordinate
 @param size : width and height of grid
 @returns true if sucessful
 @exception none
 */
bool AgentReplacement::run(int startX, int startY, int size)
{
    populateFreeSlots();
    return WriteAction::run(startX, startY, size);
}

/**
 concurrentRun now gets list of all free slots before running the replacement rule
 @returns true if sucessful
 @exception none
 */
bool AgentReplacement::concurrentRun(void)
{
    populateFreeSlots();
    return WriteAction::concurrentRun();
}

/**
 populateFreeslots puts all free slots in a vector held by this class
 
 @returns number of free slots
 @exception none
 */
unsigned long AgentReplacement::populateFreeSlots()
{
    freeSlots.clear();
    Location* loc= sim->getLattice();
    int dim=sim->getSize();
    for (int i=0; i<dim; ++i) {
        for (int k=0; k<dim; ++k) {
            if (loc[i*dim+k].hasAgent()==false) freeSlots.push_back(&loc[i*dim+k]);
        }
    }
    return freeSlots.size();
}