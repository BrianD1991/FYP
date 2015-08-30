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

/**
 * Decrements an agents surar by their metabolism
 * @param loc :Location in lattice we are runing action on
 * @param group pointer not used - nullptr passed in
 * @see Metabolism in book
 * @return true if agent was at location else false
 * @exception none
 */
bool AgentMetabolism::executeAction(Location * loc, group * ){
    if (loc->hasAgent()) {
        Agent *agent =loc->getAgent();
        agent->incSugar(-agent->getMetabolism());
        agent->incAge();
    }
    return true;
}


