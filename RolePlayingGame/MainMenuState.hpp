#ifndef MAINMENUSTATE_HPP_INCLUDED
#define MAINMENUSTATE_HPP_INCLUDED

#include "GameState.hpp"
#include "Button.hpp"

class MainMenuState: public State
{
    sf::RectangleShape background;
    sf::Font font;

    void initFonts();
    void initKeybinds();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
    virtual ~MainMenuState();

    void endState();
    void updateInput(const float& deltaTime);
    void update(const float& deltaTime);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // MAINMENUSTATE_HPP_INCLUDED
