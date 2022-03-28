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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) move(deltaTime, 0.f, -1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) move(deltaTime, -1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) move(deltaTime,  0.f, 1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) move(deltaTime,  1.f, 0.f);
}
void Entity::render(sf::RenderTarget* target)
{
    target->draw(shape);
}
