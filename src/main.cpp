#include <SFML/Graphics.hpp>
#include "input/inputs.hpp"
#include "entities/entity.hpp"
#include "physics/physics.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer");
    sf::Clock clock;
    
    // Simple player rectangle
    Player player(sf::Vector2f(40,40));
    PhysicalObject physics(player, true);
    // Simple ground for testing
    sf::RectangleShape ground(sf::Vector2f(800, 50));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0, 550);
 
    InputHandler input;
    
    while (window.isOpen()) {

        float deltaTime = clock.restart().asSeconds();  // Time since last frame

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
// Simple ground for testing
    sf::RectangleShape ground(sf::Vector2f(800, 50));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0, 550);
        input.update();
      
        if (input.isKeyPressed(sf::Keyboard::Right))
        {
            physics.applyButtonForce({1,0});
        }
        if (input.isKeyPressed(sf::Keyboard::Left))
        {
            physics.applyButtonForce({-1,0});
        }
        if (input.isKeyPressed(sf::Keyboard::Down))
        {
            physics.applyButtonForce({0,1});
        }
        if (input.isKeyPressed(sf::Keyboard::Up))
        {
            physics.applyButtonForce({0,-1});
        }
        
        physics.update(deltaTime); // Assuming ~60 FPS, so ~16ms per frame

        // Simple ground collision
        if (player.getPosition().y + 40 >= ground.getPosition().y) {
            sf::Vector2f pos = player.getPosition();
            pos.y = ground.getPosition().y - 40;
            player.setPosition(pos);
            physics.isOnGround = true;
            physics.VEL.y = 0;  // Stop falling
        } else {
            physics.isOnGround = false;
        }

        window.clear(sf::Color::Cyan);
        window.draw(player.getDrawableObject());
        window.display();
    }
    return 0;
}