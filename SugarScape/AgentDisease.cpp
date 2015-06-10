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
/**
 * If agent X resides at this location find its neighbours and collect diseases from them
 * then update agent X's immunity tags for these diseases
 * @param loc :Location we are checking
 * @see Disease Rule
 * @return True if agent was here
 * @exception none
 */
bool AgentDisease::executeAction(Location *loc, group*){

    if (loc->hasAgent()) {
        Agent * subject=loc->getAgent();
        //Add one disease from each neighbour
        std::vector<Agent*> neighbours=sim->getNeighbours(loc->getX(), loc->getY(), 1);
        for(auto a:neighbours){
            if (a->diseaseCount()>0) {
                std::vector<std::vector<bool>> diseaseSet = a->getDiseases();
                int index=sim->getRnd(0,(int)(a->diseaseCount())-1);
                if (!subject->hasDisease(diseaseSet[index])) {
                    subject->addDisease(diseaseSet[index]);//new disease contracted
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
                //!
                /*!
                 Check each substring for Hamming distance
                 */
                for (int startIndex=0; startIndex<subject->getImmunityLength()-infection.size(); ++startIndex) {
                    //!
                    /*!
                     Calculate Hamming distance of current substring
                     */
                    for (int k=0; k<infection.size(); ++k) {
                        if (infection[k]!=immunity[k+startIndex]) {
                            ++currentScore;
                        }
                    }
                    //!
                    /*!
                     Is current substring the closest so far?
                     */
                    if (currentScore<bestHammingDistance) {
                        bestHammingDistance=currentScore;
                        bestIndex=startIndex;
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
        return true;//agent updated
    }else{//no agent here
        return false;//we did nothing
    }

    
    
}
