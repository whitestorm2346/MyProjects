#include "Obstacle.hpp"

Obstacle::Obstacle(int x, int y, int width, int height)
{
    size = {width, height};
    position = {x, y};
}
Obstacle::~Obstacle()
{

}
