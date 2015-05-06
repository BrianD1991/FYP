//
//  Action.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 28/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "Action.h"


Action::Action(){
    
}
bool Action::executeAction(Location *theLocation){
    return false;
}
group* Action::formGroup(Location *theLocation){
    group* theGroup= new group;
    theGroup->push_back(theLocation);
    return theGroup;
}