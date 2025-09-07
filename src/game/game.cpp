#include "game.hpp"
#include <iostream>
#include <cmath>
#include <filesystem>

Game::Game() 
    : window(sf::VideoMode(800, 600), "Platformer"),
      running(true),
      player(sf::Vector2f(400, 100)),
      physics(player, true) {
    
    window.setFramerateLimit(60);
    
    

    loadAllSounds();
    loadAllSprites();
    createPlatforms();
}

void Game::run() {
    while (window.isOpen() && running) {
        float deltaTime = clock.restart().asSeconds();


        

        
        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::createPlatforms(){
    if (spriteManager.hasTexture("grass")) {
        spriteManager.createSprite("groundSprite", "grass");
        platforms.emplace_back(sf::Vector2f(0, 550), sf::Vector2f(800, 50), 
                              &spriteManager, "groundSprite");
    } else {
        // Fallback to colored platform
        platforms.emplace_back(sf::Vector2f(0, 550), sf::Vector2f(800, 50), sf::Color::Green);
    }
    // Create floating platform
    if (spriteManager.hasTexture("stone")) {
        spriteManager.createSprite("auxPlatformSprite", "stone");
        platforms.emplace_back(sf::Vector2f(200, 400), sf::Vector2f(500, 20), 
                              &spriteManager, "auxPlatformSprite");
    } else {
        platforms.emplace_back(sf::Vector2f(200, 400), sf::Vector2f(500, 20), sf::Color::Red);
    }

     // Add more platforms
    platforms.emplace_back(sf::Vector2f(600, 300), sf::Vector2f(150, 20), sf::Color::Blue);
    platforms.emplace_back(sf::Vector2f(50, 200), sf::Vector2f(100, 20), sf::Color::Yellow);
    
    std::cout << "Created " << platforms.size() << " platforms" << std::endl;
}



void Game::loadAllSounds(){
    std::cout << "Loading All Sounds..."<<std::endl;

    // load sound effects
    // Get current working directory and construct asset path
    soundManager.loadSound("jump", "assets/sounds/jump.mp3");
    soundManager.loadSound("die", "assets/sounds/die.wav");
    soundManager.loadSound("game_over", "assets/sounds/gameover.wav");
    soundManager.loadSound("warning", "assets/sounds/warning.wav");

    // load music tracks 
    soundManager.loadMusic("1", "assets/music/01.mp3");
    soundManager.loadMusic("2", "assets/music/02.mp3");
    soundManager.loadMusic("3", "assets/music/03.mp3");


    // start the tracks to play 
    soundManager.playMusic("2");


    // configure audio settings
    soundManager.setMasterVolume(80.0f);
    soundManager.setSoundVolume(90.0f);
    soundManager.setMusicVolumeControl(60.0f);

    std::cout << "Music Loading Complete!" << std::endl;
}

void Game::loadAllSprites(){
    std::cout << "Loading Sprites...." << std::endl; 

    // load the main player 
    if (spriteManager.loadTexture("player", "assets/textures/player/Characters/platformChar_idle.png")){
        spriteManager.createSprite("playerSprite", "player");
        
        // bind the sprite to the player;
        player.bindSprite(&spriteManager, "playerSprite");

        spriteManager.setSpriteScale("playerSprite", sf::Vector2f(1.0f,1.0f));
    }


    // load the background
    if (spriteManager.loadTexture("background", "assets/textures/background.jpg")){
        // bind the texture to a sprite to use 
        spriteManager.createSprite("backgroundSprite","background");
        spriteManager.setSpritePosition("backgroundSprite", sf::Vector2f(0,0));

        // Scale background to fit window
        sf::Vector2u bgSize = spriteManager.getTextureSize("background");
        if (bgSize.x > 0 && bgSize.y > 0) {
            float scaleX = 800.0f / bgSize.x;  // Window width / texture width
            float scaleY = 600.0f / bgSize.y;  // Window height / texture height
            
            // Use the smaller scale to maintain aspect ratio, or use both for stretch-to-fit
            float scale = std::min(scaleX, scaleY);  // Maintain aspect ratio
            // float scale = 1.0f; // Or use scaleX, scaleY separately for stretch-to-fit
            
            spriteManager.setSpriteScale("backgroundSprite", sf::Vector2f(scaleX, scaleY));
            std::cout << "Background scaled: " << scaleX << "x" << scaleY << std::endl;
        }
    }


    // Load platform textures
    if (spriteManager.loadTexture("grass", "assets/textures/Tiles/platformPack_tile001.png")){
        // We'll create platform sprites in createPlatforms()
    }

    std::cout << "Finished Loading Sprites and Textures..." << std::endl;
}


void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            running = false;
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                running = false;
            }
        }
    }
}

void Game::update(float deltaTime) {
    input.update();

    // Handle player input
    if (input.isKeyPressed(sf::Keyboard::Right)) {
        physics.applyButtonForce({1,0});
    }
    if (input.isKeyPressed(sf::Keyboard::Left)) {
        physics.applyButtonForce({-1,0});
    }
    if (input.isKeyJustPressed(sf::Keyboard::Space)) {
        // std::cout << "Spacebar Pressed!";
        physics.jump(deltaTime);
        soundManager.playSound("jump",100.0f, 1.0f);
    }

    // exponential decay on speed if less than minimum speed 
    if (abs(physics.VEL.x) < 50.0f && physics.VEL.x != 0){
        // exponential decay 
        physics.VEL.x *= pow(0.85f, deltaTime);
    }
    if (abs(physics.VEL.x) < 15.0f){
        physics.VEL.x = 0;
    }


    // Update physics
    physics.update(deltaTime);

    // Collision detection with all platforms
    for (const auto& platform : platforms) {
        if (physics.isColliding(platform.getBounds())){
            physics.resolveCollision(platform.getBounds());
            break; // Only resolve one collision per frame
        }
    }

    if (player.getPosition().y > 800){
        soundManager.stopMusic();
        soundManager.playSound("die");
        player.setPosition({0, 0});
        // wait for the track to finish and then start again 
        // sf::sleep(sf::seconds(2.0f));
        soundManager.playMusic("1");
    }

}

void Game::render() {
    window.clear(sf::Color::Cyan);

    // draw the sprite background 
    sf::Sprite* background = spriteManager.getSprite("backgroundSprite");
    if (background){
        window.draw(*background);
    }

    // draw all platforms 
    for (const auto& platform : platforms) {
        window.draw(platform);
    }
    

    window.draw(player);
    
    window.display();
}