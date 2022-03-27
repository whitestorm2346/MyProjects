#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "State/GameState.hpp"

class Game
{
    sf::RenderWindow* window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float deltaTime;

    std::stack<State*> states;

    void initWindow();
    void initState();

public:
    Game();
    virtual ~Game();

    void updateDeltaTime();
    void updateSFMLEvents();
    void update();
    void render();
    void run();
};

#endif // GAME_HPP_INCLUDED