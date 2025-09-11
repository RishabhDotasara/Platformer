#include "input.hpp"


// initialise the constructor 
InputHandler::InputHandler(){
    // initialise all keys as false 
    // all keys (enumerations) are internally represented using integers
    for (int key = sf::Keyboard::A; key <= sf::Keyboard::KeyCount; key++){
        currentKeys[static_cast<sf::Keyboard::Key> (key)] = false;
    }
}

bool InputHandler::keyDown(sf::Keyboard::Key key){
    return currentKeys[key] == true;
}

bool InputHandler::keyUp(sf::Keyboard::Key key){
    return currentKeys[key] == false;
}

bool InputHandler::isKeyBound(sf::Keyboard::Key key){
    return keyBindings.find(key) != keyBindings.end();
}

void InputHandler::bindKey(sf::Keyboard::Key key, std::function<void()> func){
    // if the key is bound 
    if(isKeyBound(key)) {
        std::cout << "Key " << key << "is already bound to a function Release the key before binding to a new function!";
        return;
    }

    keyBindings[key] = func;
}

void InputHandler::releaseKey(sf::Keyboard::Key key){
    keyBindings.erase(key);
}


// the update each frame function 
void InputHandler::update(float deltaTime){
    // ig we dont need this deltaTime here though 
    // so here we are going to check the tasks that need to be check each frame like:
    // - check the state of the keys again
    // - call all the functions that meant for the keys if the particular key is down

    // update the key states
    for (int key = sf::Keyboard::A; key <= sf::Keyboard::KeyCount; key++){
        sf::Keyboard::Key sfKey = static_cast<sf::Keyboard::Key>(key);
        if (sf::Keyboard::isKeyPressed(sfKey)){
            currentKeys[sfKey] = true;
            if (isKeyBound(sfKey)){
                keyBindings[sfKey]();
            }
        }
        else {
            currentKeys[sfKey] = false;
        }
    }
}