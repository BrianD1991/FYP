//
//  Inheritance.h
//  SugarScape
//
//  Created by Joseph Kehoe on 08/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__Inheritance__
#define __SugarScape__Inheritance__

#include <iostream>
#include "AgentCulture.h"


/*!  \class  Inheritance
 \brief Implements the Inheritance Rule
 
 Agent Inheritance $I$
 When an agent dies its wealth is equally distributed among all its living children.
 */

class Inheritance:public ReadAction{
public:
    Inheritance(World *s);
    virtual bool executeAction(Location *);
};

#endif /* defined(__SugarScape__Inheritance__) */
