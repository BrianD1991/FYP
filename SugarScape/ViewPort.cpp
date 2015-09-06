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
    cellSize=pix.second/portDimension;
    int maxRadius=cellSize/2;
    AgentRepresentations = new sf::CircleShape[portDimension*portDimension];
    for (int i=0; i<portDimension*portDimension; ++i) {
            AgentRepresentations[i].setRadius(maxRadius);
            AgentRepresentations[i].setFillColor(sf::Color::Yellow);
            AgentRepresentations[i].setPosition((i/portDimension)*cellSize,(i%portDimension)*cellSize);
            //AgentRepresentations[i].setOrigin(maxRadius, -maxRadius);
    }
}

/**
 * destructor - delete array of shape pointers
 */
ViewPort::~ViewPort(){
    delete [] AgentRepresentations;
}


/*!< Setters */


/**
 * Sets new start position (top left corner) for drawable area of lattice
 * @param newStart
 * @return new starting position
 * @exception none
 */
std::pair<int,int> ViewPort::setStartPositions(std::pair<int,int> newStart)
{
    std::pair<int,int> old=startPosition;
    startPosition=newStart;
    return old;
}

/**
 * Sets size of drawable area
 * @param newDim
 * @return old dimension size
 * @exception none
 */
int ViewPort::setSize(int newDim){
    int old=portDimension;
    portDimension=newDim;
    return old;
    
}


/**
 * Sets num of pixels in screen drawing area
 * @param newPixels
 * @return old pixel count
 * @exception none
 */
std::pair<int,int> ViewPort::setPixels(std::pair<int,int> newPixels)
{
    std::pair<int,int> old=pixelCount;
    pixelCount=newPixels;
    return old;
}

/*!< Getters */

/**
 * returns start position of lattice we are drawing (top-left corner)
 * @return startPosition
 * @exception none
 */
std::pair<int,int>  ViewPort::getStartPosition()
{
    return startPosition;
}

/**
 * Pixelcount of drawing area
 * @return PixelCount
 * @exception none
 */
std::pair<int,int>  ViewPort::getPixelCount()
{
    return pixelCount;
}

/**
 * retruns number of Lattice locations we are drawing
 * @return portDimension
 * @exception none
 */
int                 ViewPort::getSize()
{
    return portDimension;
}

/*!< Draw Method */
/**
 * Draws lattice grid on screen
 * @return true
 * @exception none
 */
bool ViewPort::draw(){
    int agentCount=0;
    // Display grid
        std::pair<int,int> pos;
        Agent *theAgent=nullptr;
        for (int i=startPosition.first; i<portDimension; ++i) {
            for (int k=startPosition.second; k<portDimension; ++k) {
                pos={i,k};
                int radius=-1;
                Location *currLocation=theWorld->getLocation(pos);
                if (currLocation->hasAgent()) {
                    agentCount++;
                    theAgent=theWorld->getLocation(pos)->getAgent();
                    radius=theAgent->getSugar();
                    if (theAgent->getTribe()==affiliation::blue) {
                        AgentRepresentations[i*portDimension+k].setFillColor(sf::Color::Blue);
                    }
                    else{
                        AgentRepresentations[i*portDimension+k].setFillColor(sf::Color::Red);
                    }
                    
                }
                else{
                    radius=theWorld->getLocation(pos)->getSugar();
                    AgentRepresentations[i*portDimension+k].setFillColor(sf::Color::Green);
                }
                if (radius>cellSize/2) {
                    radius=cellSize/2;
                }
                AgentRepresentations[i*portDimension+k].setRadius(radius);
                window->draw(AgentRepresentations[i*portDimension+k]);
            }
        }
    std::cout << "Painted Count is: " << agentCount <<std::endl;
    return true;
    
}

