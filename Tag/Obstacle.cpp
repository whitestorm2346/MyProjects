#include "Obstacle.hpp"

Obstacle::Obstacle(int x, int y, int width, int height)
{
    size = {width, height};
    position = {x, y};
}
Obstacle::~Obstacle()
{

}

void Obstacle::setSize(int width, int height)
{
    size = {width, height};
}
void Obstacle::setPosition(int x, int y)
{
    position = {x, y};
}
