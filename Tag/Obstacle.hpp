#ifndef OBSTACLE_HPP_INCLUDED
#define OBSTACLE_HPP_INCLUDED

#include <utility>

class Obstacle
{
private:
    std::pair<int, int> size;
    std::pair<int, int> position;

public:
    Obstacle(int x, int y, int width, int height);
    virtual ~Obstacle();
};

#endif // OBSTACLE_HPP_INCLUDED
