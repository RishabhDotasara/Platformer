#include "physics.hpp"
#include <iostream>
#include <cmath>

PhysicalObject::PhysicalObject(gameObject& player, bool APPLYGRAVITY): OBJECT(player), APPLYGRAVITY(APPLYGRAVITY){}

// Call this every frame for continuous physics (gravity, friction)
void PhysicalObject::update(float deltaTime) {

    // cap max speed
    if (std::abs(VEL.x) > MAXSPEED) {
        VEL.x = (VEL.x > 0 ? 1 : -1) * MAXSPEED;
    }
    if (std::abs(VEL.y) > MAXSPEED) {
        VEL.y = (VEL.y > 0 ? 1 : -1) * MAXSPEED;
    }

   

    // std::cout << "Velocity: (" << VEL.x << ", " << VEL.y << ")\n";
    // Always apply gravity
    if (APPLYGRAVITY) {
        VEL.y += GRAVITY * deltaTime;
    }
    
    // Apply friction when no input
    VEL.x -= VEL.x * FRICTION * deltaTime / MASS;
    // VEL.y -= VEL.y * FRICTION * deltaTime / MASS;

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
    if (isOnGround){
        float buttonAcc = BUTTONFORCE / MASS;
        VEL.x += buttonAcc * deltaTime * parity.x;
        VEL.y += buttonAcc * deltaTime * parity.y;
    }

}

void PhysicalObject::jump(float deltaTime){
    if(isOnGround){
        VEL.y = JUMP_FORCE/MASS;
        isOnGround = false;
    }
}




sf::FloatRect PhysicalObject::getBounds() const {
    return OBJECT.getBounds();
}

bool PhysicalObject::isColliding(const gameObject& other){
    // implementbounding boxes collision detection 
    sf::FloatRect thisBounds = OBJECT.getBounds();
    sf::FloatRect otherBounds = other.getBounds();
    return thisBounds.intersects(otherBounds);
}

bool PhysicalObject::isColliding(const sf::FloatRect& bounds) const {
    sf::FloatRect thisBounds = OBJECT.getBounds();
    return thisBounds.intersects(bounds);
}

void PhysicalObject::resolveCollision(const gameObject& other){
    resolveCollision(other.getBounds());
}


void PhysicalObject::resolveCollision(const sf::FloatRect& bounds){
    sf::FloatRect thisBounds = OBJECT.getBounds();
    sf::FloatRect otherBounds = bounds;

    // check if  collision 
    if (!thisBounds.intersects(bounds)){
        return ;
    }


    //  main idea is here is to calculate how much the other object is inside
    // the OBJECT and from which side, whichever is more, we resolve collision
    // on that side.
    float overlapLeft = (thisBounds.left + thisBounds.width) - bounds.left;   // How much we're inside from left
    float overlapRight = (bounds.left + bounds.width) - thisBounds.left;      // How much we're inside from right
    float overlapTop = (thisBounds.top + thisBounds.height) - bounds.top;     // How much we're inside from top
    float overlapBottom = (bounds.top + bounds.height) - thisBounds.top;      // How much we're inside from bottom
    
    // Find the minimum overlap (this is the direction to resolve)
    float minOverlapX = std::min(overlapLeft, overlapRight);
    float minOverlapY = std::min(overlapTop, overlapBottom);

    sf::Vector2f currentPos = OBJECT.getPosition();
     if (minOverlapX < minOverlapY) {
        // Horizontal collision - resolve on X axis
        if (overlapLeft < overlapRight) {
            // Collision from right side - move object left
            currentPos.x = bounds.left - thisBounds.width;
            if (VEL.x > 0) VEL.x = 0; // Stop moving right
            std::cout << "Right collision - moved left\n";
        } else {
            // Collision from left side - move object right
            currentPos.x = bounds.left + bounds.width;
            if (VEL.x < 0) VEL.x = 0; // Stop moving left
            std::cout << "Left collision - moved right\n";
        }
    } else {
        // Vertical collision - resolve on Y axis
        if (overlapTop < overlapBottom) {
            // Collision from bottom - move object up (landing on platform)
            currentPos.y = bounds.top - thisBounds.height;
            if (VEL.y > 0) {
                VEL.y = 0; // Stop falling
                isOnGround = true; // Player is now on ground
            }
            std::cout << "Bottom collision - landed on platform\n";
        } else {
            // Collision from top - move object down (hit ceiling)
            currentPos.y = bounds.top + bounds.height;
            if (VEL.y < 0) VEL.y = 0; // Stop jumping up
            std::cout << "Top collision - hit ceiling\n";
        }
    }
    
    // Apply the corrected position
    OBJECT.setPosition(currentPos);
    
    
}