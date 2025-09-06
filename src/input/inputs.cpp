#include "inputs.hpp"

void InputHandler::update() {
    previousKeys = currentKeys;

    // update the key states again by checking 
    currentKeys[sf::Keyboard::Right] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    currentKeys[sf::Keyboard::Left] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    currentKeys[sf::Keyboard::Up] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    currentKeys[sf::Keyboard::Down] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

bool InputHandler::isKeyPressed(sf::Keyboard::Key key)
{
    auto it = currentKeys.find(key);
    return it != currentKeys.end() && it->second;
}

bool InputHandler::isKeyJustPressed(sf::Keyboard::Key key)  {
    bool currentlyPressed = InputHandler::isKeyPressed(key);
    auto it = previousKeys.find(key);
    bool wasPressed = it != previousKeys.end() && it->second;
    
    return currentlyPressed && !wasPressed;
}

bool InputHandler::isKeyJustReleased(sf::Keyboard::Key key)  {
    bool currentlyPressed = isKeyPressed(key);
    auto it = previousKeys.find(key);
    bool wasPressed = it != previousKeys.end() && it->second;
    
    return !currentlyPressed && wasPressed;
}


void InputHandler::handleEvent(const sf::Event& event) {
    // Handle events that need immediate response (like window close)
    // Most input handling is done in update() method
}