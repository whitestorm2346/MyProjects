#ifndef MOVEMENTCOMPONENTS_HPP_INCLUDED
#define MOVEMENTCOMPONENTS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <fstream>
#include <sstream>

class MovementComponent
{
private:
    sf::Sprite& sprite;
    float maxVelocity;
    float acceleration;
    float deceleration;
    sf::Vector2f velocity;

public:
    MovementComponent(sf::Sprite& sprite,
                      float maxVelocity,
                      float acceleration,
                      float deceleration);
    virtual ~MovementComponent();

    const sf::Vector2f& getVelocity() const;

    void move(const float dir_x, const float dir_y, const float& deltaTime);
    void update(const float& deltaTime);
};

#endif // MOVEMENTCOMPONENTS_HPP_INCLUDED
