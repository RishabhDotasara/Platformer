#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "graphics/spriteManager.hpp"

// Forward declaration
class SpriteManager;

class gameObject : public sf::Drawable {
protected:
    bool active{true};
    sf::Vector2f position{0,0};
    sf::Vector2f size{32, 32};           // Default size
    sf::RectangleShape shape;            // Fallback shape
    
    // Sprite integration
    SpriteManager* spriteManager;        // Reference to sprite manager
    std::string spriteName;              // Name of sprite to use
    bool useSprite;                      // Whether to use sprite or fallback shape
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        if (!active) return;
        
        if (useSprite && spriteManager && !spriteName.empty()) {
            // Draw sprite if available
            sf::Sprite* sprite = spriteManager->getSprite(spriteName);
            if (sprite) {
                target.draw(*sprite, states);
                return;
            }
        }
        
        // Fallback to rectangle shape
        target.draw(shape, states);
    }

public:
    gameObject();
    gameObject(sf::Vector2f pos, sf::Vector2f sz = sf::Vector2f(32, 32));
    ~gameObject() = default;

    // Active state management
    void setActive(bool isActive);
    bool isActive() const;
    
    // Position management
    virtual void setPosition(sf::Vector2f pos);
    const sf::Vector2f& getPosition() const;
    
    // Size management
    virtual void setSize(sf::Vector2f sz);
    const sf::Vector2f& getSize() const;
    
    // Sprite management
    void bindSprite(SpriteManager* manager, const std::string& name);
    void unbindSprite();
    bool hasSprite() const;
    std::string getSpriteName() const;
    
    // Collision bounds
    sf::FloatRect getBounds() const;
    
    // Pure virtual function - all game objects must implement
    // virtual void update(float deltaTime) = 0;
};