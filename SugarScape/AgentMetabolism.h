//
//  AgentMetabolism.h
//  SScapeGUI
//
//  Created by Joseph kehoe on 26/08/2015.
//  Copyright (c) 2015 Joseph Kehoe. All rights reserved.
//

#ifndef __SScapeGUI__AgentMetabolism__
#define __SScapeGUI__AgentMetabolism__

#include <iostream>
#include "IndependentAction.h"

/*!  \class  AgentMetabolism
 \brief handles metabolism of agents
 
 Not a seperate rule in book but required as a seperate rule
 i.e. should have been a rule in book!
 */
class AgentMetabolism:public IndependentAction{
public:
    AgentMetabolism(World *s);
    virtual bool executeAction(Location *, group *);
};



#endif /* defined(__SScapeGUI__AgentMetabolism__) */
