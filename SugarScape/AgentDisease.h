//
//  AgentDisease.h
//  SugarScape
//
//  Created by Joseph kehoe on 21/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__AgentDisease__
#define __SugarScape__AgentDisease__

#include <iostream>
#include "ReadAction.h"

/*!  \class  AgentDisease
 \brief Implements Agent Disease Immunity and Transmission rule
 
 
Agent immune response

 * If the disease is a substring of the immune system then end (the agent is immune), else (the agent is infected) go to the following step;
 * The substring in the agent immune system having the smallest Hamming distance from the disease is selected and the first bit at which it is different from the disease string is changed to match the disease.

 
Disease transmission
 * For each neighbor, a disease that currently afflicts the agent is selected at random and given to the neighbor.
 
 Agent disease processes E
 * Combination of ``agent immune response'' and ``agent disease transmission'' rules given immediately above

 */

class AgentDisease:public ReadAction{
public:
    AgentDisease(World *s);
    virtual bool executeAction(Location *);
};


#endif /* defined(__SugarScape__AgentDisease__) */
