#include "player.hpp"


// we are here getting the same Inputhandler and not creating a new one, so as to maintain single key bindings across whole game
// which prevents us from assigning same key to multiple functions

Player::Player(sf::Vector2f pos, sf::Vector2f vel, InputHandler* inputHandler){
    // init the player with these parameters 
    position = pos; 
    vel = vel;

    // sync the shape with the variables 
    entity.setPosition(pos);


    // set the important flags here in the contructor
    // like we want the player to always have some physics 
    // so we will set physical to true.
    physical = true;


    // setup the key bindings for the player 
    inputHandler->bindKey(sf::Keyboard::Up, [this]() { this->moveUp(); });
    inputHandler->bindKey(sf::Keyboard::Down, [this]() { this->moveDown(); });
    inputHandler->bindKey(sf::Keyboard::Left, [this]() { this->moveLeft(); });
    inputHandler->bindKey(sf::Keyboard::Right, [this]() { this->moveRight(); });
}


// implement the four functions to move the players 
// we will not use any acceleration here in updating the positions, 
// simple position manipulation without acceleration.
void Player::moveUp(){
    position.y -= speed.y;
}
void Player::moveDown(){
    position.y += speed.y;
}

void Player::moveLeft(){
    position.x -= speed.x;
}

void Player::moveRight(){
    position.x += speed.x;
}

// implement the setter and getter functions 

void Player::setPosition(sf::Vector2f pos){
    position = pos;
}

sf::Vector2f Player::getPosition(){
    return position;
}