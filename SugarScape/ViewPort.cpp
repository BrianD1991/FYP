//
//  ViewPort.cpp
//  SugarScape
//
//  Created by Joseph Kehoe on 08/06/2015.
//  Copyright (c) 2015 Joseph P Kehoe. All rights reserved.
//

#include "ViewPort.h"
//#include <SFML/Audio.hpp>
//#include <SFML/Graphics.hpp>
// Here is a small helper for you ! Have a look.
//#include "ResourcePath.hpp"


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
//    // Create the main window
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Sugarscape");
//    sf::Vector2u dim = window.getSize();
//    int cellSize=dim.x/portDimension;
//    int maxRadius=cellSize/2;
//    sf::CircleShape * AgentRepresentations[portDimension][portDimension];
//    for (int i=0; i<portDimension; ++i) {
//        for (int k=0; k<portDimension; ++k) {
//            AgentRepresentations[i][k]=new sf::CircleShape(maxRadius);
//            AgentRepresentations[i][k]->setFillColor(sf::Color::Red);
//            AgentRepresentations[i][k]->setPosition(i*40,k*40);
//        }
//    }



}
ViewPort::~ViewPort(){
    //    for (int i=0; i<portDimension; ++i) {
    //        for (int k=0; k<portDimension; ++k) {
    //            delete AgentRepresentations[i][k];
    //        }
    //    }
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
//    // Create a graphical text to display
//    sf::Font font;
//    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
//        return EXIT_FAILURE;
//    }
//    std::string theText="Hello SFML";
//    sf::Text text(theText, font, 50);
//    text.setColor(sf::Color::Black);
    // Display grid
//    if (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            // Close window: exit
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            
//            // Escape pressed: exit
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
//                window.close();
//            }
//        }
//        // Clear screen
//        window.clear();
//        // Draw the string
//        window.draw(text);
//        //draw grid
//        std::pair<int,int> pos;
//        Agent *theAgent;
//        for (int i=0; i<LatticeDim; ++i) {
//            for (int k=0; k<LatticeDim; ++k) {
//                pos.first=i;
//                pos.second=k;
//                if (theWorld->getLocation(pos)->hasAgent()) {
//                    theAgent=theWorld->getLocation(pos)->getAgent();
//                    AgentRepresentations[i][k]->setRadius(theAgent->getSugar());
//                    window.draw(*AgentRepresentations[i][k]);
//                }
//                
//            }
//        }
//        // Update the window
//        window.display();
//    }
    
    return true;
    
}

