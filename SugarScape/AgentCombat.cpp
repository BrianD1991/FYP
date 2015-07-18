//
//  AgentCombat.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 16/07/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "AgentCombat.h"



bool combatCompare(Location *a, Location *b)
{
    return a->getReward()>b->getReward();
}


AgentCombat::AgentCombat(World *s)
:AgentMove(s)
{
    //our work is done
}


//1. DOES NOT REMOVE LINKS TO DEAD AGENTS!
bool AgentCombat::executeAction(Location *loc, group *grp)
{
    if (loc->hasAgent()) {
        if (grp!=nullptr)//nullptr should not be possible
        {
            //1. Update victorious agent resources
            Agent *winner = grp->getPrimeMover()->getAgent(); //must equal loc->getAgent()!
            Agent *loser = grp->getMembers()[0]->getAgent();//only one member in group - the loser
            winner->incSugar(std::min(loser->getReward(),sim->getCombatLimit()));//WHAT IF WE ADD SPICE?
            //2. Kill vanquished agent
            std::pair<int,int> currPosition=loser->getPosition();
            if (loser!=sim->killAgent(currPosition.first, currPosition.second))
            {
                std::cerr << "Delete of agent failed"<<std::endl;
            }
            //3. Move victorous agent to new position
            currPosition=winner->getPosition();
            sim->setAgent(currPosition.first, currPosition.second, nullptr);//remove old location ptr to agent
            winner->setPosition(loser->getPosition());//set new position to new location
            sim->setAgent(loser->getPosition().first,loser->getPosition().second,winner);//add ptr to agent at new location
            //4. Remove any links to killed agents
        }
        else{
            std::cerr << " nullptr in executeAction combat"<<std::endl;
        }
        return true;
    }else{
        return false;/*!< no agent present so did nothing */
    }
}


int AgentCombat::pickIndex(std::vector<Location*> possibles,Agent *me)
{//find a winner
    //Find out if there is going to be retaliation
    //1. get meanest opponent in list
    int strongestEnemy=0;
    for(auto loc:possibles){
        if (loc->hasAgent()) {
            if (strongestEnemy<loc->getAgent()->getReward()) {
                strongestEnemy=loc->getAgent()->getReward();
            }
        }
    }
    //2. Sort list by desirability
    std::sort(possibles.begin(),possibles.end(),combatCompare);
    for (int i=0; i<possibles.size(); ++i) {
        if (possibles[i]->hasAgent()==false) {
            return i;//found index of empty space
        }else{//has agent so check for combat
            if (possibles[i]->getReward()+ me->getWealth() > strongestEnemy) {
                return i;
            } else {
                return -1;//all others are worst than strongest opponent (list is sorted!)
            }
        }
    }
    return -1;
}


group* AgentCombat::formGroup(Location *loc)
{
    
    group *ourChoice = nullptr;
    if (loc->hasAgent()) {//Agent at this location
        Agent* theAgent=loc->getAgent();
        //find all empty locations
        
        std::vector<Location*> possibleLocations=sim->getCombatNeighbourhood(theAgent->getPosition().first, theAgent->getPosition().second, theAgent->getVision());
        ourChoice = new group();
        if (possibleLocations.size()!=0) {/*!< check to see if we can move anywhere */
            int index=pickIndex(possibleLocations, theAgent);
            if (index>-1) {//we have a winner -- from group
                ourChoice->push_back(sim->getLocation(possibleLocations[index]->getPosition()));
                int rank=possibleLocations[index]->getPosition().first-theAgent->getPosition().first
                +possibleLocations[index]->getPosition().second-theAgent->getPosition().second;
                if (rank<0) rank =-rank;
                ourChoice->setRank(rank);
                ourChoice->setPrimeMover(loc);
                ourChoice->setActiveParticipants(1);//one active participant per group - the agent moving
            }
        }
    }
    return ourChoice;/*!< is NOT nullPtr only if we assigned it a value earlier */
}


