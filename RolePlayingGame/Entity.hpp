#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

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

class Entity
{
protected:
    sf::RectangleShape shape;
    float movementSpeed;

public:
    Entity();
    virtual ~Entity();

    virtual void move(const float& deltaTime, const float dir_x, const float dir_y);

    virtual void update(const float& deltaTime);
    virtual void render(sf::RenderTarget* target);
};

#endif // ENTITY_HPP_INCLUDED
