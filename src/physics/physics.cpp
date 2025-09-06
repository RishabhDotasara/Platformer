#include "physics.hpp"
#include <iostream>
#include <cmath>

PhysicalObject::PhysicalObject(Player& player, bool APPLYGRAVITY): OBJECT(player), APPLYGRAVITY(APPLYGRAVITY){}

// Call this every frame for continuous physics (gravity, friction)
void PhysicalObject::update(float deltaTime) {

    // cap max speed
    if (std::abs(VEL.x) > MAXSPEED) {
        VEL.x = (VEL.x > 0 ? 1 : -1) * MAXSPEED;
    }
    if (std::abs(VEL.y) > MAXSPEED) {
        VEL.y = (VEL.y > 0 ? 1 : -1) * MAXSPEED;
    }

   

    std::cout << "Velocity: (" << VEL.x << ", " << VEL.y << ")\n";
    // Always apply gravity
    if (APPLYGRAVITY) {
        VEL.y += GRAVITY * deltaTime;
    }
    
    // Apply friction when no input
    VEL.x -= VEL.x * FRICTION * deltaTime / MASS;
    VEL.y -= VEL.y * FRICTION * deltaTime / MASS;

     // if velocity less than the min speed, decay exponentially 
    if (isOnGround && std::abs(VEL.x) > MIN_VELOCITY && VEL.x != 0) {
        VEL.x *= pow(FRICTION, deltaTime);  // Exponential decay
    } else if (isOnGround) {
        VEL.x = 0;  // Stop completely
    }
   
    
    // Always update position
    OBJECT.setPosition(OBJECT.getPosition() + VEL * deltaTime);
}

// Call this only when button is pressed
void PhysicalObject::applyButtonForce(sf::Vector2i parity, float deltaTime) {
    float buttonAcc = BUTTONFORCE / MASS;
    VEL.x += buttonAcc * deltaTime * parity.x;
    VEL.y += buttonAcc * deltaTime * parity.y;

}