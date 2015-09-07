//
//  Location.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 25/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "Location.h"



/**
 * default constructor
 * @param theWorld (pointer to world (default nulptr)
 * @param pos :coordinates of location (default nullPosition)
 * @param y :y coordinate of location (default -1)
 * @return none
 * @exception none
 */
Location::Location(World *theWorld, std::pair<int,int> pos):
    deadAgent(nullptr),newResident(nullptr),currentResident(nullptr),
    currentPollution(0),newPollution(0),done(false),
    newSugar(0),position(pos),sim(theWorld)
{
    if (sim!=nullptr) {
        maxSugar=sim->getRnd(sim->getInitialSugarMin(), sim->getInitialSugarMax());
        currentSugar=sim->getRnd(sim->getInitialSugarMin(), maxSugar);
    }else{
        maxSugar=0;
        currentSugar=0;
    }
}



/**
 * Destructor - Deletes Agent pointer at location
 * @return none
 * @exception none
 */
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

//****************************GETTERS**********************************

/**
 * return true if location is done
 * @return done
 * @exception none
 */
bool Location::isDone(void){
    return done;
}

/**
 * return position of location
 * @return coordinate as std::pair
 * @exception none
 */
std::pair<int,int> Location::getPosition(void){
    return position;
}

/**
 * return X-position of location
 * @return X-coordinate
 * @exception none
 */
int Location::getX(void){
    return position.first;
}

/**
 * return Y-position of location
 * @return Y-coordinate
 * @exception none
 */
int Location::getY(void){
    return position.second;
}

/**
 * return sugar at location
 * @return sugar level
 * @exception none
 */
int Location::getSugar(void){
    return currentSugar;
}

/**
 * return wealth at location
 * @return sugar level
 * @exception none
 */
int Location::getWealth(void){
    return currentSugar;
}

/**
 * returns reward for site (wealth +resident agent reward
 * @see AgentCombat Rule
 * @return reward level
 * @exception none
 */
int Location::getReward(void){
    if (currentResident!=nullptr) {
        return this->getWealth()+currentResident->getReward();
    } else {
        return this->getWealth();
    }
}

/**
 * return max allowed sugar level at location
 * @return max sugar level
 * @exception none
 */
int Location::getMaxSugar(void){
    return maxSugar;
}

/**
 * return pollution level at location if exists
 * @return pollution level
 * @exception none
 */
int Location::getPollution(void){
    return currentPollution;
}

/**
 * return agent at location if exists
 * @return pointer to agent (or nullptr)
 * @exception none
 */
Agent* Location::getAgent(void){
    return currentResident;
}
//*************************SETTERS***************************************


/**
 * set position of location (can only be done if not already set)
 * @param newPosition std::pair -- x and y coordinates
 * @return new position coordinates
 * @exception none
 */
std::pair<int,int> Location::setPosition(std::pair<int,int> newPosition){
    if (position==nullPosition) {
        position=newPosition;
    }
    return position;
}

/**
 * Set location X coordinate (only works if not already set)
 * @param x
 * @return new x value
 * @exception none
 */
int Location::setX(int x){
    if (position.first==-1){
        position.first=x;
    }
    return position.first;
}

/**
 * Set location Y coordinate (only works if not already set)
 * @param y
 * @return new y value
 * @exception none
 */
int Location::setY(int y){
    if (position.second==-1) {
        position.second=y;
    }
    return position.second;
}

/**
 * Update Sugar level (up to maxSugar)
 * @param newAmount
 * @return new Sugar level
 * @exception none
 */
int Location::setSugar(int newAmount){
    newSugar=newAmount;
    if (newSugar>maxSugar){
        newSugar=maxSugar;
    }
    return newSugar;
}

/**
 * Set new maximum sugar level for location. Can only be updated if not already set
 * @param newMax
 * @return max sugar level
 * @exception none
 */
int Location::setMaxSugar(int newMax){
    if (maxSugar==0) {
        maxSugar=newMax;
    }
    return maxSugar;
}

/**
 * update pollution value
 * @param newAmount
 * @return current (old) Pollution level
 * @exception none
 */
int Location::setPollution(int newAmount){
    newPollution=newAmount;
    return currentPollution;
}

/**
 * put new agent at this location
 * @param newAgent (pointer)
 * @return pointer to agent being replaced (or nullptr)
 * @exception none
 */
Agent* Location::setAgent(Agent* newAgent){
    newResident=newAgent;
    return currentResident;
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
