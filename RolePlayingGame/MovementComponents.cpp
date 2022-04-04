#include "MovementComponents.hpp"

MovementComponent::MovementComponent(sf::Sprite& sprite,
    float maxVelocity, float acceleration, float deceleration)
    : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{

}
MovementComponent::~MovementComponent()
{

}

const sf::Vector2f& MovementComponent::getVelocity() const
{
    return velocity;
}
void MovementComponent::move(const float dir_x, const float dir_y, const float& deltaTime)
{
    velocity.x += acceleration * dir_x;
    velocity.y += acceleration * dir_y;
}
void MovementComponent::update(const float& deltaTime)
{
    if(velocity.x > 0.f)
    {
        if(velocity.x > maxVelocity) velocity.x = maxVelocity;

        velocity.x -= deceleration;

        if(velocity.x < 0.f) velocity.x = 0.f;
    }
    else if(velocity.x < 0.f)
    {
        if(velocity.x < -maxVelocity) velocity.x = -maxVelocity;

        velocity.x += deceleration;

        if(velocity.x > 0.f) velocity.x = 0.f;
    }

    if(velocity.y > 0.f)
    {
        if(velocity.y > maxVelocity) velocity.y = maxVelocity;

        velocity.y -= deceleration;

        if(velocity.y < 0.f) velocity.y = 0.f;
    }
    else if(velocity.y < 0.f)
    {
        if(velocity.y < -maxVelocity) velocity.y = -maxVelocity;

        velocity.y += deceleration;

        if(velocity.y > 0.f) velocity.y = 0.f;
    }

    sprite.move(velocity * deltaTime);
}
