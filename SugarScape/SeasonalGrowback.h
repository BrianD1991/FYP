//
//  SeasonalGrowback.h
//  SugarScape
//
//  Created by Joseph Kehoe on 11/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__SeasonalGrowback__
#define __SugarScape__SeasonalGrowback__

#include <iostream>
#include "IndependentAction.h"

/*!  \class  SeasonalGrowback
 \brief Implements Seasonal Growback Rule
 
Initially it is summer in the top half of the Sugarscape and winter in the bottom half.  Then every $\gamma$ time periods the seasons flip - in the region where it was summer it becomes winter and vice versa. For each site, if the season is summer then sugar grows back at a rate of *sugarGrowth* units per time interval; if the season is winter then the grow back rate is *sugarGrowth* units per *WinterRate* time intervals.
 */

class SeasonalGrowback:public IndependentAction{
public:
    SeasonalGrowback(World *s);
    virtual bool executeAction(Location *);
};

#endif /* defined(__SugarScape__SeasonalGrowback__) */
