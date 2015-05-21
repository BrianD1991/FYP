//
//  AgentDisease.cpp
//  SugarScape
//
//  Created by Joseph kehoe on 21/05/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "AgentDisease.h"

AgentDisease::AgentDisease(World *s):ReadAction(s){
    //EMPTY
}

bool AgentDisease::executeAction(Location *loc){

    if (loc->hasAgent()) {
        Agent * subject=loc->getAgent();
        //Add diseases from neighbours
        std::vector<Agent*> neighbours=sim->getNeighbours(loc->getX(), loc->getY(), 1);
        for(auto a:neighbours){
            if (a->diseaseCount()>0) {
                std::vector<std::vector<bool>> diseaseSet = a->getDiseases();
                int index=sim->getRnd(0,(int)(a->diseaseCount())-1);
                if (!subject->hasDisease(diseaseSet[index])) {
                    subject->addDisease(diseaseSet[index]);
                }
            }
            
        }
        //check immunity and update immmunity tags
        std::vector<bool> immunity=subject->getImmunity();
        for(auto infection:subject->getDiseases()){
            if (!subject->isImmune(infection)) {
                
                int bestIndex=0;
                int bestHammingDistance=(int)infection.size()+1;
                int currentScore=0;
                for (int i=0; i<subject->getImmunityLength()-infection.size(); ++i) {
                    for (int k=i; k<infection.size(); ++k) {
                        if (infection[i]!=immunity[i]) {
                            ++currentScore;
                        }
                    }
                    if (currentScore<bestHammingDistance) {
                        bestHammingDistance=currentScore;
                        bestIndex=i;
                    }
                }
                //find first tag not agreeing
                int i=0;
                for (i=0; immunity[bestIndex+i]==infection[i]; ++i) {
                    //EMPTY
                }
                //set tag at index value to new value
                subject->setImmunityTag(infection[i],i);
                
            }
        }
        return true;
    }else{
        return false;//we did nothing
    }

    
    
}
