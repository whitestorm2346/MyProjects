#ifndef CHARACTOR_HPP_INCLUDED
#define CHARACTOR_HPP_INCLUDED

#include <utility>
#include <string>

#include "Timer.hpp"

#define x first
#define y second

class Character
{
private:
    std::string name;
    std::pair<int, int> position;
    double speed; // unit: seconds per step
    Timer* timer;

public:
    Character();
    virtual ~Character();

    virtual void move() = 0;
    virtual bool checkCollide();
};

#endif // CHARACTOR_HPP_INCLUDED
