//
//  main.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 25/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include <chrono>
#include <iostream>
#include <fstream>



#include "World.h"
#include "Growback.h"
#include "SeasonalGrowback.h"
#include "PollutionFormation.h"
#include "GarbageCollection.h"
#include "AgentMove.h"
#include "AgentCulture.h"
#include "AgentDeath.h"
#include "AgentDisease.h"
#include "Diffusion.h"
#include "AgentCombat.h"
#include "AgentReplacement.h"
#include "AgentMetabolism.h"
#include "AgentMating.h"


int benchmark(int,int,int,int,int,std::string);

int benchmark(int numRepeats, int stepCount, int dimStart, int increment, int runs, std::string fileName){
    std::ofstream outputFile(fileName,std::ios::out | std::ios::app);
    for (int i=0; i<runs; ++i) {
        std::chrono::duration <double, std::milli> min;
        std::chrono::duration <double, std::milli> max;
        std::chrono::duration <double, std::milli> avg;
        for (int k=0;k<numRepeats; ++k) {
            // create everything
            std::cout << "SIZE" << dimStart+i*increment << ": ";
            outputFile  << dimStart+i*increment << ",";
            World theWorld(dimStart+i*increment);
            theWorld.init();
            theWorld.sync();
            //theWorld.sanityCeck();
            Growback growback(&theWorld);
            SeasonalGrowback seasonalGrowback(&theWorld);
            AgentMove move(&theWorld);
            PollutionFormation pollForm(&theWorld);
            GarbageCollection gc(&theWorld);
            AgentCulture agentCulture(&theWorld);
            AgentDeath agentDeath(&theWorld);
            AgentDisease agentDisease(&theWorld);
            Diffusion diffusion(&theWorld);
            AgentCombat agentCombat(&theWorld);
            AgentReplacement agentReplacement(&theWorld);
            AgentMetabolism agentMetabolism(&theWorld);
            AgentMating agentMating(&theWorld);
            
            
            //!
            /*!
             Add the rules we are using here.
             */
            theWorld.addRule(&growback);
            //theWorld.addRule(&seasonalGrowback);
            //theWorld.addRule(&pollForm);
            //theWorld.addRule(&diffusion);
            
            theWorld.addRule(&agentMetabolism);
            theWorld.addRule(&move);
            //theWorld.addRule(&agentCombat);
            
            //theWorld.addRule(&agentCulture);
            //theWorld.addRule(&agentDisease);
            
            theWorld.addRule(&agentMating);
            //theWorld.addRule(&agentReplacement);
            theWorld.addRule(&agentDeath);

            
            
            auto start = std::chrono::steady_clock::now();
            for (int m=0; m<stepCount; ++m) {
                //step
                theWorld.applyRules();
            }
            auto end = std::chrono::steady_clock::now();
            auto diff = end - start;
            if (k==0) {
                min=max=avg=diff;
            }else{
                if (diff<min) min=diff;
                if (diff>max) max=diff;
                avg +=diff;
            }
            std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms ";
            std::cout  << std::chrono::duration <double, std::nano> (diff).count() << " ns " ;
            std::cout << "Agents:" << theWorld.getAgentCount() <<std::endl;
            outputFile  << std::chrono::duration <double, std::milli> (diff).count() << ",";
            outputFile  << std::chrono::duration <double, std::nano> (diff).count() << ","
                        << theWorld.getAgentCount() <<std::endl;
        }
        avg=avg/stepCount;
        std::cout << "MIN:" << std::chrono::duration <double, std::milli> (min).count()
                <<" MAX:" << std::chrono::duration <double, std::milli> (max).count()
        <<" AVG:" << std::chrono::duration <double, std::milli> (avg).count() << std::endl;
        
    }
    outputFile.close();
    return 0;
}

int main(int, char const**)
{
    
    benchmark(1,50, 50, 50, 2, "/Users/joseph/test200.txt");
    return 0;
}

