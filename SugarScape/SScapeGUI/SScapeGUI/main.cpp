
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

#include "ViewPort.h"
#include "World.h"
#include "Growback.h"
#include "SeasonalGrowback.h"
#include "PollutionFormation.h"
#include "GarbageCollection.h"
#include "AgentMove.h"
#include "AgentCulture.h"

int main(int, char const**)
{
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    // create everything
    World theWorld;
    theWorld.init();
    theWorld.sync();
    theWorld.sanityCeck();
    ViewPort theGUI(&window,&theWorld,std::pair<int,int>(800,600),std::pair<int,int>(0,0),20);
    Action *growback= new Growback(&theWorld);
    Action *seasonalGrowback = new SeasonalGrowback(&theWorld);
    Action *move = new AgentMove(&theWorld);
    PollutionFormation pollForm(&theWorld);
    GarbageCollection gc(&theWorld);
    AgentCulture agentCulture(&theWorld);
    theWorld.addRule(&agentCulture);
    theWorld.addRule(&pollForm);
    //theWorld.addRule(seasonalGrowback);
    //theWorld.addRule(&gc);
    theWorld.addRule(move);

    int stepCount=0;
    std::string counter;

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

//    // Load a sprite to display
//    sf::Texture texture;
//    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
//        return EXIT_FAILURE;
//    }
//    sf::Sprite sprite(texture);
//
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    counter = std::to_string(stepCount);
    sf::Text text(counter, font, 50);
    text.setColor(sf::Color::White);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();
        
        theWorld.applyRules();
        theGUI.draw();
        // Draw the sprite
        //window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
        counter = std::to_string(++stepCount);
        text.setString(counter);
        sf::Time t1 = sf::seconds(0.1f);
        sf::sleep(t1);
        theWorld.sanityCeck();
    }

    //tidy up at end
    delete seasonalGrowback;
    delete growback;
    delete move;

    return EXIT_SUCCESS;
}
