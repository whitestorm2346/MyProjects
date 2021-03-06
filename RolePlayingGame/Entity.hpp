#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include "MovementComponents.hpp"
#include "AnimationComponent.hpp"

class Entity
{
private:
    void initVariables();

protected:
    sf::Sprite sprite;
    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;

public:
    Entity();
    virtual ~Entity();

    void setTexture(sf::Texture& texture);
    void createMovementComponent(const float maxVelocity,
                                 const float acceleration,
                                 const float deceleration);
    void createAnimationComponent(sf::Texture& textureSheet);

    virtual void setPosition(const float x, const float y);
    virtual void move(const float dir_x, const float dir_y, const float& deltaTime);
    virtual void update(const float& deltaTime);
    virtual void render(sf::RenderTarget* target);
};

#endif // ENTITY_HPP_INCLUDED
