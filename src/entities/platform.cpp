#include "platform.hpp"

Platform::Platform(sf::Vector2f pos, sf::Vector2f size, sf::Color color) : gameObject(pos, size) {
    shape.setFillColor(color);
}

// contructor for sprite 
Platform::Platform(sf::Vector2f pos, sf::Vector2f size, SpriteManager* spriteManager, const std::string spriteName) : gameObject(pos, size) {

    if (spriteManager && spriteManager->hasSprite(spriteName)){
        bindSprite(spriteManager, spriteName);

        // Scale sprite to match platform size
        sf::Sprite* sprite = spriteManager->getSprite(spriteName);
        if (sprite) {
            sf::Vector2u textureSize = sprite->getTexture()->getSize();
            if (textureSize.x > 0 && textureSize.y > 0) {
                float scaleX = size.x / textureSize.x;
                float scaleY = size.y / textureSize.y;
                spriteManager->setSpriteScale(spriteName, sf::Vector2f(scaleX, scaleY));
            }
        }
    }
    else 
    {
        shape.setFillColor(sf::Color::Red); // Default color if sprite not found
        std::cerr << "Sprite not found: " << spriteName << ". Using fallback shape" << std::endl;
    }
}

void Platform::setColor(sf::Color color) {
    shape.setFillColor(color);
}

void Platform::setTilePattern(int tilesX, int tilesY) {
    if (useSprite && spriteManager && !spriteName.empty()) {
        sf::Sprite* sprite = spriteManager->getSprite(spriteName);
        if (sprite) {
            // Set texture to repeat across the platform
            sf::Vector2u textureSize = sprite->getTexture()->getSize();
            sf::IntRect textureRect(0, 0, textureSize.x * tilesX, textureSize.y * tilesY);
            spriteManager->setTextureRect(spriteName, textureRect);
        }
    }
}