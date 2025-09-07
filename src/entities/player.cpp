#include "player.hpp"

// Constructor
Player::Player(sf::Vector2f initialPosition) {
   player.setFillColor(sf::Color::Red);
}

// Position getter
sf::Vector2f Player::getPosition() {
    return gameObject::getPosition();
}

// Position setter
void Player::setPosition(sf::Vector2f newPosition) {
    gameObject::setPosition(newPosition);
}

void Player::setColor(sf::Color color){
    player.setFillColor(color);
}

