#include "gameObject.hpp"


gameObject::gameObject() : active(true) {
    shape.setSize({50, 50});
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
}

gameObject::~gameObject() {}

void gameObject::setActive(bool isActive) { active = isActive; }

bool gameObject::isActive() const { return active; }

sf::Vector2f gameObject::getPosition(){
    return shape.getPosition();
}
 
void gameObject::setPosition(sf::Vector2f newPosition){
    shape.setPosition(newPosition);
}
