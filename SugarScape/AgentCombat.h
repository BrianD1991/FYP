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


class AgentCombat :public AgentMove{
protected:
    int findVictim(std::vector<Agent*>);
public:
    AgentCombat(World *s);
    virtual bool executeAction(Location *, group *);
    virtual group* formGroup(Location *);
};
#endif /* defined(__SugarScape__AgentCombat__) */
