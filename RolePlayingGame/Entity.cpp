#include "Entity.hpp"

Entity::Entity()
{
    initVariables();
}
Entity::~Entity()
{
    delete movementComponent;
}

void Entity::initVariables()
{
    movementComponent = nullptr;
}
void Entity::setTexture(sf::Texture& texture)
{
    sprite.setTexture(texture);
}
void Entity::createMovementComponent(const float maxVelocity,
                                     const float acceleration,
                                     const float deceleration)
{
    movementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}
void Entity::setPosition(const float x, const float y)
{
    sprite.setPosition(x, y);
}
void Entity::move(const float dir_x, const float dir_y, const float& deltaTime)
{
    if(movementComponent)
    {
        movementComponent->move(dir_x, dir_y, deltaTime);
    }
}
void Entity::update(const float& deltaTime)
{
    if(movementComponent) movementComponent->update(deltaTime);
}
void Entity::render(sf::RenderTarget* target)
{
    target->draw(sprite);
}
