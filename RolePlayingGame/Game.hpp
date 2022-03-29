#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "GameState.hpp"

class Game
{
    sf::RenderWindow* window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float deltaTime;

    std::stack<State*> states;
    std::map<std::string, int> supportedKeys;

    void initWindow();
    void initStates();
    void initKeys();

public:
    Game();
    virtual ~Game();

    void endApplication();

    void updateDeltaTime();
    void updateSFMLEvents();
    void update();

    void render();
    void run();
};

#endif // GAME_HPP_INCLUDED
