//
//  AgentCombat.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 16/07/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__AgentCombat__
#define __SugarScape__AgentCombat__

#include <iostream>
#include "AgentMove.h"

bool combatCompare(Location *, Location *);

class AgentCombat :public AgentMove{
public:
    AgentCombat(World *s);
    virtual bool executeAction(Location *, group *);
    virtual group* formGroup(Location *);
    virtual int pickIndex(std::vector<Location*>, Agent *);
};
#endif /* defined(__SugarScape__AgentCombat__) */
