#ifndef DISTANCE_HPP_INCLUDED
#define DISTANCE_HPP_INCLUDED

#include <utility>

#include "Field.hpp"

class Distance
{
private:
    std::pair<int, int> position;
    Field* field;
    int** distance;

public:
    Distance();
    virtual ~Distance();

    void setField();
    void countDistance();
};

#endif // DISTANCE_HPP_INCLUDED
