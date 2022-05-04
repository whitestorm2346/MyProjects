#include "Charactor.hpp"

Character::Character()
{
    name = "O";
    position = {0, 0};
    speed = 0.5;
    timer = new Timer(speed);
}
Character::~Character()
{
    delete timer;
}

bool Character::checkCollide()
{
    return true;
}
