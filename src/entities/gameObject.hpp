#pragma once
#include <SFML/Graphics.hpp>


class gameObject : public sf::Drawable {
    protected:
        bool active{true};
        sf::Vector2f position{0,0};
        sf::RectangleShape shape;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            // Default implementation (can be empty or provide basic drawing)
            if (active){
                target.draw(shape, states);
            }
        }
    public:
        gameObject();
        virtual ~gameObject();

        void setActive(bool isActive);
        bool isActive() const;

        // getter and setter for position
        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f newPosition);

        // collision detection helpers 
        sf::FloatRect getBounds() const {
            return shape.getGlobalBounds();
        }
        
};