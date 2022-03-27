#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "State.hpp"

class GameState: public State
{
public:
    GameState(sf::RenderWindow* window);
    virtual ~GameState();

    void endState();
    void update(const float& deltaTime);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // GAMESTATE_HPP_INCLUDED
