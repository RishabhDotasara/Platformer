#include "spriteManager.hpp"

bool SpriteManager::loadTexture(const std::string& name, const std::string& filePath) {
    // Check if texture already loaded
    if (textures.find(name) != textures.end()) {
        std::cout << "Texture '" << name << "' already loaded!" << std::endl;
        return true;
    }
    
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Error: Failed to load texture '" << name << "' from: " << filePath << std::endl;
        return false;
    }
    
    // Enable smooth filtering for better quality
    texture.setSmooth(true);
    
    textures[name] = std::move(texture);
    std::cout << "Successfully loaded texture: " << name << " (" 
              << texture.getSize().x << "x" << texture.getSize().y << ")" << std::endl;
    return true;
}

sf::Texture* SpriteManager::getTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it != textures.end()) {
        return &it->second;
    }
    
    std::cerr << "Error: Texture '" << name << "' not found!" << std::endl;
    return nullptr;
}

bool SpriteManager::hasTexture(const std::string& name) const {
    return textures.find(name) != textures.end();
}

bool SpriteManager::createSprite(const std::string& name, const std::string& textureName) {
    // Check if sprite already exists
    if (sprites.find(name) != sprites.end()) {
        std::cout << "Sprite '" << name << "' already exists!" << std::endl;
        return true;
    }
    
    // Check if texture exists
    auto textureIt = textures.find(textureName);
    if (textureIt == textures.end()) {
        std::cerr << "Error: Cannot create sprite '" << name 
                  << "' - texture '" << textureName << "' not found!" << std::endl;
        return false;
    }
    
    sf::Sprite sprite;
    sprite.setTexture(textureIt->second);
    sprites[name] = sprite;
    
    std::cout << "Successfully created sprite: " << name << std::endl;
    return true;
}

sf::Sprite* SpriteManager::getSprite(const std::string& name) {
    auto it = sprites.find(name);
    if (it != sprites.end()) {
        return &it->second;
    }
    
    std::cerr << "Error: Sprite '" << name << "' not found!" << std::endl;
    return nullptr;
}

bool SpriteManager::hasSprite(const std::string& name) const {
    return sprites.find(name) != sprites.end();
}

void SpriteManager::setSpritePosition(const std::string& spriteName, const sf::Vector2f& position) {
    sf::Sprite* sprite = getSprite(spriteName);
    if (sprite) {
        sprite->setPosition(position);
    }
}

void SpriteManager::setSpriteScale(const std::string& spriteName, const sf::Vector2f& scale) {
    sf::Sprite* sprite = getSprite(spriteName);
    if (sprite) {
        sprite->setScale(scale);
    }
}

void SpriteManager::setTextureRect(const std::string& spriteName, const sf::IntRect& rect) {
    sf::Sprite* sprite = getSprite(spriteName);
    if (sprite) {
        sprite->setTextureRect(rect);
    }
}

void SpriteManager::setSpriteRotation(const std::string& spriteName, float angle) {
    sf::Sprite* sprite = getSprite(spriteName);
    if (sprite) {
        sprite->setRotation(angle);
    }
}

void SpriteManager::setSpriteOrigin(const std::string& spriteName, const sf::Vector2f& origin) {
    sf::Sprite* sprite = getSprite(spriteName);
    if (sprite) {
        sprite->setOrigin(origin);
    }
}

void SpriteManager::listLoadedTextures() const {
    std::cout << "Loaded textures (" << textures.size() << "):" << std::endl;
    for (const auto& pair : textures) {
        auto size = pair.second.getSize();
        std::cout << "  - " << pair.first << " (" << size.x << "x" << size.y << ")" << std::endl;
    }
}

void SpriteManager::listLoadedSprites() const {
    std::cout << "Created sprites (" << sprites.size() << "):" << std::endl;
    for (const auto& pair : sprites) {
        auto bounds = pair.second.getGlobalBounds();
        std::cout << "  - " << pair.first << " (pos: " << bounds.left 
                  << "," << bounds.top << ", size: " << bounds.width 
                  << "x" << bounds.height << ")" << std::endl;
    }
}

sf::Vector2u SpriteManager::getTextureSize(const std::string& textureName) const {
    auto it = textures.find(textureName);
    if (it != textures.end()) {
        return it->second.getSize();
    }
    return sf::Vector2u(0, 0);
}

void SpriteManager::removeSprite(const std::string& name) {
    auto it = sprites.find(name);
    if (it != sprites.end()) {
        sprites.erase(it);
        std::cout << "Removed sprite: " << name << std::endl;
    }
}

void SpriteManager::removeTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it != textures.end()) {
        // Check if any sprites are using this texture
        bool textureInUse = false;
        for (const auto& spritePair : sprites) {
            if (spritePair.second.getTexture() == &it->second) {
                std::cerr << "Warning: Cannot remove texture '" << name 
                          << "' - sprite '" << spritePair.first << "' is using it!" << std::endl;
                textureInUse = true;
            }
        }
        
        if (!textureInUse) {
            textures.erase(it);
            std::cout << "Removed texture: " << name << std::endl;
        }
    }
}

void SpriteManager::clear() {
    sprites.clear();
    textures.clear();
    std::cout << "Cleared all textures and sprites" << std::endl;
}