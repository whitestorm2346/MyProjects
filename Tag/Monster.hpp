#ifndef MONSTER_HPP_INCLUDED
#define MONSTER_HPP_INCLUDED

#include "Charactor.hpp"

class Monster: public Character
{
public:
    Monster();
    virtual ~Monster();

    void move();
};

#endif // MONSTER_HPP_INCLUDED
