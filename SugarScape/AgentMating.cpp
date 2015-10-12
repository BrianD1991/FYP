//
//  AgentMating.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 20/07/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "AgentMating.h"


AgentMating::AgentMating(World *sim)
:IterativeWriteAction(sim)
{
    //our work is done
}



bool AgentMating::executeAction(Location *loc, group *grp)
{
    if (loc->hasAgent()) {
        Agent* theMale=loc->getAgent();
        if (grp->getMembers().size()==2) {
            std::pair<int,int> newPosition=grp->getMembers()[1]->getPosition();/*!< second in group is empty location */
            Agent *theFemale=grp->getMembers()[0]->getAgent();/*!< first in group is female agent*/
            Agent *offSpring= new Agent(sim,theMale,theFemale,newPosition);
            sim->setAgent(newPosition, offSpring);/*!< Put offspring in empty location */
            offSpring->incSugar(grp->getMembers()[1]->getSugar());/*!< eat sugar at new location */
            //offSpring->incSugar(theMale->getSugar()/2);
            //theMale->incSugar(-theMale->getSugar()/2);
            //offSpring->incSugar(theFemale->getSugar()/2);
            //theFemale->incSugar(-theFemale->getSugar()/2);
            offSpring->makeUnavailable();
            grp->getMembers()[1]->setSugar(0);/*!< sugar at new location now consumed */
            
            if (loc->getCardinal(0)->getAgent()==theFemale) {
                theMale->markNeighbour(0);
            } else if(loc->getCardinal(1)->getAgent()==theFemale){
                theMale->markNeighbour(1);
            } else if (loc->getCardinal(2)->getAgent()==theFemale){
                theMale->markNeighbour(2);
            }else if (loc->getCardinal(3)->getAgent()==theFemale){
                theMale->markNeighbour(3);
            }else{
                std::cerr <<"MATING CANNOT FIND FEMALE"<<std::endl;
            }
            return true;
        }else{
            return false;/*!< group has no female or no location so no matting here */
        }
    }else{
        std::cerr << "exectued mating on location with no agent! " << std::endl;
        return false;/*!< no agent present so do nothing */
    }

}


/**
 formGroup forms group of male and female agent and location for offspring
 
 returns nullptr if location is empty or contains a female agent.
 Otherwise it returns a group contaiing a free location and a female agent location.
 If there are no available mates or locations for offspring then return a group 
 containing only the male agent.
 
 @param loc :location we are forming group for
 @returns pointer to group or nullptr
 @exception none
 */
group* AgentMating::formGroup(Location *loc)
{
    if (loc->hasAgent()) {
        if (loc->getAgent()->getSex()==Sex::male) {
            Agent *me=loc->getAgent();
            Agent *mate=nullptr;
            group *grp= new group();/*!< create group */
            grp->setRank(1);
            grp->setActiveParticipants(1);
            grp->setPrimeMover(loc);
            for (int i=0; i<4 && mate==nullptr; ++i) {/*!< find mate first */

                if (me->getAvail(i) && suitable(loc->getCardinal(i))==true) {
                    mate=loc->getCardinal(i)->getAgent();
                }
                me->markNeighbour(i);
            }
            if (mate==nullptr) {/*!< no mate available return empty group */
                return grp;
            }
            std::vector<Location*> destinations=sim->getEmptyNeighbourhood(me->getPosition(),1);/*!< get empty locations around me for offspring */
            std::vector<Location*> moreDestinations=sim->getEmptyNeighbourhood(mate->getPosition(),1);/*!< get more empty locations around mate for offspring */
            destinations.insert(destinations.end(),moreDestinations.begin(),moreDestinations.end());/*!< combine location vectors */
            for (auto it = destinations.begin(); it != destinations.end();) {/*!< remove slots that are taken (done!)*/
                if ((*it)->isDone()) {
                    it = destinations.erase( it ); // reset iterator to a valid value post-erase
                }
                else {
                        ++it;
                }
            }
            if (destinations.size()==0) {/*!< nowhere for offspring beside me or mate so return empty group */
                return grp;
            }
            grp->push_back(mate->getLocation());/*!< if I get here then all is fine create group */
            grp->push_back(destinations[0]);
            return grp;
        }
    }
    return nullptr;//no male agent here so do nothing

}


/**
 participationCount
 
 We only count male agents as participants for this rule
 @param startX :x-coordinate of top left of grid
 @param startY :y-coordinate of top left of grid
  @param dimSize :width and height of grid
 @returns number of participants as int
 @exception none
 */
int AgentMating::participantCount(int startX, int startY, int dimSize)
{
    int pcount=0;
    Agent *theAgent=nullptr;
#pragma omp parallel for private(theAgent)
    for (int i=startX; i<startX+dimSize; ++i) {
        for (int k=startY; k<startY+dimSize; ++k) {
            theAgent=sim->getAgent(std::pair<int,int>(i, k));
            if (theAgent!=nullptr) {
                if (theAgent->getSex()==Sex::male && theAgent->allDone()==false){
                    ++pcount;
                }
            }
        }
    }
    return pcount;
}

bool AgentMating::suitable(Location *loc){
    if (loc->hasAgent() && loc->getAgent()->getSex()==Sex::female) {
        return true;
    }
    return false;
}



