//
//  main.cpp
//  SugarScape
//
//  Created by Joseph P Kehoe on 25/04/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include <iostream>
#include "World.h"
#include "Growback.h"
#include "AgentMove.h"
#include "ViewPort.h"

int main(int argc, const char * argv[])
{

    // create everything
    World theWorld;
    ViewPort theGUI(&theWorld,std::pair<int,int>(800,600),std::pair<int,int>(0,0),40);
    Action *growback= new Growback(&theWorld);
    Action *move = new AgentMove(&theWorld);
    theWorld.addRule(growback);
    theWorld.addRule(move);
    
    //step through sim
    bool ok=true;
    while (ok) {
        theWorld.applyRules();
        theGUI.draw();
    
    }
    
    
    
    //tidy up at end
    delete growback;
    delete move;
    

    return 0;
}

