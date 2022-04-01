#include "Entity.hpp"

Entity::Entity()
{
    initVariables();
}
Entity::~Entity()
{
    delete sprite;
    delete movementComponent;
}

void Entity::initVariables()
{
    texture = nullptr;
    sprite = nullptr;
    movementComponent = nullptr;
}
void Entity::createSprite(sf::Texture* texture)
{
    this->texture = texture;
    sprite = new sf::Sprite(*texture);
}
void Entity::createMovementComponent(const float maxVelocity)
{
    movementComponent = new MovementComponent(maxVelocity);
}
void Entity::setPosition(const float x, const float y)
{
    if(sprite) sprite->setPosition(x, y);
}
void Entity::move(const float& deltaTime, const float dir_x, const float dir_y)
{
    if(sprite && movementComponent)
    {
        movementComponent->move(dir_x, dir_y);
        sprite->move(movementComponent->getVelocity() * deltaTime);
    }
}
void Entity::update(const float& deltaTime)
{

}
void Entity::render(sf::RenderTarget* target)
{
    if(sprite) target->draw(*sprite);
}
