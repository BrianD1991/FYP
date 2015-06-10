//
//  AgentBasicMove.h
//  SugarScape
//
//  Created by Joseph kehoe on 10/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__AgentBasicMove__
#define __SugarScape__AgentBasicMove__

#include <iostream>
#include "WriteAction.h"

class AgentBasicMove :public WriteAction{
public:
    AgentBasicMove(World *s);
    virtual bool executeAction(Location *, group *);
    virtual group* formGroup(Location *);
    
};

#endif /* defined(__SugarScape__AgentBasicMove__) */
