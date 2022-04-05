#include "Player.hpp"

Player::Player(float x, float y, sf::Texture& textureSheet)
{
    initVariables();

    setPosition(x, y);

    createMovementComponent(300.f, 15.f, 5.f);
    createAnimationComponent(textureSheet);

    animationComponent->addAnimation("ATTACKING", 10.f, 0, 0, 11, 0, 520, 420);
    animationComponent->addAnimation("CASTING_SPELLS", 10.f, 0, 1, 17, 1, 520, 420);
    animationComponent->addAnimation("DYING", 10.f, 0, 2, 14, 2, 520, 420);
    animationComponent->addAnimation("HURT", 10.f, 0, 3, 11, 3, 520, 420);
    animationComponent->addAnimation("IDLE", 10.f, 0, 4, 11, 4, 520, 420);
    animationComponent->addAnimation("IDLE_BLINK", 10.f, 0, 5, 11, 5, 520, 420);
    animationComponent->addAnimation("TAUNT", 10.f, 0, 6, 17, 6, 520, 420);
    animationComponent->addAnimation("WALKING", 10.f, 0, 7, 11, 7, 520, 420);
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

    if(movementComponent->idle()) animationComponent->play("IDLE", deltaTime);
    else animationComponent->play("WALKING", deltaTime);
}
