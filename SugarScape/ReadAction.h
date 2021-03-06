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

/*!  \class  ReadAction
 \brief Actions that read the neighbours state but only update their own
 
 Read-Dependent Rules all inherit from this. They need to implement formGroup and executeAction.
 They can just inherit the rest!
 */
class ReadAction:public Action{
public:
    ReadAction(World*);
    virtual ~ReadAction();
    virtual bool run(int,int,int);
    virtual bool concurrentRun(void);
    virtual group* formGroup(Location*);
};
#endif /* defined(__SugarScape__ReadAction__) */
