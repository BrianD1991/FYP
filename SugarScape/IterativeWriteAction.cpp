//
//  IterativeWriteAction.cpp
//  SugarScape
//
//  Created by Joseph kehoe on 28/08/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "IterativeWriteAction.h"

/**
 * Construtor - pass World Pointer back to base class constructor
 * @param sim :Pointer to World Object
 * @exception none
 */
IterativeWriteAction::IterativeWriteAction(World *sim)
:WriteAction(sim)
{
    //our work is done
}


/**
 * run action iteratively.  Call run until we have performed action on all possible neighbours
 * @param startX :X-coordinate of top left corner of grid we are running on
 * @param startY :Y-coordinate of top left corner of grid we are working on
 * @param size :Dimensions of grid
 * @return true
 * @exception none
 */
bool IterativeWriteAction::run(int startX, int startY, int size)
{
        int participants=participantCount(startX, startY, size);
        while (participants>0) {
            WriteAction::run(startX, startY, size);
            sim->sync();/*!< *MUST* sync before iterating */
            participants=participantCount(startX, startY, size);
        }
        sim->resetNeighbours();
        return true;
}


/**
 * Concurrent version of run. Tiled algorithm from base class but call run iteratively on each subtile
 * @return true
 * @exception none
 */
bool IterativeWriteAction::concurrentRun(void)
{
    int participants=participantCount(0, 0, sim->getSize());
    while (participants>0) {
        WriteAction::concurrentRun();
        sim->sync();/*!< *MUST* sync before iterating */
        participants=participantCount(0, 0, sim->getSize());
    }
    sim->resetNeighbours();
    return true;

}
