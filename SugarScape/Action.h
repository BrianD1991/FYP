//
//  Action.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__Action__
#define __SugarScape__Action__

#include <iostream>
#include "Agent.h"

class Action{
public:
    Action();
    bool execute(Agent* );
};
#endif /* defined(__SugarScape__Action__) */
