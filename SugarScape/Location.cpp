//
//  Location.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 25/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "Location.h"


//constructors
Location::Location():
    maxSugar(0),currentSugar(0),
    currentPollution(0),newPollution(0),
    newSugar(0),position(0,0)
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

//helpers
bool Location::sync(void){
    currentPollution=newPollution;
    currentSugar=newSugar;
    return true;
}
