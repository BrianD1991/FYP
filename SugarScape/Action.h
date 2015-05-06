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
#include "World.h"

class Action{
protected:
    World *sim;
public:
    Action(World*);
    virtual ~Action();
    virtual int run(void);
    virtual bool executeAction(Location *);
    virtual group* formGroup(Location *);
};
#endif /* defined(__SugarScape__Action__) */
