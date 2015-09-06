//
//  Agent.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//
#include "World.h"

#include "Agent.h"

//Constructors

/**
 * Constructor, lots to set up
 * @param s :Pointer to World Object
 * @param dad :Male parent of Agent
 * @param mum :Female parent of Agent
 * @param pos :Position of Agent in Lattice
 * @return none
 * @exception none
 */
Agent::Agent(World *s,Agent *dad, Agent *mum, std::pair<int,int> pos):amountEaten(0), done(false),
    father(dad),mother(mum),killed(false),newPosition(pos),currentPosition(pos),
    theWorld(s),currentAge(0),newAge(1),vision(2),
    cultureLength(s->getCultureCount()),immunityLength(s->getImmunityLength())
{
    if (dad==nullptr) {
        newSugar=currentSugar=theWorld->getRnd(0, theWorld->getInitialSugarMax());
        newSpice=currentSpice=theWorld->getRnd(0, theWorld->getInitialSpiceMax() );
        maxAge=theWorld->getRnd(theWorld->getMinAge(), theWorld->getMaxAge());
        currentMetabolism=newMetabolism=theWorld->getRnd(theWorld->getMinMetabolism(),theWorld->getMaxMetabolism());
        //currentSpiceMetabolism=newSpiceMetabolism=theWorld->getRnd(theWorld->getMinSpiceMetabolism(),theWorld->getMaxSpiceMetabolism());
    }
    else{
        newSugar=currentSugar=theWorld->getRnd(0, theWorld->getInitialSugarMax());
        newSpice=currentSpice=theWorld->getRnd(0, theWorld->getInitialSpiceMax() );
        maxAge=theWorld->getRnd(theWorld->getMinAge(), dad->getMaxAge());
        currentMetabolism=newMetabolism=theWorld->getRnd(theWorld->getMinMetabolism(),mum->getMetabolism());
        //currentSpiceMetabolism=newSpiceMetabolism=theWorld->getRnd(theWorld->getMinSpiceMetabolism(),mum->getSpiceMetabolism());
    }
    if (theWorld->getRnd(0,1)==0) {
        sex=Sex::male;
    }else{
        sex=Sex::female;
    }
    
    cultureLength=theWorld->getCultureCount();
    immunityLength=theWorld->getImmunityLength();
    diseaseLength=theWorld->getDiseaseLength();
    /*!< Create random immunity */
    for (int i=0; i<immunityLength; ++i) {
        bool aBit=false;
        if (theWorld->getRnd(0, 10)>=5) {
            aBit=true;
        }
        currentImmunity.push_back(aBit);
        newImmunity.push_back(aBit);
    }
    /*!< Create random culture */
    for (int i=0; i<cultureLength; ++i) {
        bool aBit=false;
        if (theWorld->getRnd(0, 10)>=5) {
            aBit=true;
        }
        currentCulture.push_back(aBit);
        newCulture.push_back(aBit);
    }
    /*!< Create random disease */
    std::vector<bool> newDisease;
    for (int i=0; i<diseaseLength; ++i) {
        bool aBit=false;
        if (theWorld->getRnd(0, 10)>=5) {
            aBit=true;
        }
        newDisease.push_back(aBit);
    }
    currentDiseases.push_back(newDisease);
    newDiseases.push_back(newDisease);
}



//getters

/**
 * Returns true if there is ana vailable agent in the given direction
 * @param direction :Int from 0 to 3 indicating direction
 * @see iterativeWriteAction
 * @return true if agent in that direction is available
 * @exception none *NEED TO ADD EXCEPTION HERE*
 */
bool Agent::getAvail(int direction){
    if (direction>=0 && direction<=3) {
        return availableNeighbours[direction];
    }
    return false;
}

/**
 * Returns amount eaten - used by pollution formation rule
 * @see PollutionFormation
 * @return amount eaten by agent during step
 * @exception none
 */
int Agent::getAmountEaten(void){
    return amountEaten;
}

/**
 * Tells if agent has completed action, or is booked, for this step
 * @see Action run method
 * @return true if done else false
 * @exception none
 */
bool Agent::isDone(void){
    return done;
}

/**
 * gets current position

 * @return std::pair with position in lattice of agent
 * @exception none
 */
std::pair<int, int> Agent::getPosition(void){
    return currentPosition;
}

/**
 * returns sex of Agent
 * @return sex
 * @exception none
 */
Sex Agent::getSex(void){
    return sex;
}

/**
 * Returns length of vision of agent
 * @return int - value of vision
 * @exception none
 */
int Agent::getVision(void){
    return vision;
}

/**
 * Returns Age of agent
 * @return int - value of age
 * @exception none
 */
int Agent::getAge(void){
    return currentAge;
}

/**
 * Returns Maximum allowable age of agent
 * @return int - value of max age
 * @exception none
 */
int Agent::getMaxAge(void){
    return maxAge;
}

/**
 * Returns Sugar Metabolism of agent
 * @return int - value of sugar metabolism
 * @exception none
 */
int Agent::getMetabolism(void){
    return currentMetabolism;
}

/**
 * Returns Spice Metabolism of agent
 * @return int - value of spice metabolism
 * @exception none
 */
int Agent::getSpiceMetabolism(void){
    return currentSpiceMetabolism;
}

/**
 * Returns Amount of Sugar held by agent
 * @return int - value of Sugar reserves
 * @exception none
 */
int Agent::getSugar(void){
    return currentSugar;
}

/**
 * Returns Amount of Spice held by agent
 * @return int - value of Spice reserves
 * @exception none
 */
int Agent::getSpice(void){
    return currentSpice;
}

/**
 * Returns Combined amount of Sugar and Spice held by agent
 * @return int - value of Sugar+spice reserves
 * @exception none
 */
int Agent::getWealth(void){
    return currentSugar+currentSpice;
}

/**
 * Returns Reward for killing agent
 * @return int - Maximum of agent wealth and COmbat limit
 * @exception none
 */
int Agent::getReward(void){
    return std::min(this->getWealth(),theWorld->getCombatLimit());
}

/**
 * Returns Number of culture tags held by agent
 * @return int - length of culture vector
 * @exception none
 */
int Agent::getCultureLength(void){
    return cultureLength;
}

/**
 * Returns Number of Immunity tags held by agent
 * @return int - length of immunity vector
 * @exception none
 */
int Agent::getImmunityLength(void){
    return immunityLength;
}


/**
 * Returns Number of children of agent
 * @return int - size of currentChildren vector
 * @exception none
 */
unsigned long Agent::getChildrenCount()
{
    return currentChildren.size();
}

/**
 * Returns pointer to father of agent
 * @return Agent* --nullptr if no father else pointer to father
 * @exception none
 */
Agent* Agent::getFather()
{
    return father;
}

/**
 * Returns pointer to mother of agent
 * @return Agent* --nullptr if no mother else pointer to mother
 * @exception none
 */
Agent* Agent::getMother()
{
    return mother;
}


/**
 * Returns culture of agent
 * @return vector containing culture tags
 * @exception none
 */
std::vector<bool> Agent::getCulture(void){
    return currentCulture;
}

/**
 * Returns immunity of agent
 * @return vector containing immunity tags
 * @exception none
 */
std::vector<bool> Agent::getImmunity(void){
    return currentImmunity;
}

/**
 * Returns children of agent
 * @return vector containing children
 * @exception none
 */
std::vector<Agent*> Agent::getChildren(void){
    return currentChildren;
}

/**
 * Returns loans owed *by* agent
 * @return vector containing loans owed
 * @exception none
 */
std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::getLoansOwed(void){
    return currentLoansOwed;
}

/**
 * Returns loans owed *to* agent
 * @return vector containing loans owing to us
 * @exception none
 */
std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::getLoansOwing(void){
    return currentLoansOwing;
}


/**
 * Returns diseases caught by agent
 * @return vector containing diseases
 * @exception none
 */
std::vector<std::vector<bool>> Agent::getDiseases(void){
    return currentDiseases;
}

/**
 * Returns location of agent
 * @return pointer to location object
 * @exception none
 */
Location* Agent::getLocation(void){
    return theWorld->getLocation(currentPosition);
}




//***********************************SETTERS***********************************


/**
 * marks neighbour in given direction as done
 * @param direction :int (0 to 3) indicating direction
 * @see iterativeWriteAction
 * @return true if direction is ok
 * @exception none *ADD EXCEPTION HERE*
 */
bool Agent::markNeighbour(int direction)
{
    if (0<=direction && 4>direction) {
        availableNeighbours[direction]=false;
        return true;
    }else{
        return false;
    }
    
}

/**
 * sets agent to new position - handles wraparound properly
 * @param destination std::pair containing new position
 * @return new position
 * @exception none
 */
std::pair<int, int> Agent::setPosition(std::pair<int, int> destination){
    newPosition.first=theWorld->wrap(destination.first);
    newPosition.second=theWorld->wrap(destination.second);
    return newPosition;
}

/**
 * sets sex of agent, only works if sex is not already set
 * @param sex
 * @return new sex
 * @exception none
 */
Sex Agent::setSex(Sex newSex){
    if (sex==Sex::unknown) sex=newSex;
    return sex;
}

/**
 * sets vision of agent, only works if vision is not already set
 * @param newvision
 * @return new vision value
 * @exception none
 */
int Agent::setVision(int newVision){
    if (vision==-1) {
        vision=newVision;
    }
    return newVision;
}

/**
 * increments agent age
 * @return new age
 * @exception none
 */
int Agent::incAge(void){
    return ++currentAge;
}

/**
 * increments agent age by any amount
 * @return new age
 * @exception none *NEED TO ADD EXCEPTION*
 */
int Agent::setAge(int newAmount){
    if (newAmount>=0) {
        currentAge=newAmount;
    }
    return currentAge;
}

/**
 * sets maximum age of agent, only works if maximum age is not already set
 * @param newMax
 * @return maxAge value
 * @exception none
 */
int Agent::setMaxAge(int newMax){
    if (maxAge==-1) {
        maxAge=newMax;
    }
    return maxAge;
}

/**
 * sets sugar metabolism of agent
 * @param newAmount
 * @return newMetabolism value
 * @exception none
 */
int Agent::setMetabolism(int newAmount){
    if (newAmount>=0) {
        newMetabolism=newAmount;
    }
    return newMetabolism;
}


/**
 * sets spice metabolism of agent
 * @param newAmount
 * @return newMetabolism value
 * @exception none
 */
int Agent::setSpiceMetabolism(int newAmount){
    if (newAmount>=0) {
        newSpiceMetabolism=newAmount;
    }
    return newSpiceMetabolism;
}

/**
 * Adds Sugar to reserves held by agent
 * @param extraSugar
 * @return new Sugar reserves
 * @exception none
 */
int Agent::incSugar(int extraSugar){
    newSugar+=extraSugar;
    return newSugar;
}

/**
 * Adds Spice to reserves held by agent
 * @param extraSpice
 * @return new Spice reserves
 * @exception none
 */
int Agent::incSpice(int extraSpice){
    newSpice+=extraSpice;
    return newSpice;
}

/**
 * Sets Sugar reserves held by agent to a new amount
 * @param newAmount
 * @return new Sugar reserves
 * @exception none
 */
int Agent::setSugar(int newAmount){
    newSugar=newAmount;
    return newSugar;
}

/**
 * Sets Spice reserves held by agent to a new amount
 * @param newAmount
 * @return new Spice reserves
 * @exception none
 */
int Agent::setSpice(int newAmount){
    newSpice=newAmount;
    return newSpice;
}

/**
 * Sets culture length to a new amount
 * @param newAmount
 * @return new culture length
 * @exception none
 */
int Agent::setCultureLength(int newAmount){
    if (newAmount>=0) {
        cultureLength=newAmount;
    }
    return cultureLength;
}

/**
 * Sets immunity length to a new amount
 * @param newAmount
 * @return new immunity length
 * @exception none
 */
int Agent::setImmunityLength(int newAmount){
    if (newAmount>=0) {
        immunityLength=newAmount;
    }
    return immunityLength;
}

/**
 * Set a specific tag to new value
 * @param newValue
 * @param index
 * @see Disease Rule
 * @return index of new tag if ok else -1
 * @exception none *ADD EXCEPTION HERE*
 */
int Agent::setImmunityTag(bool newValue,int index){
    if (index>=0 && index<newImmunity.size()) {
        newImmunity[index]=newValue;
        return index;
    }
    return -1;
}

/**
 * Replaces culture of agent with new culture. Not used but you never know!
 * @param replacementCulture
 * @return new culture vector
 * @exception none
 */
std::vector<bool> Agent::setCulture(std::vector<bool> replacementCulture){
    newCulture=replacementCulture;
    return newCulture;
}

/**
 * Replaces immunity of agent with new immunity. Not used but you never know!
 * @param replacementImmunity
 * @return new immunity vector
 * @exception none
 */
std::vector<bool> Agent::setImmunity(std::vector<bool> replacementImmunity){
    newImmunity=replacementImmunity;
    return newImmunity;
}

/**
 * Replaces children of agent with new children. Not used but you never know!
 * @param replacementChildren
 * @return new children vector
 * @exception none
 */
std::vector<Agent*> Agent::setChildren(std::vector<Agent*>replacementChildren){
    newChildren=replacementChildren;
    return newChildren;
}

/**
 * Replaces loans owed *TO* agent with new loans owed. Not used but you never know!
 * @param replacementLoansOwed
 * @return new loans owed vector
 * @exception none
 */
std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::setLoansOwed(std::vector<std::pair<Agent*,std::pair<int, int>>> replacementLoansOwed){
    newLoansOwed=replacementLoansOwed;
    return newLoansOwed;
}


/**
 * Replaces loans owed *BY* agent with new loans owed *BY* agent. Not used but you never know!
 * @param replacementLoansOwing
 * @return new loans owing vector
 * @exception none
 */
std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::setLoansOwing(std::vector<std::pair<Agent*,std::pair<int, int>>> replacementLoansOwing){
    newLoansOwing=replacementLoansOwing;
    return newLoansOwing;
}


/**
 * Replaces diseases caught by agent with diseases. Not used but you never know!
 * @param replacementDiseases
 * @return new diseases vector
 * @exception none
 */
std::vector<std::vector<bool>> Agent::setDiseases(std::vector<std::vector<bool>> replacementDiseases){
    newDiseases=replacementDiseases;
    return newDiseases;
}




//*********************** HELPERS ***********************************************

/**
 * Initialise some values in existing agent: Not used as yet
 * @param sim :pointer to world
 * @param dad :pointer to male parent
 * @param mum :pointer to female parent
 * @return pointer to agent
 * @see reincarnate method
 * @exception none
 */
Agent* Agent::initialise(World *sim,Agent *dad, Agent *mum)
{
    theWorld=sim;
    father=dad;
    mother=mum;
    done=false;
    cultureLength=theWorld->getCultureCount();
    immunityLength=theWorld->getImmunityLength();
    diseaseLength=theWorld->getDiseaseLength();
    currentAge=newAge=0;
    return this;
}



/**
 * reincarnates agent for replacement rule, saves deleting one agent and then creating a new replacement
 * @param pos :new position of agent
 * @see Replacement rule
 * @return pointer to agent
 * @exception none
 */
Agent* Agent::reincarnate(std::pair<int,int> pos){
    mother=father=nullptr;
    killed=false;
    newPosition=currentPosition=pos;
    currentAge=0;
    newAge=1;
    vision=theWorld->getRnd(0, theWorld->getMaxVision());
    cultureLength=theWorld->getCultureCount();
    immunityLength=theWorld->getImmunityLength();
    newSugar=currentSugar=theWorld->getRnd(0, theWorld->getInitialSugarMax());
    newSpice=currentSpice=theWorld->getRnd(0, theWorld->getInitialSpiceMax());
    maxAge=theWorld->getRnd(theWorld->getMinAge(), theWorld->getMaxAge());
    currentMetabolism=newMetabolism=theWorld->getRnd(theWorld->getMinMetabolism(),theWorld->getMaxMetabolism());
    currentSpiceMetabolism=newSpiceMetabolism=theWorld->getRnd(theWorld->getMinSpiceMetabolism(),theWorld->getMaxSpiceMetabolism());
    cultureLength=theWorld->getCultureCount();
    immunityLength=theWorld->getImmunityLength();
    diseaseLength=theWorld->getDiseaseLength();
    /*!< Create random immunity */
    for (int i=0; i<immunityLength; ++i) {
        bool aBit=false;
        if (theWorld->getRnd(0, 10)>=5) {
            aBit=true;
        }
        currentImmunity.push_back(aBit);
        newImmunity.push_back(aBit);
    }
    /*!< Create random culture */
    for (int i=0; i<cultureLength; ++i) {
        bool aBit=false;
        if (theWorld->getRnd(0, 10)>=5) {
            aBit=true;
        }
        currentCulture.push_back(aBit);
        newCulture.push_back(aBit);
    }
    /*!< Create random disease */
    std::vector<bool> newDisease;
    for (int i=0; i<diseaseLength; ++i) {
        bool aBit=false;
        if (theWorld->getRnd(0, 10)>=5) {
            aBit=true;
        }
        newDisease.push_back(aBit);
    }
    currentDiseases.push_back(newDisease);
    newDiseases.push_back(newDisease);
    return this;
}

/**
 * mark this agent as done (completed action or part of group going to complete action
 * @return true
 * @exception none
 */
bool Agent::markDone(void){
    return done=true;
}


/**
 * mrk agent as killed
 * @see Combat rule
 * @return true
 * @exception none
 */
bool Agent::markKilled(){
    return killed=true;
}

/**
 * REturns tribe of agent (red or blue)
 * @see Culture Rule
 * @return affiliation (red or blue)
 * @exception none
 */
affiliation Agent::getTribe(void){
    int reds=0;
    for (int i=0; i<cultureLength; ++i) {
        if (currentCulture[i]==true) {
            reds++;
        }
    }
    if (reds>cultureLength/2) {
        return affiliation::red;
    }
    else{
        return affiliation::blue;
    }
}


/**
 * tells us if agent is immune to a disease
 * @param disease
 * @see AgentDisease Rule
 * @return true if immune else false
 * @exception none
 */
bool Agent::isImmune(std::vector<bool> disease){
    int j=0;
    int length= (int)disease.size();
    for (int i=0; i<immunityLength-length; ++i) {
        for (j=0; j<length && disease[j]==currentImmunity[i+j]; ++j) {
            if (i+j==immunityLength-1) {
                return false;
            }
        }
        if (j==length) {
            return true;
        }
    }
    return false;
}

/**
 * Is this agent our child?
 * @param agent
 * @see Inheritance Rule
 * @return true if agent is our child
 * @exception none
 */
bool Agent::isChild(Agent* agent){
    for (const Agent* child: currentChildren){
        if (agent==child) return true;
    }
    return false;
}

/**
 * Adds agent to our list of children
 * @param newChild
 * @return number of children we have
 * @exception none
 */
unsigned long Agent::addChild(Agent* newChild){
    newChildren.push_back(newChild);
    return newChildren.size();
}

/**
 * delete agent from our child list (we only store living children)
 * @param goneChild
 * @return number of children we have
 * @exception none
 */
unsigned long Agent::removeChild(Agent* goneChild){
    auto it = std::find(newChildren.begin(), newChildren.end(), goneChild);
    if(it != newChildren.end())
        newChildren.erase(it);
    return newChildren.size();
}

/**
 * Returns amount owed *BY* agent *IN TOTAL*
 * @see Credit Rule
 * @return amount we owe IN TOTAL
 * @exception none
 */
int Agent::totalOwed(void){
    int total=0;
    for(const std::pair<Agent*,std::pair<int, int>> account:currentLoansOwed){
        total+=account.second.first+account.second.first*theWorld->getRate()*theWorld->getDuration();
    }//for
    return total;
}

/**
 * Returns amount owed *TO* agent *IN TOTAL*
 * @see Credit Rule
 * @return amount we are owed IN TOTAL
 * @exception none
 */
int Agent::totalOwing(void){
    int total=0;
    for(const std::pair<Agent*,std::pair<int, int>> account:currentLoansOwing){
        total+=account.second.first+account.second.first*theWorld->getRate()*theWorld->getDuration();
    }//for
    return total;
}


/**
 * Returns amount owed *BY* agent TODAY
 * @see Credit Rule
 * @return amount we owe
 * @exception none
 */
int Agent::OwedToday(void){
    int total=0;
    for(const std::pair<Agent*,std::pair<int, int>> account:currentLoansOwed){
        if (account.second.second==theWorld->getStep()) {
            total+=account.second.first+account.second.first*theWorld->getRate()*theWorld->getDuration();
        }//if
    }//for
    return total;
}

/**
 * Returns amount owed *TO* agent TODAY
 * @see Credit Rule
 * @return amount we are owed
 * @exception none
 */
int Agent::OwingToday(void){
    int total=0;
    for(const std::pair<Agent*,std::pair<int, int>> account:currentLoansOwing){
        if (account.second.second==theWorld->getStep()) {
            total+=account.second.first+account.second.first*theWorld->getRate()*theWorld->getDuration();
        }//if
    }//for
    return total;
}


/**
 * Checks to see if an agent has a particular disease
 * @param infection :disease we are checking for
 * @return true if we have it otherwise false
 * @exception none
 */
bool Agent::hasDisease(std::vector<bool> infection){
    for(const std::vector<bool> myDisease:currentDiseases){
        if (myDisease==infection) {
            return true;
        }
    }
    return false;
}

/**
 * Infects an agent with a disease by adding it to the list of diseases agent has. Be careful not to add the same disease multiple times
 * @param infection :Bool array representing a disease
 * @return the number of diseases held by the agent
 * @exception none
 */
unsigned long Agent::addDisease(std::vector<bool> infection){
    newDiseases.push_back(infection);
    return newDiseases.size();
}


/**
 * Returns number of diseases an agent has
 * @return length of currentDiseases vector
 * @exception none
 */
unsigned long Agent::diseaseCount(void){
    return currentDiseases.size();
}

/**
 * Sets the value of one of the bools in the culture array
 * @param index :index of tag being updated
 * @param value :new value of tag
 * @return new tag value
 * @exception none
 */
bool Agent::setTag(int index,bool value){
    return newCulture[index]=value;
}

/**
 * Tells us if an agent is dead -- if it has reached maxAge or has no sugar left
 * @return true if will die now else false
 * @exception none
 */
bool Agent::isDead(void)
{
    if (currentAge>=maxAge || currentSugar<=0) {
        return true;
    } else {
        return false;
    }
}

/**
 * Tells us if an agent is marked for dead via combat
 * @return true if will be killed in combat now else false
 * @exception none
 */
bool Agent::isKilled(void)
{
    return killed;
}

/**
 * Removes all loans with dead agents
 * @return number of loan agreements nullified
 * @exception none
 */
int Agent::removeDeadLoans(void)
{
    int repititions=0;
    auto it=newLoansOwed.begin();
    while(it!=newLoansOwed.end())
    {
        if (it->first->isDead()) {
            it=newLoansOwed.erase(it);
            ++repititions;
        }
        else{
            ++it;
        }
    }
    it=newLoansOwing.begin();
    while(it!=newLoansOwing.end())
    {
        if (it->first->isDead()) {
            it=newLoansOwing.erase(it);
            ++repititions;
        }
        else{
            ++it;
        }
    }
    return repititions;
}

/**
 * Removed link to mother if father is dead
 * @return true if mother was dead else false
 * @exception none
 */
bool Agent::removeDeadMother(void)
{
    if (mother==nullptr) {
        return true;
    }
    else if (mother->isDead()) {
        mother=nullptr;
        return true;
    }
    else{
        return false;
    }
}

/**
 * Removes link to father if father is dead
 * @return true if father was dead else false
 * @exception none
 */
bool Agent::removeDeadFather(void)
{
    if (father==nullptr) {
        return true;
    }
    else if (father->isDead()) {
        father=nullptr;
        return true;
    }
    else{
        return false;
    }
}
/**
 * Removes all loans with dead agents
 * @return number of loan agreements nullified
 * @exception none
 */
int Agent::removeKilledLoans(void)
{
    int repititions=0;
    auto it=newLoansOwed.begin();
    while(it!=newLoansOwed.end())
    {
        if (it->first->isKilled()) {
            it=newLoansOwed.erase(it);
            ++repititions;
        }
        else{
            ++it;
        }
    }
    it=newLoansOwing.begin();
    while(it!=newLoansOwing.end())
    {
        if (it->first->isKilled()) {
            it=newLoansOwing.erase(it);
            ++repititions;
        }
        else{
            ++it;
        }
    }
    return repititions;
}

/**
 * Removed link to mother if mother is dead
 * @return true if mother was dead else false
 * @exception none
 */
bool Agent::removeKilledMother(void)
{
    if (mother==nullptr) {
        return true;
    }
    else if (mother->isKilled()) {
        mother=nullptr;
        return true;
    }
    else{
        return false;
    }
}
/**
 * Removed link to father if father is dead
 * @return true if father was dead else false
 * @exception none
 */
bool Agent::removeKilledFather(void)
{
    if (father==nullptr) {
        return true;
    }
    else if (father->isKilled()) {
        father=nullptr;
        return true;
    }
    else{
        return false;
    }
}


/**
 * Tells us if all neighbours are done
 * @see IterativeWriteAction
 * @return true if all done
 * @exception none
 */
bool Agent::allDone(void){
    for (int i=0; i<4; ++i) {
        if (availableNeighbours[i]==true) {
            return false;
        }
    }
    return true;
}

/**
 * Sets all neighbours to not done
 * @see IterativeWriteAction
 * @return true
 * @exception none
 */
bool Agent::resetNeighbours(void){
    for (int i=0; i<4; ++i) {
        availableNeighbours[i]=true;
    }
    return true;
}


/**
 * Sets all neighbours to done
 * @see IterativeWriteAction
 * @return true
 * @exception none
 */
bool Agent::makeUnavailable(void){
    for (int i=0; i<4; ++i) {
        availableNeighbours[i]=false;
    }
    return true;
}
/**
 * Finalises updates - Applies updates to agent state
 * @return true if update sucessfull, otherwise false
 * @exception none
 */
bool Agent::sync(void){
    currentPosition=newPosition;
    currentSugar=newSugar;
    currentSpice=newSpice;
    for (int i=0; i<cultureLength; ++i) {
        currentCulture[i]=newCulture[i];
    }
    for (int i=0; i<immunityLength; ++i) {
        currentImmunity[i]=newImmunity[i];
    }
    currentChildren=newChildren;
    currentLoansOwed=newLoansOwed;
    currentLoansOwing=newLoansOwing;
    currentDiseases=newDiseases;
    done=false;
    killed = false;
    return true;
}

