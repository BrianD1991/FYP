//
//  AgentMove.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 16/07/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__AgentMove__
#define __SugarScape__AgentMove__

#include <iostream>
#include "AgentBasicMove.h"

bool myCompare(Location *a, Location *b);

class AgentMove :public AgentBasicMove{
public:
    AgentMove(World *s);
    virtual int pickIndex(std::vector<Location*>);
};

#endif /* defined(__SugarScape__AgentMove__) */
