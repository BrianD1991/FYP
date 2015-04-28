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
class Location{
    int x,y;
    int sugar;
    int maxSugar;
    int pollution;
public:
    //constructors
    Location();
    Location(int,int);
    
    //getters
    int getX(void);
    int getY(void);
    int getSugar(void);
    int getMaxSugar(void);
    int getPollution(void);
    
    //setters
    int setX(int);
    int setY(int);
    int setSugar(int);
    int setMaxSugar(int);
    int setPollution(int);
};

#endif /* defined(__SugarScape__Location__) */
