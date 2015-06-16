//
//  AgentDeath.h
//  SugarScape
//
//  Created by Joseph kehoe on 16/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__AgentDeath__
#define __SugarScape__AgentDeath__

#include <iostream>
#include "ReadAction.h"

/*!  \class  AgentDeath
 \brief Kills off agents whose time is due
 
 When an agent reaches its maximum allowed age or runs out of resources it is removed from the simulation and all its associated loans (either as borrower or lender) are considered void.
 */
class AgentDeath :public ReadAction{
public:
    AgentDeath(World *s);
    virtual bool executeAction(Location *, group *);

    
};


#endif /* defined(__SugarScape__AgentDeath__) */
