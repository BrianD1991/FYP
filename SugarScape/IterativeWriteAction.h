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

class IterativeWriteAction:public WriteAction{

public:
    IterativeWriteAction(World*);
    virtual bool run(int startX, int startY, int size);
    virtual bool concurrentRun(void);
};

#endif /* defined(__SugarScape__IterativeWriteAction__) */
