//
//  Diffusion.h
//  SugarScape
//
//  Created by Joseph Kehoe on 12/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__Diffusion__
#define __SugarScape__Diffusion__

#include <iostream>
#include "IndependentAction.h"

/*!  \class  Diffusion
 \brief Implements Pollution Diffusion rule
 
 * Each alpha (pollutionRate) time periods and at each site, compute the pollution flux the average pollution level over all its von Neumann neighbouring sites;
 * Each site's flux becomes its new pollution level.
 */

class Diffusion:public IndependentAction{
public:
    Diffusion(World *s);
    virtual bool executeAction(Location *);
};


#endif /* defined(__SugarScape__Diffusion__) */
