//
//  Location.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 25/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "Location.h"


//constructors
Location::Location(World *theWorld):
    deadAgent(nullptr),newResident(nullptr),currentResident(nullptr),
    currentPollution(0),newPollution(0),done(false),
    newSugar(0),position(nullPosition),sim(theWorld)
{
    if (sim!=nullptr) {
        maxSugar=sim->getRnd(sim->getInitialSugarMin(), sim->getInitialSugarMax());
        currentSugar=sim->getRnd(sim->getInitialSugarMin(), maxSugar);
    }else{
        maxSugar=0;
        currentSugar=0;
    }
}

Location::Location(int x,int y):
    done(false),deadAgent(nullptr),newResident(nullptr),currentResident(nullptr),
    currentPollution(0),newPollution(0),
newSugar(0),position(std::make_pair(x, y))
{
    if (sim!=nullptr) {
        maxSugar=sim->getRnd(sim->getInitialSugarMin(), sim->getInitialSugarMax());
        currentSugar=sim->getRnd(sim->getInitialSugarMin(), maxSugar);
    }else{
        maxSugar=0;
        currentSugar=0;
    }
}

//Destructor
Location::~Location(){//remove agent pointers if any exist
    if (deadAgent!=nullptr) {
        delete deadAgent;
    }
    if (currentResident==newResident) {
        if (currentResident!=nullptr) {
            delete currentResident;
        }
    }
    else {
        if (currentResident!=nullptr) {
            delete currentResident;
        }
        if (newResident!=nullptr) {
            delete newResident;
        }
    }
}

//getters
bool Location::isDone(void){
    return done;
}
std::pair<int,int> Location::getPosition(void){
    return position;
}
int Location::getX(void){
    return position.first;
}
int Location::getY(void){
    return position.second;
}
int Location::getSugar(void){
    return currentSugar;
}
int Location::getWealth(void){
    return currentSugar;
}
int Location::getReward(void){
    if (currentResident!=nullptr) {
        return this->getWealth()+currentResident->getReward();
    } else {
        return this->getWealth();
    }
}
int Location::getMaxSugar(void){
    return maxSugar;
}
int Location::getPollution(void){
    return currentPollution;
}
Agent* Location::getAgent(void){
    return currentResident;
}
//setters
std::pair<int,int> Location::setPosition(std::pair<int,int> newPosition){
    if (position==nullPosition) {
        position=newPosition;
    }
    return position;
}
int Location::setX(int x){
    if (position.first==-1){
        position.first=x;
    }
    return position.first;
}
int Location::setY(int y){
    if (position.second==-1) {
        position.second=y;
    }
    return position.second;
}
int Location::setSugar(int newAmount){
    newSugar=newAmount;
    if (newSugar>maxSugar){
        newSugar=maxSugar;
    }
    return newSugar;
}
int Location::setMaxSugar(int newMax){
    if (maxSugar==0) {
        maxSugar=newMax;
    }
    return maxSugar;
}
int Location::setPollution(int newAmount){
    newPollution=newAmount;
    return newPollution;
}

Agent* Location::setAgent(Agent* newAgent){
    newResident=newAgent;
    return newResident;
}

/**
 * Change pointer to world -Why would we ever do this??
 * @param theWorld
 * @return pointer to old world object
 * @exception none
 */
World* Location::setWorld(World* theWorld){
    World* old=sim;
    sim=theWorld;
    return old;
}



//******************HELPERS***********************

/**
 * Mark us done
 * @return true
 * @exception none
 */
bool Location::markDone(void){
    return done=true;
}

/**
 * do we have an agent here?
 * @return true if we have an agent here else false
 * @exception none
 */
bool Location::hasAgent(void){
    return currentResident!=nullptr;
}

/**
 * Kill agent at this location
 * @return pointer to killed agent (nullptr if none)
 * @exception none
 */
Agent* Location::killAgent(void)
{
    newResident=nullptr;
    return deadAgent=currentResident;
}

/**
 * returns true if we have a dead agent waiting to be deleted
 * @return true if there is a dead agent
 * @exception none
 */
bool Location::hasDeadAgent()
{
    return deadAgent!=nullptr;
}

/**
 * Returns location N,S,E or W.
 * @param direction :integer 0..3 for cardinal directions
 * @return Location in direction we wanted
 * @exception none *ADD EXCEPTION HERE*
 */
Location* Location::getCardinal(int direction){
    switch (direction) {
        case 0:
            return sim->getLocation(std::pair<int,int>(position.first-1,position.second));
            break;
        case 1:
            return sim->getLocation(std::pair<int,int>(position.first+1,position.second));
            break;
        case 2:
            return sim->getLocation(std::pair<int,int>(position.first,position.second+1));
            break;
        case 3:
            return sim->getLocation(std::pair<int,int>(position.first,position.second-1));
            break;
        default:
            std::cerr << "cardinal called with value "<< direction << std::endl;
            break;
    }
    return nullptr;
}

/**
 * deletes dead agents - Not required. Done in sync
 * @return true if dead agent was removed else if no dead agent then false
 * @exception none
 */
bool Location::putOutGarbage(void)
{
    if (deadAgent!=nullptr) {
        delete deadAgent;
        deadAgent=nullptr;
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * initAgent Used to initialise a location with an agent. Use only when initialising locationd
 * @param InitialAgent :Pointer to new agent
 * @return true
 * @exception none
 */
bool Location::initAgent(Agent * InitialAgent){
    currentResident=newResident=InitialAgent;
    return true;
}

/**
 * Synchronises all updates. deletes agents that are dead
 * @return true
 * @exception none
 */
bool Location::sync(void){
    done=false;
    currentPollution=newPollution;
    currentSugar=newSugar;
    currentResident=newResident;
    if (deadAgent!=nullptr) {
        delete deadAgent;
        deadAgent=nullptr;
    }
    return true;
}
