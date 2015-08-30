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

/*!  \class  Action
 \brief Abstract base class for Actions
 
 Derived actions need to define formGroup and executeAction functions as they are pure virtual. 
 run and concurrentRun perform actions on lattice.
 */

class Action{
protected:
    World *sim; /*!< The object containing the entire simulation */
public:
    Action(World*);
    virtual ~Action();
    virtual bool run(int,int,int);
    virtual bool concurrentRun(void);
    virtual bool executeAction(Location *, group* grp=nullptr)=0;
    virtual group* formGroup(Location *)=0;
};
#endif /* defined(__SugarScape__Action__) */


//!
/*!
 <#detail#>
 */



/*!< <#description#> */


/**
 * <#description#>
 * @param <#param1#>
 * @param <#param2#>
 * @see <#ref#>
 * @return <#returnValue#>
 * @exception <#exceptionValue#>
 */


/*!  \class  <#name#>
 \brief <#brief#>
 
 <#description#>
 */

