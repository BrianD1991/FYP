//
//  ViewPort.cpp
//  SugarScape
//
//  Created by Joseph Kehoe on 08/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "ViewPort.h"


/**
 * Constructor
 * @param aWorld :World we want to draw
 * @param pix :number of pixels in window
 * @param start :starting location (upper left corner) of window
 * @param dim :dimensions of window
 * @see ViewPort
 * @exception none
 */
ViewPort::ViewPort(World * aWorld, std::pair<int,int> pix, std::pair<int,int> start,int dim):
    theWorld(aWorld),pixelCount(pix),startPosition(start),portDimension(dim)
{
    //our work is done!
}



/*!< Setters */
std::pair<int,int> ViewPort::setStartPositions(std::pair<int,int> newStart)
{
    std::pair<int,int> old=startPosition;
    startPosition=newStart;
    return old;
}


int ViewPort::setSize(int newDim){
    int old=portDimension;
    portDimension=newDim;
    return old;
    
}


std::pair<int,int> ViewPort::setPixels(std::pair<int,int> newPixels)
{
    std::pair<int,int> old=pixelCount;
    pixelCount=newPixels;
    return old;
}

/*!< Getters */
std::pair<int,int>  ViewPort::getStartPosition()
{
    return startPosition;
}

std::pair<int,int>  ViewPort::getPixelCount()
{
    return pixelCount;
}

int                 ViewPort::getSize()
{
    return portDimension;
}

/*!< Draw Method */
bool ViewPort::draw(){
    return true;
    
}

