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
#include "Location.h"
#include "group.h"

class Action{
public:
    Action();
    bool executeAction(Location *);
    group* formGroup(Location *);
};
#endif /* defined(__SugarScape__Action__) */
