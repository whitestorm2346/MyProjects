#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "Entity.hpp"

class Player: public Entity
{
private:
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture* texture);
    virtual ~Player();
};

#endif // PLAYER_HPP_INCLUDED
