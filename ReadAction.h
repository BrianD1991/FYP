//
//  ReadAction.h
//  SugarScape
//
//  Created by Joseph P Kehoe on 06/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__ReadAction__
#define __SugarScape__ReadAction__

#include <iostream>
#include "Action.h"

class ReadAction:Action{
    ReadAction(World*);
    virtual ~ReadAction();
    virtual int run(void);
};
#endif /* defined(__SugarScape__ReadAction__) */
