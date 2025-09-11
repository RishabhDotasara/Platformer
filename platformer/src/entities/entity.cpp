#include "entity.hpp"



Entity::Entity(){
    // Set default position and size
    position = sf::Vector2f(100.0f, 100.0f);
    size = sf::Vector2f(50.0f, 50.0f);
    
    // Configure the rectangle shape
    entity.setPosition(position);
    entity.setSize(size);
    entity.setFillColor(color);
}

void Entity::update(float deltaTime){
    // here update all the params that you want to update 
    // ex: physics params, the position of the entity 

    // keep updating the position 
    position.x += velocity.x;
    position.y += velocity.y;
    
    // apply gravity 
    if (physical){
        // apply the acceleration 
        velocity.y += GRAVITY * deltaTime;

    }

    // set the position for the entity
    entity.setPosition(position);
}
