#pragma once
#include <SFML/Graphics.hpp>
#include "../input/inputs.hpp"
#include "../entities/player.hpp"
#include "../physics/physics.hpp"
#include "../music/soundManager.hpp"
#include "../entities/platform.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    bool running;
    
    // Game objects
    Player player;
    PhysicalObject physics;
    

    // all platforms 
    std::vector<Platform> platforms;


    InputHandler input;

    // managers
    SoundManager soundManager;
    SpriteManager spriteManager;
    
    // Private methods
    void handleEvents();
    void update(float deltaTime);
    void render();
    void loadAllSounds();
    void loadAllSprites();
    void createPlatforms();

public:
    Game();
    ~Game() = default;
    
    void run();  // Main game loop
};