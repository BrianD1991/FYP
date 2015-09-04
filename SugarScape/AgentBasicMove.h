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


/*!  \class  AgentBasicMove
 \brief Simplest Movement Rule - Random Movement
 
 Movement - M

 - Look out as far as vision permits in each of the four lattice directions, north, south, east and west;
 - Considering only unoccupied lattice positions, Pick a Location at random;
 - Move to the new position
 - Collect all resources at that location

 */
class AgentBasicMove :public WriteAction{
public:
    AgentBasicMove(World *s);
    virtual bool executeAction(Location *, group *);
    virtual group* formGroup(Location *);

};

#endif /* defined(__SugarScape__AgentBasicMove__) */
