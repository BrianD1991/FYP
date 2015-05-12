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
Agent::Agent(World *s):amountEaten(0), done(false),
    theWorld(s),currentAge(0),newAge(0),
    cultureLength(s->getCultureCount()),immunityLength(s->getImmunityLength())
{
    //TO DO!!
}

//getters
int Agent::getAmountEaten(void){
    return amountEaten;
}

bool Agent::isDone(void){
    return done;
}
std::pair<int, int> Agent::getPosition(void){
    return currentPosition;
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
std::pair<int, int> Agent::setPosition(std::pair<int, int> destination){
    newPosition=destination;
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
std::vector<Agent*> Agent::setChildren(std::vector<Agent*>replacementChildren){
    newChildren=replacementChildren;
    return newChildren;
}

std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::setLoansOwed(std::vector<std::pair<Agent*,std::pair<int, int>>> replacementLoansOwed){
    newLoansOwed=replacementLoansOwed;
    return newLoansOwed;
}
std::vector<std::pair<Agent*,std::pair<int, int>>> Agent::setLoansOwing(std::vector<std::pair<Agent*,std::pair<int, int>>> replacementLoansOwing){
    newLoansOwing=replacementLoansOwing;
    return newLoansOwing;
}
std::vector<bool*> Agent::setDiseases(std::vector<bool*> replacementDiseases){
    newDiseases=replacementDiseases;
    return newDiseases;
}

//helpers
bool Agent::markDone(void){
    return done=true;
}
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
bool Agent::isImmune(bool* disease, int length){
    int j=0;
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
bool Agent::isChild(Agent* agent){
    for (const Agent* child: currentChildren){
        if (agent==child) return true;
    }
    return false;
}
unsigned long Agent::addChild(Agent* newChild){
    newChildren.push_back(newChild);
    return newChildren.size();
}
unsigned long Agent::removeChild(Agent* goneChild){
    auto it = std::find(newChildren.begin(), newChildren.end(), goneChild);
    if(it != newChildren.end())
        newChildren.erase(it);
    return newChildren.size();
}
int Agent::totalOwed(void){
    int total=0;
    for(const std::pair<Agent*,std::pair<int, int>> account:currentLoansOwed){
        total+=account.second.first+account.second.first*theWorld->getRate()*theWorld->getDuration();
    }//for
    return total;
}
int Agent::totalOwing(void){
    int total=0;
    for(const std::pair<Agent*,std::pair<int, int>> account:currentLoansOwing){
        total+=account.second.first+account.second.first*theWorld->getRate()*theWorld->getDuration();
    }//for
    return total;
}
int Agent::OwedToday(void){
    int total=0;
    for(const std::pair<Agent*,std::pair<int, int>> account:currentLoansOwed){
        if (account.second.second==theWorld->getStep()) {
            total+=account.second.first+account.second.first*theWorld->getRate()*theWorld->getDuration();
        }//if
    }//for
    return total;
}
int Agent::OwingToday(void){
    int total=0;
    for(const std::pair<Agent*,std::pair<int, int>> account:currentLoansOwing){
        if (account.second.second==theWorld->getStep()) {
            total+=account.second.first+account.second.first*theWorld->getRate()*theWorld->getDuration();
        }//if
    }//for
    return total;
}
bool Agent::hasDisease(bool* infection){
    for(const bool* myDisease:currentDiseases){
        if (myDisease==infection) {
            return true;
        }
    }
    return false;
}
unsigned long Agent::addDisease(bool* infection){
    newDiseases.push_back(infection);
    return newDiseases.size();
}
bool Agent::sync(void){
    currentPosition=newPosition;
    currentAge=newAge;
    currentSugar=newSugar;
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
    return true;
}

