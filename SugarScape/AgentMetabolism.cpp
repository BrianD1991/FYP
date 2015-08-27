//
//  AgentMetabolism.cpp
//  SScapeGUI
//
//  Created by Joseph kehoe on 26/08/2015.
//  Copyright (c) 2015 Joseph Kehoe. All rights reserved.
//

#include "AgentMetabolism.h"


AgentMetabolism::AgentMetabolism(World *sim):IndependentAction(sim){
    
}

bool AgentMetabolism::executeAction(Location * loc, group * ){
    if (loc->hasAgent()) {
        Agent *agent =loc->getAgent();
        agent->incSugar(-agent->getMetabolism());
        agent->incAge();
    }
    return true;
}


