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
    deadAgent(nullptr),newResident(nullptr),
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
    done(false),deadAgent(nullptr),newResident(nullptr),
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
World* Location::setWorld(World* theWorld){
    World* old=sim;
    sim=theWorld;
    return old;
}
//helpers
bool Location::markDone(void){
    return done=true;
}
bool Location::hasAgent(void){
    return currentResident!=nullptr;
}
Agent* Location::killAgent(void)
{
    newResident=nullptr;
    return deadAgent=currentResident;
}
bool Location::hasDeadAgent()
{
    return deadAgent!=nullptr;
}

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

bool Location::sync(void){
    done=false;
    currentPollution=newPollution;
    currentSugar=newSugar;
    currentResident=newResident;
    return true;
}
