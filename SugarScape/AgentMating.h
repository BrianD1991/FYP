//
//  AgentMating.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 20/07/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__AgentMating__
#define __SugarScape__AgentMating__

#include <iostream>
#include "IterativeWriteAction.h"

/*!  \class  AgentMating
 \brief Mating Rule
 
 Agent Mating S

 - Select a neighboring agent at random;
 - If the neighboring agent is of the opposite sex and if both agents are fertile and at least one of the agents has an empty neighboring site then a newborn is produced by crossing over the parents' genetic and cultural characteristics;
 - Repeat for all neighbors.
 */
class AgentMating:public IterativeWriteAction{
protected:
    bool suitable(Location*);
public:
    AgentMating(World*);
    virtual bool executeAction(Location *, group *);
    virtual group* formGroup(Location *);
    virtual int participantCount(int,int,int);
    //virtual bool run(int startX, int startY, int size);
};
#endif /* defined(__SugarScape__AgentMating__) */
