#include "gameObject.hpp"

// constructor for shape
gameObject::gameObject() : active(true), spriteManager(nullptr), useSprite(false) {
    shape.setSize({50, 50});
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
}

// constructor for sprite 
gameObject::gameObject(sf::Vector2f pos, sf::Vector2f sz) 
    : position(pos), size(sz), spriteManager(nullptr), useSprite(false) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::White);
}

void gameObject::setActive(bool isActive) { active = isActive; }

bool gameObject::isActive() const { return active; }

const sf::Vector2f& gameObject::getPosition() const{
    return position;
}
 
void gameObject::setPosition(sf::Vector2f newPosition){
    position = newPosition;
    shape.setPosition(position);

    // set for sprite if there 
    if (useSprite && spriteManager && spriteManager->hasSprite(spriteName)){
        spriteManager->setSpritePosition(spriteName, position);
    }
}

void gameObject::setSize(sf::Vector2f sz) {
    size = sz;
    shape.setSize(size);
    
    // Note: Sprites don't change size this way - they use scale
    // You might want to calculate and set sprite scale here
}

const sf::Vector2f& gameObject::getSize() const {
    return size;
}

void gameObject::bindSprite(SpriteManager* manager, const std::string& name) {
    spriteManager = manager;
    spriteName = name;
    useSprite = true;
    
    // Update sprite position to match current position
    if (spriteManager && !spriteName.empty()) {
        spriteManager->setSpritePosition(spriteName, position);
    }
}

void gameObject::unbindSprite() {
    spriteManager = nullptr;
    spriteName.clear();
    useSprite = false;
}

bool gameObject::hasSprite() const {
    return useSprite && spriteManager && !spriteName.empty();
}

std::string gameObject::getSpriteName() const {
    return spriteName;
}

sf::FloatRect gameObject::getBounds() const {
    if (useSprite && spriteManager && !spriteName.empty()) {
        sf::Sprite* sprite = spriteManager->getSprite(spriteName);
        if (sprite) {
            return sprite->getGlobalBounds();
        }
    }
    
    // Fallback to shape bounds
    return sf::FloatRect(position.x, position.y, size.x, size.y);
}