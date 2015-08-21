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
ViewPort::ViewPort(sf::RenderWindow * theWindow, World * aWorld, std::pair<int,int> pix, std::pair<int,int> start,int dim):
    window(theWindow), theWorld(aWorld),pixelCount(pix),startPosition(start),portDimension(dim)
{
    int cellSize=pix.first/portDimension;
    int maxRadius=cellSize/2;
    AgentRepresentations = new sf::CircleShape[portDimension*portDimension];
    for (int i=0; i<portDimension*portDimension; ++i) {
            AgentRepresentations[i].setRadius(maxRadius);
            AgentRepresentations[i].setFillColor(sf::Color::Red);
            AgentRepresentations[i].setPosition((i/portDimension)*cellSize,(i%portDimension)*cellSize);
    }
}
ViewPort::~ViewPort(){
    delete [] AgentRepresentations;
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

    // Display grid
        std::pair<int,int> pos;
        Agent *theAgent=nullptr;
        for (int i=0; i<portDimension; ++i) {
            for (int k=0; k<portDimension; ++k) {
                pos={i,k};
                int radius=-1;
                if (theWorld->getLocation(pos)->hasAgent()) {
                    theAgent=theWorld->getLocation(pos)->getAgent();
                    radius=theAgent->getSugar();
                    AgentRepresentations[i*portDimension+k].setFillColor(sf::Color::Red);
                }
                else{
                    radius=theWorld->getLocation(pos)->getSugar();
                    AgentRepresentations[i*portDimension+k].setFillColor(sf::Color::Green);
                }
                AgentRepresentations[i*portDimension+k].setRadius(radius);
                window->draw(AgentRepresentations[i*portDimension+k]);
            }
        }
    return true;
    
}

