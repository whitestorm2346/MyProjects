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
    float maxVelocity;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f deceleration;

public:
    MovementComponent(float maxVelocity);
    virtual ~MovementComponent();

    const sf::Vector2f& getVelocity() const;

    void move(const float dir_x, const float dir_y);
    void update(const float& deltaTime);
};

#endif // MOVEMENTCOMPONENTS_HPP_INCLUDED
