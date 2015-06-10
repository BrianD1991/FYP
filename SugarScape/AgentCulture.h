//
//  AgentCulture.h
//  SugarScape
//
//  Created by Joseph Kehoe on 12/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__AgentCulture__
#define __SugarScape__AgentCulture__

#include <iostream>
#include "ReadAction.h"

/*!  \class  AgentCulture
 \brief Implements Agent Culture rule
 


* Select a neighboring agent at random;
* Select a tag randomly;
* If the neighbor agrees with the agent  at that tag position, no change is made; if they disagree, the neighbor's tag is flipped to agree with the agent's tag;
* Repeat for all neighbors.

Group membership
* Agents are defined to be members of the Blue group when 0s outnumber 1s on their tag strings, and members of the Red group in the opposite case.
Agent Culture K
* Combination of the ``agent cultural transmission'' and ``agent group membership'' rules given immediately above.
 */

class AgentCulture:public ReadAction{
public:
    AgentCulture(World *s);
    virtual bool executeAction(Location *, group *);
};


#endif /* defined(__SugarScape__AgentCulture__) */
