#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "State.hpp"

class GameState: public State
{
private:
    Entity player;

    void initKeybinds();

public:
    GameState(sf::RenderWindow* window,
              std::map<std::string, int>* supportedKeys,
              std::stack<State*>* states);
    virtual ~GameState();

    void endState();
    void updateInput(const float& deltaTime);
    void update(const float& deltaTime);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // GAMESTATE_HPP_INCLUDED
