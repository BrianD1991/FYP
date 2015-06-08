//
//  Inheritance.cpp
//  SugarScape
//
//  Created by Joseph Kehoe on 08/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "Inheritance.h"

Inheritance::Inheritance(World *s):ReadAction(s)
{
    //Our work is done!
}


bool Inheritance::executeAction(Location * loc)
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
        return false;
    }

}
        
