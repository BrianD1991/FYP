//
//  IndependentAction.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__IndependentAction__
#define __SugarScape__IndependentAction__

#include <iostream>
#include "Action.h"

class IndependentAction:Action{
    IndependentAction(World*);
    virtual ~IndependentAction();
    virtual int run(void);
};
#endif /* defined(__SugarScape__IndependentAction__) */
