//
//  World.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__World__
#define __SugarScape__World__

#include <iostream>
#include "Action.h"
#include "Location.h"

class World{
    int step;
    int size;
    int cultureCount;
    int maxVision;
    int minMetabolism, maxMetabolism;
    int sugarGrowth;
    int minAge,maxAge;
    int duration;
    int rate;
    int initialSugarMin,initialSugarMax;
    int winterRate;
    int seasonLength;
    int production;
    int consumption;
    int combatLimit;
    int immunityLength;
    int initialPopulationSize;
    int pollutionRate;
    int childAmount;
    
    Location ** Lattice;
    std::vector<Agent*> population;
    
public:
    //Constructors
    World(void);

    
    
    //Getters
    int getStep(void);
    int getSize(void);
    int getCultureCount(void);
    int getMaxVision(void);
    int getMinMetabolism(void);
    int getMaxMetabolism(void);
    int getSugarGrowth(void);
    int getMinAge(void);
    int getMaxAge(void);
    int getDuration(void);
    int getRate(void);
    int getInitialSugarMin(void);
    int getInitialSugarMax(void);
    int getWinterRate(void);
    int getSeasonLength(void);
    int getProduction(void);
    int getConsumption(void);
    int getCombatLimit(void);
    int getImmunityLength(void);
    int getInitialPopulationSize(void);
    int getPollutionRate(void);
    int getChildAmount(void);
    Agent* getAgent(int,int);
    std::vector<Agent*> getNeighbours(int,int,int);
    
    //Setters
    int setSize(int);
    int setCultureCount(int);
    int setMaxVision(int);
    int setMinMetabolism(int);
    int setMaxMetabolism(int);
    int setSugarGrowth(int);
    int setMinAge(int);
    int setMaxAge(int);
    int setDuration(int);
    int setRate(int);
    int setInitialSugarMin(int);
    int setInitialSugarMax(int);
    int setWinterRate(int);
    int setSeasonLength(int);
    int setProduction(int);
    int setConsumption(int);
    int setCombatLimit(int);
    int setImmunityLength(int);
    int setInitialPopulationSize(int);
    int setPollutionRate(int);
    int setChildAmount(int);
    Agent* setAgent(int,int,Agent*);
    
    

    //Rule Application
    int doIndependentRule(Action* upDate);
    int doReadDependentRule(Action* upDate);
    int doWriteDependentRule(Action* upDate, Action* getGroup);

};


#endif /* defined(__SugarScape__World__) */
