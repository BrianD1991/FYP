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
    std::vector<Location*> members; /*!< Agents in this group */
    int rank; /*!< Determines the ranking of a group - used for collision resolution*/
    int size; /*!< Number of agents in this group */
public:
    //constructor
    group(void);
    //getters
    int getRank(void);
    std::vector<Location*> getMembers(void);
    int getSize(void);
    
    //setters
    int push_back(Location*);
    int setRank(int);
    
    
    //Helpers
    static bool compare(group *,group *);

    
};
#endif /* defined(__SugarScape__group__) */
