#pragma once
#include <iostream> 
#include <unordered_map>
#include <SFML/Window.hpp>
#include <functional>




class InputHandler {
    private: 
        // map to store the state of the key at any timeframe 
        std::unordered_map<sf::Keyboard::Key, bool> currentKeys;
        std::unordered_map<sf::Keyboard::Key, std::function<void()>> keyBindings;


    public:

        // constructor 
        InputHandler();

        // have some state methods, getters and setters 
        bool keyDown(sf::Keyboard::Key key);
        bool keyUp(sf::Keyboard::Key key);

        // to check if a key is already bound to some other function
        bool isKeyBound(sf::Keyboard::Key key);
        void bindKey(sf::Keyboard::Key key, std::function<void()> func);
        void releaseKey(sf::Keyboard::Key);


        // a public update function to update the states each frame 
        void update(float deltaTime);

};