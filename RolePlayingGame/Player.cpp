#include "Player.hpp"

Player::Player(float x, float y, sf::Texture* texture)
{
    initVariables();
    initComponents();
    createSprite(texture);
    setPosition(x, y);
}
Player::~Player()
{

}

void Player::initVariables()
{

}
void Player::initComponents()
{
    createMovementComponent(100.f);
}
