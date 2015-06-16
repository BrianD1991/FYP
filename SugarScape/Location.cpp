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
    maxSugar(0),currentSugar(0),deadAgent(nullptr),
    currentPollution(0),newPollution(0),
    newSugar(0),position(0,0),sim(theWorld)
{
    //empty
}
Location::Location(int x,int y):
    maxSugar(0),currentSugar(0),
    currentPollution(0),newPollution(0),
newSugar(0),position(std::make_pair(x, y))
{
    //empty
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
