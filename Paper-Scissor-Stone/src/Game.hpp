#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Image.hpp>

#include "Item.hpp"

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Paper-Scissor-Stone"

#define ICON_PATH "src/images/icon.png"

#define ITEM_COUNT 1

class Game{
private:
    sf::RenderWindow* root;
    sf::Event event;
    sf::Clock dtClock;
    sf::Image icon;
    Item* items;
    float deltaTime;

public:
    Game();
    virtual ~Game();

    void run();
};

#endif // GAME_HPP_INCLUDED
