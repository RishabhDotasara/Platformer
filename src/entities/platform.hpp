#include "gameObject.hpp"
#include <iostream>


class Platform : public gameObject {

    public:
        Platform(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
        Platform(sf::Vector2f pos, sf::Vector2f size, SpriteManager* spriteManager, const std::string spriteName);


        void setColor(sf::Color color);
        void setTilePattern(int tilesX, int tilesY);

};