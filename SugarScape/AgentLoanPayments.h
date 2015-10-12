//
//  AgentLoanPayments.h
//  SugarScape
//
//  Created by Joseph kehoe on 12/10/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__AgentLoanPayments__
#define __SugarScape__AgentLoanPayments__

#include <iostream>
#include "WriteAction.h"

/*!  \class  AgentReplacement
 \brief Replacement Rule
 
 Replacement - R_[a,b]
 When an agent dies it is replaced by an agent of age 0 having random genetic attributes, random position on the Sugarscape, random initial endowment, and a maximum age selected from the range [a,b].
 */
class AgentLoanPayments :public WriteAction{

public:
    AgentLoanPayments(World *s);
    virtual bool executeAction(Location *, group *);
    virtual group* formGroup(Location *);
    
};


#endif /* defined(__SugarScape__AgentLoanPayments__) */
