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

int main(int argc, const char * argv[])
{

    // insert code here...
    World theWorld;
    Action *growback= new Growback(&theWorld);
    Action *move = new AgentMove(&theWorld);
    theWorld.addRule(growback);
    theWorld.addRule(move);
    
    
    //tidy up
    delete growback;
    delete move;
    
    if (argc>1) {
        std::cout << "Hello " << argv[1]<<std::endl;
    }
    else
        std::cout << "Hello, World!\n";
    return 0;
}

