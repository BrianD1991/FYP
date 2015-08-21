//
//  AgentBasicMove.cpp
//  SugarScape
//
//  Created by Joseph kehoe on 10/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "AgentBasicMove.h"

AgentBasicMove::AgentBasicMove(World *s)
    :WriteAction(s)
{
    //our work is done
}




bool AgentBasicMove::executeAction(Location *loc, group * grp)
{
    if (loc->hasAgent()) {
        Agent* theAgent=loc->getAgent();
        std::pair<int,int> currPosition=theAgent->getPosition();
        std::pair<int,int> newPosition=grp->getMembers()[0]->getPosition();
        sim->setAgent(currPosition, nullptr);/*!< remove old location ptr to agent */
        theAgent->setPosition(newPosition);/*!< set new position to new location */
        sim->setAgent(newPosition,theAgent);/*!< add ptr to agent at new location */
        theAgent->incSugar(grp->getMembers()[0]->getSugar());/*!< eat sugar at new location */
        grp->getMembers()[0]->setSugar(0);/*!< sugar at new location now consumed */
        return true;
    }else{
        std::cerr << "exectued basicMove on location with no agent! " << std::endl;
        return false;/*!< no agent present so do nothing */
    }
}

/**
 * Pick a random empty location within our neighbourhood as defined by our vision
 * @param loc :Our location
 * @see Move Rule
 * @return Our chosen location held in a group object (or our existing location if we have no move
 * @exception none
 */
group* AgentBasicMove::formGroup(Location *loc)
{
    group *ourChoice = nullptr;
    if (loc->hasAgent()) {/*!< Agent at this location */
        ourChoice = new group();     
        Agent* theAgent=loc->getAgent();
        std::vector<Location*> possibleDestinations=sim->getEmptyNeighbourhood(theAgent->getPosition(), theAgent->getVision());/*!< find all empty locations */
        if (possibleDestinations.size()!=0) {/*!< check to see if we can move anywhere */
            int index=pickIndex(possibleDestinations);
            int rank=possibleDestinations[index]->getPosition().first-theAgent->getPosition().first
                    +possibleDestinations[index]->getPosition().second-theAgent->getPosition().second;
            if (rank<0) rank =-rank;
            ourChoice->push_back(possibleDestinations[index]);
            ourChoice->setRank(rank);
            ourChoice->setPrimeMover(loc);
            ourChoice->setActiveParticipants(1);//one active participant per group - the agent moving
        }
        else{/*!< nowhere to move so stay here */
            ourChoice->push_back(loc);
            ourChoice->setRank(0);
            ourChoice->setPrimeMover(loc);
            ourChoice->setActiveParticipants(1);
        }
        
    }
    return ourChoice;/*!< is NOT nullPtr only if we assigned it a value earlier */
}






