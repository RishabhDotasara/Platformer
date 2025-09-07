#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>

class SpriteManager {
private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Sprite> sprites;
    
public:
    SpriteManager() = default;
    ~SpriteManager() = default;
    
    // Texture management
    bool loadTexture(const std::string& name, const std::string& filePath);
    sf::Texture* getTexture(const std::string& name);
    bool hasTexture(const std::string& name) const;
    
    // Sprite management
    bool createSprite(const std::string& name, const std::string& textureName);
    sf::Sprite* getSprite(const std::string& name);
    bool hasSprite(const std::string& name) const;
    
    // Sprite manipulation
    void setSpritePosition(const std::string& spriteName, const sf::Vector2f& position);
    void setSpriteScale(const std::string& spriteName, const sf::Vector2f& scale);
    void setTextureRect(const std::string& spriteName, const sf::IntRect& rect);
    void setSpriteRotation(const std::string& spriteName, float angle);
    void setSpriteOrigin(const std::string& spriteName, const sf::Vector2f& origin);
    
    // Utility functions
    void listLoadedTextures() const;
    void listLoadedSprites() const;
    sf::Vector2u getTextureSize(const std::string& textureName) const;
    
    // Cleanup
    void removeSprite(const std::string& name);
    void removeTexture(const std::string& name);
    void clear();
};