//
//  IterativeWriteAction.h
//  SugarScape
//
//  Created by Joseph kehoe on 28/08/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__IterativeWriteAction__
#define __SugarScape__IterativeWriteAction__

#include <iostream>
#include "WriteAction.h"

/*!  \class  IterativeWriteAction
 \brief Write-Dependent Actions that are iterative
 
 Base Class for all iterative Write-Dependent Actions If an action is applied to every (or more than one) neighbour each in turn during a single step then it inherits from this
 */
class IterativeWriteAction:public WriteAction{

public:
    IterativeWriteAction(World*);
    virtual bool run(int startX, int startY, int size);
    virtual bool concurrentRun(void);
    virtual int  participantCount(int, int, int);
};

#endif /* defined(__SugarScape__IterativeWriteAction__) */
