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

/**
 * Constructor - passes World pointer to parent constructor
 * @param s :Pointer to World
 * @return none
 * @exception none
 */
AgentCombat::AgentCombat(World *s)
:AgentMove(s)
{
    //our work is done
}


/**
 * Agent removes agent in location in group from world and takes resources
 * It also removes links to agents killed by combat (lenders, borrowers, etc.)
 * @param loc :Pointer to Location of the winning agent
 * @param grp : Pointer to Group containing location of losing agent (or possibly an empty location)
 * @see Combat Rule
 * @return true if agent exists at loc else false
 * @exception none
 */
bool AgentCombat::executeAction(Location *loc, group *grp)
{
    if (loc->hasAgent()) {
        Agent *winner = grp->getPrimeMover()->getAgent(); //must equal loc->getAgent()!
        if (grp->getMembers().size()!=0)/*!< we are moving somewhere */
        {
            if (grp->getMembers()[0]->hasAgent()==false) {/*!< moving to empty location */
                loc->getAgent()->incSugar(grp->getMembers()[0]->getSugar());/*!< eat sugar at destination */
                grp->getMembers()[0]->setSugar(0);/*!< sugar at location is consumed */
            }
            else{
                //std::cout <<"COMBAT!"<<std::endl;
                //1. Update victorious agent resources
                Agent *loser = grp->getMembers()[0]->getAgent();//only one member in group - the loser
                winner->incSugar(grp->getMembers()[0]->getReward());//*WHAT IF WE ADD SPICE?*
                grp->getMembers()[0]->setSugar(0);/*!< sugar at location is consumed */
                //2. Kill vanquished agent
                std::pair<int,int> currPosition=loser->getPosition();
                if (loser!=sim->killAgent(currPosition))
                {
                    std::cerr << "Delete of agent failed"<<std::endl;
                }
            }
            //Move agent to new position
            std::pair<int,int> currPosition=winner->getPosition();
            sim->setAgent(currPosition, nullptr);//remove old location ptr to agent
            winner->setPosition(grp->getMembers()[0]->getPosition());//set new position to new location
            sim->setAgent(grp->getMembers()[0]->getPosition(),winner);//add ptr to agent at new location
        }
        else{/*!< we are staying put-not moving */
            loc->getAgent()->incSugar(loc->getSugar());/*!< eat sugar at destination */
            loc->setSugar(0);/*!< sugar at location is consumed */
        }
        for(auto ag:winner->getChildren())/*!< Remove any links to killed children */
        {
            if (ag->isKilled()) {
                winner->removeChild(ag);
            }
        }
        winner->removeKilledLoans();/*!< remove loans with killed agents */
        winner->removeKilledFather();/*!< remove father link if he is killed */
        winner->removeKilledMother();/*!< remove mother link if she is killed */
        return true;
    }else{
        return false;/*!< no agent present so did nothing */
    }
}


/**
 * Picks the agent we want to attack if any, or otherwise an empty location to move to
 * @param possibles : list containing al possible destinations
 * @param me : the Agent making the move
 * @see Combat Rule
 * @return index of destination from list (std::vector)
 * @exception none
 */
int AgentCombat::pickIndex(std::vector<Location*> possibles,Agent *me)
{//find a winner
    //Find out if there is going to be retaliation
    //1. get meanest opponent in list
    int strongestEnemy=0;
    for(auto loc:possibles){
        if (loc->hasAgent()) {
            if (strongestEnemy < loc->getAgent()->getReward()) {
                strongestEnemy = loc->getAgent()->getReward();
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
            }
        }
    }
    return -1;
}


/**
 * Creates the group containing the vistim we are attacking or empty location we are moving to
 * @param loc :pointer to our location
 * @see Combat Rule
 * @return pointer to group object
 * @exception none
 */
group* AgentCombat::formGroup(Location *loc)
{
    if (loc->hasAgent() && loc->isDone()==false) {/*!< Agent at this location */
        group *ourChoice = nullptr;
        Agent* theAgent=loc->getAgent();
        std::vector<Location*> possibleLocations=sim->getCombatNeighbourhood(theAgent->getPosition(), theAgent->getVision());/*!< Find all possible destinations */
        ourChoice = new group();
        if (possibleLocations.size()!=0) {/*!< check to see if we can move anywhere */
            int index=pickIndex(possibleLocations, theAgent);
            if (index>-1) {//we have a winner -- form  a group
                ourChoice->push_back(possibleLocations[index]);
                                     //sim->getLocation(possibleLocations[index]->getPosition()));
                int rank=possibleLocations[index]->getPosition().first-theAgent->getPosition().first
                +possibleLocations[index]->getPosition().second-theAgent->getPosition().second;
                if (rank<0) rank =-rank;
                ourChoice->setRank(rank);
                ourChoice->setPrimeMover(loc);
                if (possibleLocations[index]->hasAgent()) {
                    ourChoice->setActiveParticipants(2);/*!< have killed agent therefore two participants here */
                }else{
                    ourChoice->setActiveParticipants(1);//one active participant in group - the agent moving
                }
            }
            else{/*!< cannot find anywhere safe to move so stay here */

                ourChoice->setRank(0);
                ourChoice->setPrimeMover(loc);
                ourChoice->setActiveParticipants(1);
            }
        }else{/*!< everywhere is occupied so stay here */
            ourChoice->setRank(0);
            ourChoice->setPrimeMover(loc);
            ourChoice->setActiveParticipants(1);
        }
        return ourChoice;
    }
    return nullptr;/*!< No agent here do nothing */
}


