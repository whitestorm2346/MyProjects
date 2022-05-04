#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "Charactor.hpp"

class Player: public Character
{
public:
    Player();
    virtual ~Player();

    void move();
};

#endif // PLAYER_HPP_INCLUDED
