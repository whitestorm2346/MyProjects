#ifndef FIELD_HPP_INCLUDED
#define FIELD_HPP_INCLUDED

#include <utility>

#include "List.hpp"
#include "Obstacle.hpp"

class Field
{
private:
    std::pair<int, int> size;
    List<Obstacle*>* obstacles;

public:
    Field(int width, int height);
    ~Field();
};

#endif // FIELD_HPP_INCLUDED
