//
//  IterativeWriteAction.cpp
//  SugarScape
//
//  Created by Joseph kehoe on 28/08/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "IterativeWriteAction.h"


bool IterativeWriteAction::run(int startX, int startY, int size)
{
        int participants=participantCount(startX, startY, size);
        while (participants>0) {
            WriteAction::run(startX, startY, size);
            participants=participantCount(startX, startY, size);
        }
        sim->resetNeighbours();
        return true;
}


bool IterativeWriteAction::concurrentRun(void)
{
    int sectionSize=sim->getMaxVision();
    /*!< construct tile set - tile contains 9 sections - 3 each side*/
    int tileDim=3*sectionSize;
    int tileNum=sim->getSize()/tileDim;/*!< Assume size%tileDim==0 */
#pragma omp for
    for (int xTile=0; xTile<tileNum; ++xTile) {
#pragma omp for
        for (int yTile=0; yTile<tileNum; ++yTile) {
            //sequentally run through each tile
            for (int i=0; i<3; ++i) {
                for (int k=0; k<3; ++k) {
                    int participants=participantCount((xTile+i)*sectionSize,(yTile+k)*sectionSize,sectionSize);
                    while (participants>0) {
                        WriteAction::run((xTile+i)*sectionSize,(yTile+k)*sectionSize,sectionSize);
                        participants=participantCount((xTile+i)*sectionSize,(yTile+k)*sectionSize,sectionSize);
                    }
                    
                }
            }
        }
    }
    sim->resetNeighbours();
    return true;
}