#include "entity.hpp"

// Constructor
Player::Player(sf::Vector2f initialPosition) {
    player.setSize(sf::Vector2f(32, 48));  // Set player size (width, height)
    player.setFillColor(sf::Color::Red);   // Set player color
    player.setPosition(initialPosition);   // Set initial position
}

// Position getter
sf::Vector2f Player::getPosition() {
    return gameObject::getPosition();
}

// Position setter
void Player::setPosition(sf::Vector2f newPosition) {
    gameObject::setPosition(newPosition);
}

