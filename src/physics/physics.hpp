#pragma once
#include <SFML/Graphics.hpp>
#include "../entities/entity.hpp"

class PhysicalObject{
    private:
        float GRAVITY{980.0f};
        float MASS{1.0f};
        // the button force here should be high enough to overcome 
        // the frictional force on the first acceleration, else the body won't 
        // accelerate because of the exponential decay of friction for low speed
        float BUTTONFORCE{5000.0f};
        float FRICTION{0.85f};
        bool APPLYGRAVITY{true};
        float MAXSPEED{450.0f};
        float JUMP_FORCE{-450.0f};
        float MIN_VELOCITY{15.0f}; 
        Player& OBJECT;

    public: 
        bool isOnGround{false};
        sf::Vector2f VEL{0, 0};
    // this should further be changed to a general object instead of a player 
        PhysicalObject(Player& object, bool APPLYGRAVITY = true);
        
        // this method for continous forces
        void update(float deltaTime);

        // this method for forces to be applied no button press
        void applyButtonForce(sf::Vector2i parity = {0,0}, float deltaTime = 0.016f); // default deltaTime ~60FPS

};