//
//  Inheritance.cpp
//  SugarScape
//
//  Created by Joseph Kehoe on 08/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "Inheritance.h"

Inheritance::Inheritance(World* s)
    :ReadAction(s)
{
    //Our work is done!
}

/**
 * Check location for agent. If present check to see if due to die.  If so then remove all sugar.
 * If agent is not dying then check each parent to see if they are dying.
 * If they are take the correct share of their sugar (total sugar divided by number of children.
 * Note: We do not bother to check if any of their other children may be dying - just to simplify code
 * @param loc :location to check for agent
 * @see Inheritance Rule
 * @return true if agent was presnt otherwise false
 * @exception none
 */
bool Inheritance::executeAction(Location * loc, group *)
{
    if (loc->hasAgent()) {
        Agent* theAgent=loc->getAgent();
        if (theAgent->getAge()==theAgent->getMaxAge()) {//I am dying
            theAgent->setSugar(0);
        }
        else {//I am alive check to see if parents are dying
            if (theAgent->getFather()->getAge()==theAgent->getFather()->getMaxAge()) {
                theAgent->incSugar(theAgent->getFather()->getSugar()/theAgent->getFather()->getChildrenCount());
            }
            if (theAgent->getMother()->getAge()==theAgent->getMother()->getMaxAge()) {
                theAgent->incSugar(theAgent->getMother()->getSugar()/theAgent->getMother()->getChildrenCount());
            }
        }
        
        return true;
    }else{
        return false;/*!< no agent present so did nothing */
    }

}


