//
//  Growback.h
//  SugarScape
//
//  Created by Joseph Kehoe on 11/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__Growback__
#define __SugarScape__Growback__

#include <iostream>
#include "IndependentAction.h"

/*!  \class  Growback
 \brief Implements Growback Rule
 
 At each Lattice position, sugar grows back at a fixed rate of *sugarGrowth* units per time interval up to the capacity at that position.
 */

class Growback:public IndependentAction{
public:
    Growback(World *s);
    virtual bool executeAction(Location *, group *);
};
#endif /* defined(__SugarScape__Growback__) */
