//
//  ViewPort.h
//  SugarScape
//
//  Created by Joseph Kehoe on 08/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#ifndef __SugarScape__ViewPort__
#define __SugarScape__ViewPort__

#include <iostream>
#include "Location.h"
#include "World.h"


/*!  \class  ViewPort
 \brief Window that draws section of simulation space
 
 Draws a section of the grid on the screen. Draws from (startX,startY) to
 (startX+portDimension,startY+portDimension).
 Uses (PixelX,pixelY) pixels
 */

class ViewPort{
private:
    std::pair<int,int> startPosition;
    std::pair<int,int> pixelCount;
    int portDimension;
    World *theWorld;
    
public:
    /*!< Constructor */
    ViewPort(World *, std::pair<int,int>, std::pair<int,int>,int dim=20);
    
    /*!< Draw Method */
    bool draw();
    
    /*!< Setters */
    std::pair<int,int>  setStartPositions(std::pair<int,int>);
    int                 setSize(int);
    std::pair<int,int>  setPixels(std::pair<int,int>);
    
    /*!< Getters */
    std::pair<int,int>  getStartPosition();
    std::pair<int,int>  getPixelCount();
    int                 getSize();

};





#endif /* defined(__SugarScape__ViewPort__) */
