#pragma once
#include <SFML/Graphics.hpp>


class Player
{
    private:
        sf::RectangleShape player;

    public:

    // constructor
        Player(sf::Vector2f initialPosition);

        //  position getter
        sf::Vector2f getPosition();
        
        // position setter
        void setPosition(sf::Vector2f newPosition);

        // drawable object getter
        const sf::Drawable& getDrawableObject();
};