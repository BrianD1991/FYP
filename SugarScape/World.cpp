//
//  World.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "World.h"


//Constructors
World::World(void){
    
}

//Getters
int World::getStep(void){
    return step;
}
int World::getSize(void){
    return size;
}
int World::getCultureCount(void){
    return cultureCount;
}
int World::getMaxVision(void){
    return maxVision;
}
int World::getMinMetabolism(void){
    return minMetabolism;
}
int World::getMaxMetabolism(void){
    return maxMetabolism;
}
int World::getSugarGrowth(void){
    return sugarGrowth;
}
int World::getMinAge(void){
    return minAge;
}
int World::getMaxAge(void){
    return maxAge;
}
int World::getDuration(void){
    return duration;
}
int World::getRate(void){
    return rate;
}
int World::getInitialSugarMin(void){
    return initialSugarMin;
}
int World::getInitialSugarMax(void){
    return initialSugarMax;
}
int World::getWinterRate(void){
    return winterRate;
}
int World::getSeasonLength(void){
    return seasonLength;
}
int World::getProduction(void){
    return production;
}
int World::getConsumption(void){
    return consumption;
}
int World::getCombatLimit(void){
    return combatLimit;
}
int World::getImmunityLength(void){
    return immunityLength;
}
int World::getInitialPopulationSize(void){
    return initialPopulationSize;
}
int World::getPollutionRate(void){
    return pollutionRate;
}
int World::getChildAmount(void){
    return childAmount;
}

//Setters
int World::setSize(int newSize){
    size=newSize;
    return size;
}
int World::setCultureCount(int newCultureCount){
    cultureCount=newCultureCount;
    return cultureCount;
}
int World::setMaxVision(int newMaxVision){
    maxVision=newMaxVision;
    return maxVision;
}
int World::setMinMetabolism(int newMinMetabolism){
    minMetabolism=newMinMetabolism;
    return minMetabolism;
}
int World::setMaxMetabolism(int newMaxMetabolism){
    maxMetabolism=newMaxMetabolism;
    return maxMetabolism;
}
int World::setSugarGrowth(int newSugarGrowth){
    sugarGrowth=newSugarGrowth;
    return sugarGrowth;
}
int World::setMinAge(int newMinAge){
    minAge=newMinAge;
    return minAge;
}
int World::setMaxAge(int newMaxAge){
    maxAge=newMaxAge;
    return maxAge;
}
int World::setDuration(int newDuration){
    duration=newDuration;
    return duration;
}
int World::setRate(int newRate){
    rate=newRate;
    return rate;
}
int World::setInitialSugarMin(int newInitialSugarMin){
    initialSugarMin=newInitialSugarMin;
    return initialSugarMin;
}
int World::setInitialSugarMax(int newInitialSugarMax){
    initialSugarMax=newInitialSugarMax;
    return initialSugarMax;
}
int World::setWinterRate(int newWinterRate){
    winterRate=newWinterRate;
    return winterRate;
}
int World::setSeasonLength(int newSeasonLength){
    seasonLength=newSeasonLength;
    return seasonLength;
}
int World::setProduction(int newProduction){
    production=newProduction;
    return production;
}
int World::setConsumption(int newConsumption){
    consumption=newConsumption;
    return consumption;
}
int World::setCombatLimit(int newCombatLimit){
    combatLimit=newCombatLimit;
    return combatLimit;
}
int World::setImmunityLength(int newImmunityLength){
    immunityLength=newImmunityLength;
    return immunityLength;
}
int World::setInitialPopulationSize(int newInitialPopulationSize){
    initialPopulationSize=newInitialPopulationSize;
    return initialPopulationSize;
}
int World::setPollutionRate(int newPollutionRate){
    pollutionRate=newPollutionRate;
    return pollutionRate;
}
int World::setChildAmount(int newChildAmount){
    childAmount=newChildAmount;
    return childAmount;
}

//Rule Application
int World::doIndependentRule(Action* upDate){
    return -1;
}
int World::doReadDependentRule(Action* upDate){
    return -1;
}
int World::doWriteDependentRule(Action* upDate, Action* getGroup){
    return -1;
}
