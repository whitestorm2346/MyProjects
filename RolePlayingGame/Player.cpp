#include "Player.hpp"

Player::Player(float x, float y, sf::Texture& texture)
{
    initVariables();
    initComponents();
    setTexture(texture);
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
    createMovementComponent(250.f, 10.f, 4.f);
}
