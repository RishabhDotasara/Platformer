#include <SFML/Graphics.hpp>
#include <iostream>
#include "entities/player.hpp"
#include "input/input.hpp"




int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer Game");
    window.setFramerateLimit(60);
    
    // create an input handler instance 
    InputHandler inputHandler;

    // Create an entity
    Player player{sf::Vector2f(20.0f,0.0f), sf::Vector2f(5.0f,-10.0f), &inputHandler};
    player.physical = false;


    // init the clock 
    sf::Clock clock;

    // Main game loop
    while (window.isOpen())
    {

        // get the deltaTime using clocok 
        float deltaTime = clock.restart().asSeconds();

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
                
            // Escape key: exit
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        // input Handler update each frame
        inputHandler.update(deltaTime);

        // Update the entity
        player.update(deltaTime);

        // Clear screen
        window.clear(sf::Color::Black);

        // Draw the entity
        window.draw(player);

        // Update the window
        window.display();
    }

    return 0;
}