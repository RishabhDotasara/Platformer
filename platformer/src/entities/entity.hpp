#pragma once 
#include <iostream> 
#include <SFML/Graphics.hpp>


class Entity : public sf::Drawable {
    protected: 

        // base shape params
        sf::Vector2f position;
        sf::Vector2f velocity{0.0f,0.0f};
        sf::Vector2f size; 
        sf::Color color{sf::Color::Red};

        // the base shape 
        sf::RectangleShape entity;

        
        

        // physics constants 
        const float GRAVITY{98.0f};
        const float VEL_DEL{10.0f};

        // the draw method from the sf::Drawable class 
    
    private: 
        // overiding to convert this entity into an drawable object on the sfml window
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(entity, states);
        }

    public: 

        // flag to turn on physics on this entity
        bool physical{false};

        Entity();

        // update function to update params each frame 
        // here we will have all physics being updated if it is there. 
        virtual void update(float deltaTime);

        // physics function 
        // void applyPhysics();

        // sprite functions 
        // to be implemented after 
        // void bindSprite()


        // collision detection functions
        // bool isColliding(Entity& other);
        // void resolveCollision(Entity& other);
};

