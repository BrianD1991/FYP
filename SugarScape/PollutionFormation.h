//
//  PollutionFormation.h
//  SugarScape
//
//  Created by Joseph Kehoe on 12/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__PollutionFormation__
#define __SugarScape__PollutionFormation__

#include <iostream>
#include "IndependentAction.h"

/*!  \class  PollutionFormation
 \brief Implements Pollution Formation rule
 
When sugar quantity s is gathered from the Sugarscape, an amount of production pollution is gathered production*s. When sugar amount m is consumed (metabolised), consumption pollution is generated according to consumption*m. The total pollution on a site at time t p[t], is the sum of the pollution present at the previous time, plus the pollution resulting from production and consumption activities, that is, p[t]=p[t-1]+ s+ m. */

class PollutionFormation:public IndependentAction{
public:
    PollutionFormation(World *s);
    virtual bool executeAction(Location *, group *);
};


#endif /* defined(__SugarScape__PollutionFormation__) */
