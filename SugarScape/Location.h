//
//  Location.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 25/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__Location__
#define __SugarScape__Location__

#include <iostream>
#include "Agent.h"
const std::pair<int, int> nullPosition(-1,-1);

class Location{
        //immutable -- once initialised these stay constant
        std::pair<int,int> position;
        int maxSugar;
    
        //mutable
        bool done;
        int currentSugar,newSugar;
        int currentPollution,newPollution;
        Agent *currentResident,*newResident;
public:
    //constructors
    Location();
    Location(int,int);
    
    //getters
    bool isDone(void);
    std::pair<int,int> getPosition(void);
    int getX(void);
    int getY(void);
    int getSugar(void);
    int getMaxSugar(void);
    int getPollution(void);
    Agent* getAgent(void);
    
    //setters
    std::pair<int,int> setPosition(std::pair<int,int>);
    int setX(int);
    int setY(int);
    int setSugar(int);
    int setMaxSugar(int);
    int setPollution(int);
    Agent *setAgent(Agent*);
    
    //helpers
    bool markDone(void);
    bool hasAgent(void);
    bool sync(void);
};

#endif /* defined(__SugarScape__Location__) */
