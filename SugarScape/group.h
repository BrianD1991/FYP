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
#include <algorithm>
#include "Location.h"


/*!  \class  group
 \brief Group used in writeDependent actions to record groups of agents who wish to
 interact exclusively for an action (e.g. combat)
 
 Holds:
 - list of agents in the group;
 - The prime mover in the group (e.g. in Combat this is the attacking agent);
 - Size of group
 - Ranking of group , used to sort groups in order
 - Number of active participants (can differ from  size of group - e.g. mating has a group size of 3 but only two active participants
 */
class group{
    std::vector<Location*> members; /*!< Locations of Agents in this group */
    Location *primeMover;/*!< Location of Agent who formed the group */
    int rank; /*!< Determines the ranking of a group - used for collision resolution*/
    int size; /*!< Number of agents in this group */
    int activeParticipants;/*!< Number of active participants in this group used to calculate no. of*/
    /*!< remaining entities left to be assigned to groups*/
public:
    //constructor
    group(void);
    //getters
    int getRank(void);
    std::vector<Location*> getMembers(void);
    int getSize(void);
    int getActiveParticipants(void);
    Location *getPrimeMover(void);
    
    //setters
    int push_back(Location*);
    int setRank(int);
    int setActiveParticipants(int);
    bool setPrimeMover(Location*);
    
    
    //Helpers
    static bool compare(group *,group *);
    
    
};
#endif /* defined(__SugarScape__group__) */
