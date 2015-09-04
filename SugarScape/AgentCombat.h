//
//  AgentCombat.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 16/07/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__AgentCombat__
#define __SugarScape__AgentCombat__

#include <iostream>
#include "AgentMove.h"

bool combatCompare(Location *, Location *);

/*!  \class  AgentCombat
 \brief Combat Rule
 
Agent Combat C_{\alpha}

 - Look out as far as vision permits in the four principle lattice directions;
 - Throw out all sites occupied by members of the agent's own tribe;
 - Throw out all sites occupied by members of different tribes who are wealthier then the agent;
 - The reward of each remaining site is given by the resource level at the site plus, if it is occupied, the minimum of $\alpha$ and the occupant's wealth;
 - Throw out all sites that are vulnerable to retaliation;
 - Select the nearest position having maximum reward and go there;
 - Gather the resources at the site plus the minimum of $\alpha$ and the occupants wealth if the site was occupied;
 - If the site was occupied then the former occupant is considered ``killed'' - permanently removed from play.
 */
class AgentCombat :public AgentMove{
public:
    AgentCombat(World *s);
    virtual bool executeAction(Location *, group *);
    virtual group* formGroup(Location *);
    virtual int pickIndex(std::vector<Location*>, Agent *);
};
#endif /* defined(__SugarScape__AgentCombat__) */
