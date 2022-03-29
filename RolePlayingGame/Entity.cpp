#include "Entity.hpp"

Entity::Entity()
{
    shape.setSize(sf::Vector2f(50.f, 50.f));
    shape.setFillColor(sf::Color::White);

    movementSpeed = 100.f;
}
Entity::~Entity()
{

}

void Entity::move(const float& deltaTime, const float dir_x, const float dir_y)
{
    shape.move(dir_x * movementSpeed * deltaTime, dir_y * movementSpeed * deltaTime);
}
void Entity::update(const float& deltaTime)
{

}
void Entity::render(sf::RenderTarget* target)
{
    target->draw(shape);
}
