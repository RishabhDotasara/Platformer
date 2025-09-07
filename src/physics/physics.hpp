#pragma once
#include <SFML/Graphics.hpp>
#include "../entities/gameObject.hpp"

class PhysicalObject{
    private:
        float GRAVITY{1500.0f};
        float MASS{1.0f};
        // the button force here should be high enough to overcome 
        // the frictional force on the first acceleration, else the body won't 
        // accelerate because of the exponential decay of friction for low speed
        float BUTTONFORCE{40000.0f};
        float FRICTION{1.0f};
        bool APPLYGRAVITY{true};
        float MAXSPEED{500.0f};
        float JUMP_FORCE{-2000.0f};
        float MIN_VELOCITY{300.0f}; 
        gameObject& OBJECT;

    public: 
        bool isOnGround{false};
        sf::Vector2f VEL{0, 0};
    // this should further be changed to a general object instead of a player 
        PhysicalObject(gameObject& object, bool APPLYGRAVITY = true);
        
        // this method for continous forces
        void update(float deltaTime);

        // this method for forces to be applied no button press
        void applyButtonForce(sf::Vector2i parity = {0,0}, float deltaTime = 0.016f); // default deltaTime ~60FPS
        
        // jump method 
        void jump(float deltaTime);

        // collision detection and resolution 
        bool isColliding(const gameObject& other);
        bool isColliding(const sf::FloatRect& bounds) const;
        sf::FloatRect getBounds() const;
    
        
        void resolveCollision(const gameObject& other);
        void resolveCollision(const sf::FloatRect& bounds);
};  