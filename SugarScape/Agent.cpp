//
//  Agent.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "Agent.h"

//Constructors
Agent::Agent()
{
    
}

//getters
std::pair<int, int> Agent::getPosition(void){
    return position;
}
Sex Agent::getSex(void){
    return sex;
}
int Agent::getVision(void){
    return vision;
}
int Agent::getAge(void){
    return currentAge;
}
int Agent::getMaxAge(void){
    return maxAge;
}
int Agent::getMetabolism(void){
    return currentMetabolism;
}
int Agent::getSugar(void){
    return currentSugar;
}
int Agent::getCultureLength(void){
    return cultureLength;
}
int Agent::getImmunityLength(void){
    return immunityLength;
}
bool *Agent::getCulture(void){
    return currentCulture;
}
bool *Agent::getImmunity(void){
    return currentImmunity;
}
std::vector<Agent*> Agent::getChildren(void){
    return currentChildren;
}
std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::getLoansOwed(void){
    return currentLoansOwed;
}
std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::getLoansOwing(void){
    return currentLoansOwing;
}
std::vector<bool*> Agent::getDiseases(void){
    return currentDiseases;
}

//setters
std::pair<int, int> Agent::setPosition(std::pair<int, int> newPosition){
    position=newPosition;
    return newPosition;
}
Sex Agent::setSex(Sex newSex){
    if (sex==Sex::unknown) sex=newSex;
    return sex;
}
int Agent::setVision(int newVision){
    if (vision==-1) {
        vision=newVision;
    }
    return newVision;
}
int Agent::incAge(void){
    return ++newAge;
}
int Agent::setAge(int newAmount){
    newAge=newAmount;
    return newAge;
}
int Agent::setMaxAge(int newMax){
    if (maxAge==-1) {
        maxAge=newMax;
    }
    return maxAge;
}
int Agent::setMetabolism(int newAmount){
    newMetabolism=newAmount;
    return newMetabolism;
}
int Agent::incSugar(int extraSugar){
    newSugar+=extraSugar;
    return newSugar;
}
int Agent::setSugar(int newAmount){
    newSugar=newAmount;
    return newSugar;
}
int Agent::setCultureLength(int newAmount){
    cultureLength=newAmount;
    return cultureLength;
}
int Agent::setImmunityLength(int newAmount){
    immunityLength=newAmount;
    return immunityLength;
}
bool *Agent::setCulture(bool* replacementCulture){
    delete newCulture;
    newCulture=replacementCulture;
    return newCulture;
}
bool *Agent::setImmunity(bool* replacementImmunity){
    delete newImmunity;
    newImmunity=replacementImmunity;
    return newImmunity;
}
std::vector<Agent*> Agent::setChildren(std::vector<Agent*>){

}
std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::setLoansOwed(std::vector<std::pair<Agent*,std::pair<int, int>>>);
std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::setLoansOwing(std::vector<std::pair<Agent*,std::pair<int, int>>>);
std::vector<bool*> Agent::setDiseases(std::vector<bool*>);

//helpers
affiliation Agent::getTribe(void);
bool Agent::isImmune(bool*);
bool Agent::isChild(Agent*);
int Agent::addChild(Agent*);
int Agent::removeChild(Agent*);
int Agent::totalOwed(void);
int Agent::totalOwing(void);
int Agent::OwedToday(void);
int Agent::OwingToday(void);
bool Agent::hasDisease(bool*);
int Agent::addDisease(bool*);
bool Agent::sync(void);