#ifndef FIELD_HPP_INCLUDED
#define FIELD_HPP_INCLUDED

#include <utility>
#include <cstdlib>

#include "List.hpp"
#include "Obstacle.hpp"

class Field
{
private:
    std::pair<int, int> size;
    List<Obstacle*>* obstacles;

public:
    char** matrix;

    Field(int width, int height);
    virtual ~Field();

    void setSize(int width, int height);
    void addObstacle();
    void popObstacle();
    void generate();
};

#endif // FIELD_HPP_INCLUDED
