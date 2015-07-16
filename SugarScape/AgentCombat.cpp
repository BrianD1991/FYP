//
//  AgentCombat.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 16/07/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "AgentCombat.h"

AgentCombat::AgentCombat(World *s)
:AgentMove(s)
{
    //our work is done
}

bool AgentCombat::executeAction(Location *loc, group *grp)
{
    return false;
}


int AgentCombat::findVictim(std::vector<Agent*> possibles)
{
    return -1;
}


group* AgentCombat::formGroup(Location *loc)
{
    
    group *ourChoice = nullptr;
    if (loc->hasAgent()) {//Agent at this location
        Agent* theAgent=loc->getAgent();
        //find all empty locations
        std::vector<Agent*> possibleVictims=sim->getNeighbours(theAgent->getPosition().first, theAgent->getPosition().second, theAgent->getVision());
        ourChoice = new group();
        if (possibleVictims.size()!=0) {/*!< check to see if we can move anywhere */
            int index=findVictim(possibleVictims);
            if (index>-1) {
                ourChoice->push_back(sim->getLocation(possibleVictims[index]->getPosition()));
                int rank=possibleVictims[index]->getPosition().first-theAgent->getPosition().first
                +possibleVictims[index]->getPosition().second-theAgent->getPosition().second;
                if (rank<0) rank =-rank;
                ourChoice->setRank(rank);
                ourChoice->setPrimeMover(loc);
                ourChoice->setActiveParticipants(1);//one active participant per group - the agent moving
            }else
            {
                return AgentMove::formGroup(loc);
            }
        }else
        {
            return AgentMove::formGroup(loc);
        }
        
    }
    return ourChoice;/*!< is NOT nullPtr only if we assigned it a value earlier */
}


