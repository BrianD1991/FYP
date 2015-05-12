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
#include "Location.h"

class Action;


class World{
    int step; /*!< Number of steps the simulation has run for */
    int size; /*!< Dimensions of lattice  a size*size matrix of locations*/
    int cultureCount;/*!< Length of bitstring containing culture information */
    int maxVision; /*!< Maximum extent allowable for any agents vision */
    int minMetabolism, maxMetabolism; /*!< minimum and maximum metabolism rates that any agent may be born with */
    int sugarGrowth; /*!< Rate at which sugar is replenished by each location during a step */
    int minAge,maxAge; /*!< Minimum and maximum allowable lifespan that can be assigned to any agents*/
    int duration; /*!< Duration of all loan lengths in steps */
    int rate; /*!< Rate of interest applied to loans */
    int initialSugarMin,initialSugarMax; /*!< Range of initial sugar allocation given to agents at beginning of simulation */
    int winterRate; /*!< Rate that sugar grows back during winter season */
    int seasonLength; /*!< Length of each season (winter and summer) */
    int production;
    int consumption;
    int combatLimit; /*!< Maximum reward attainable through killing an agent */
    int immunityLength;
    int initialPopulationSize; /*!< Starting population size */
    int pollutionRate; /*!< Number of timeperiods that pass between each diffusion of pollution */
    int childAmount;
    
    Location ** Lattice; /*!< 2D (size by size) Matrix of locations in world  */
    std::vector<Agent*> population; /*!< Agents in simulation */
    std::vector<Action*> activeRules; /*!< Rules we run each time step */
    
    
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
    Location** getLattice(void);
    
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
    int applyRules(void);

};


#endif /* defined(__SugarScape__World__) */
