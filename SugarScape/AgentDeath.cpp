//
//  AgentDeath.cpp
//  SugarScape
//
//  Created by Joseph kehoe on 16/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "AgentDeath.h"

AgentDeath::AgentDeath(World *s)
    :ReadAction(s)
{
    //our work is done
}

/**
 * Moves agents that are due to die to the deadAgent pointer in location
 * Deletes any references to dead agents in any other classes
 * @param loc :Location we a re checking
 * @param group - not used by this method
 * @see Death Rule
 * @return True if an agent was present
 * @exception none
 */
bool AgentDeath::executeAction(Location * loc, group *)
{
    if (loc->hasAgent()) {
        Agent* theAgent=loc->getAgent();
        if (theAgent->isDead()) {
            //remove from location
            std::pair<int,int> currPosition=theAgent->getPosition();
            if (theAgent!=sim->killAgent(currPosition))
                {
                    std::cerr << "Delete of agent failed"<<std::endl;
                }
            //possibly empty all attributes? or just let them be?
        } else {
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
