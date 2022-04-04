#include "Player.hpp"

Player::Player(float x, float y, sf::Texture& textureSheet)
{
    initVariables();

    setPosition(x, y);

    createMovementComponent(300.f, 15.f, 5.f);
    createAnimationComponent(textureSheet);

    animationComponent->addAnimation("IDLE_RIGHT", 10.f, 0, 0, 11, 0, 520, 420);
}
Player::~Player()
{

}

void Player::initVariables()
{

}
void Player::initComponents()
{

}
void Player::update(const float& deltaTime)
{
    movementComponent->update(deltaTime);
    animationComponent->play("IDLE_RIGHT", deltaTime);
}
