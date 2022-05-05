#include "Field.hpp"

Field::Field(int width, int height)
{
    size = {width, height};
    obstacles = new List<Obstacle*>();
}
Field::~Field()
{
    delete obstacles;
}
