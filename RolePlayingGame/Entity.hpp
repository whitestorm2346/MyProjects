#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include "MovementComponents.hpp"

class Entity
{
private:
    void initVariables();

protected:
    sf::Texture* texture;
    sf::Sprite* sprite;
    MovementComponent* movementComponent;

public:
    Entity();
    virtual ~Entity();

    void createSprite(sf::Texture* texture);
    void createMovementComponent(const float maxVelocity);

    virtual void setPosition(const float x, const float y);
    virtual void move(const float& deltaTime, const float dir_x, const float dir_y);
    virtual void update(const float& deltaTime);
    virtual void render(sf::RenderTarget* target);
};

#endif // ENTITY_HPP_INCLUDED
