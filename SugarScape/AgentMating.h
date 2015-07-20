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
#include "WriteAction.h"

class AgentMating:public WriteAction{
protected:
    bool suitable(Location*);
public:
    AgentMating(World*);
    virtual bool executeAction(Location *, group *);
    virtual group* formGroup(Location *);
    virtual int participantCount(int,int,int);
};
#endif /* defined(__SugarScape__AgentMating__) */
