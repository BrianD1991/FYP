//
//  AgentReplacement.h
//  SugarScape
//
//  Created by Joseph kehoe on 07/07/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__AgentReplacement__
#define __SugarScape__AgentReplacement__

#include <iostream>
#include "WriteAction.h"

class AgentReplacement :public WriteAction{
    std::vector<Location* > freeSlots;
    unsigned long  populateFreeSlots(void);
public:
    AgentReplacement(World *s);
    virtual bool executeAction(Location *, group *);
    virtual group* formGroup(Location *);
    virtual bool run(int,int,int);
    virtual bool concurrentRun(void);
    
};
#endif /* defined(__SugarScape__AgentReplacement__) */
