#pragma once
#include <SFML/Graphics.hpp>
#include "../input/inputs.hpp"
#include "../entities/entity.hpp"
#include "../physics/physics.hpp"
#include "../music/soundManager.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    bool running;
    
    // Game objects
    Player player;
    PhysicalObject physics;
    sf::RectangleShape ground;
    sf::RectangleShape auxGround;
    InputHandler input;

    // music & sound settings
    SoundManager soundManager;

    
    // Private methods
    void handleEvents();
    void update(float deltaTime);
    void render();
    void loadAllSounds();

public:
    Game();
    ~Game() = default;
    
    void run();  // Main game loop
};