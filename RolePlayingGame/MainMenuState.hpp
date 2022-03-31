#ifndef MAINMENUSTATE_HPP_INCLUDED
#define MAINMENUSTATE_HPP_INCLUDED

#include "GameState.hpp"
#include "Button.hpp"

class MainMenuState: public State
{
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, Button*> buttons;

    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window,
                  std::map<std::string, int>* supportedKeys,
                  std::stack<State*>* states);
    virtual ~MainMenuState();

    void endState();
    void updateInput(const float& deltaTime);
    void updateButtons();
    void update(const float& deltaTime);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // MAINMENUSTATE_HPP_INCLUDED
