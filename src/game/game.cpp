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
    
    // Initialize ground
    ground.setSize(sf::Vector2f(8000, 50));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0, 550);
    
    // second ground 
    auxGround.setSize(sf::Vector2f(500, 20));
    auxGround.setFillColor(sf::Color::Red);
    auxGround.setPosition(0, 500);

    loadAllSounds();
}

void Game::run() {
    while (window.isOpen() && running) {
        float deltaTime = clock.restart().asSeconds();


        if (player.getPosition().y > 800){
            soundManager.stopMusic();
            soundManager.playSound("die");
            player.setPosition({0, 0});
            // wait for the track to finish and then start again 
            // sf::sleep(sf::seconds(2.0f));
            soundManager.playMusic("1");
        }

        
        handleEvents();
        update(deltaTime);
        render();
    }
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
    
     // collision detection 
    if (physics.isColliding(ground.getGlobalBounds())){
        physics.resolveCollision(ground.getGlobalBounds());
    }

    if (physics.isColliding(auxGround.getGlobalBounds())){
        physics.resolveCollision(auxGround.getGlobalBounds());
    }

}

void Game::render() {
    window.clear(sf::Color::Cyan);
    
    window.draw(ground);
    window.draw(auxGround);
    window.draw(player);
    
    window.display();
}