#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map> 

class InputHandler 
{
    private: 
    std::unordered_map<sf::Keyboard::Key, bool> previousKeys;
    std::unordered_map<sf::Keyboard::Key, bool> currentKeys;

    public:

    // main function that updates the values in the maps 
    void update();

    bool isKeyPressed(sf::Keyboard::Key key);

    //only single press detection
    bool isKeyJustPressed(sf::Keyboard::Key key);

    //key release detection 
    bool isKeyJustReleased(sf::Keyboard::Key key);

    // 
    void handleEvent(const sf::Event& event);

};