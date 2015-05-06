//
//  group.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__group__
#define __SugarScape__group__

#include <iostream>
#include "Location.h"

class group{
    std::vector<Location*> members;
    int score;
    int size;
public:
    int getScore(void);
    std::vector<Location*> getMembers(void);
    int getSize(void);
    
    bool push_back(Location*);
    
    static bool compare(group *,group *);
    
};
#endif /* defined(__SugarScape__group__) */
