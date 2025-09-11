#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "input/input.hpp"


class Player : public Entity{

    private: 
        // we will implement the player movement physics here, will take the inputHandler as input
        // and will use here to get all the active keystrokes and keyBindings

        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();

        // speed params 
        sf::Vector2f speed{10.0f, 10.0f};

        
        public: 

        // constructor with all initial params 
        Player(sf::Vector2f pos, sf::Vector2f vel, InputHandler* inputHandler);

        // here we don't need to implement the draw function again, as we did it in the 
        // base entity class, which will be inherited here

        // write some getter and setter function here for the player 
        void setPosition(sf::Vector2f pos);
        sf::Vector2f getPosition();
    
};