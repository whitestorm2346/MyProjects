#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Paper-Scissor-Stone"

#define ICON_PATH "src/images/icon.png"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Image.hpp>

class Game{
private:
    sf::RenderWindow* root;
    sf::Event* event;
    sf::Clock* dtClock;
    sf::Image* icon;
    float deltaTime;

    void init();

public:
    Game();
    virtual ~Game();

    void run();
};

#endif // GAME_HPP_INCLUDED
