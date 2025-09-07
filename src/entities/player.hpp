#pragma once
#include <SFML/Graphics.hpp>
#include "gameObject.hpp"


class Player : public gameObject
{

    private: 
        sf::RectangleShape player;
    public:

    // constructor
        Player(sf::Vector2f initialPosition);

        // void update(float deltaTime) override;

        // Player specific methods 
        void handleInput();
        void setColor(sf::Color color);
        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f pos);
};