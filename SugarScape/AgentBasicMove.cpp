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
        //Agent* theAgent=loc->getAgent();
        std::pair<int,int> currPosition=loc->getAgent()->getPosition();
        sim->setAgent(currPosition.first, currPosition.second, nullptr);//remove old location ptr to agent
        loc->getAgent()->setPosition(grp->getMembers()[0]->getPosition());//set new position to new location
        sim->setAgent(grp->getMembers()[0]->getPosition().first,grp->getMembers()[0]->getPosition().second,loc->getAgent());//add ptr to agent at new location
        return true;
    }else{
        return false;/*!< no agent present so did nothing */
    }
}


/**
 * Pick a random empty location within our neighbourhood as defined by our vision
 * @param loc :Our location
 * @see Move Rule
 * @return Our chosen location held in a group object (or nullPtr if we have no move
 * @exception none
 */
group* AgentBasicMove::formGroup(Location *loc)
{
    group *ourChoice = nullptr;
    if (loc->hasAgent()) {//Agent at this location
        Agent* theAgent=loc->getAgent();
        //find all empty locations
        std::vector<Location*> possibleDestinations=sim->getEmptyNeighbourhood(theAgent->getPosition().first, theAgent->getPosition().second, theAgent->getVision());
        if (possibleDestinations.size()!=0) {/*!< check to see if we can move anywhere */
            ourChoice = new group();
            int index=sim->getRnd(0,(int)possibleDestinations.size());//pick random location
            ourChoice->push_back(possibleDestinations[index]);
            int rank=possibleDestinations[index]->getPosition().first-theAgent->getPosition().first
                    +possibleDestinations[index]->getPosition().second-theAgent->getPosition().second;
            if (rank<0) rank+=theAgent->getVision();
            else rank -=theAgent->getVision();
            ourChoice->setRank(rank);
        }
        
    }
    return ourChoice;/*!< is NOT nullPtr only if we assigned it a value earlier */
}
