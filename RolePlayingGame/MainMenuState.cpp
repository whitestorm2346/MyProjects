#include "MainMenuState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
    : State(window, supportedKeys)
{
    initFonts();
    initKeybinds();

    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color::Magenta);
}
MainMenuState::~MainMenuState()
{

}

void MainMenuState::initFonts()
{
    if(font.loadFromFile("Font/consola.ttf"))
}
void MainMenuState::initKeybinds()
{
    std::ifstream ifs("Config/gameStateKeybinds.ini");

    if(ifs.is_open())
    {
        std::string key, value;

        for(; ifs>> key >> value;)
        {
            keybinds[key] = supportedKeys->at(value);
        }
    }

    ifs.close();
}
void MainMenuState::endState()
{
    std::cout<< "Ending MainMenuState!\n";
}
void MainMenuState::updateInput(const float& deltaTime)
{
    checkForQuit();
}
void MainMenuState::update(const float& deltaTime)
{
    updateMousePositions();
    updateInput(deltaTime);
}
void MainMenuState::render(sf::RenderTarget* target /** = nullptr */)
{
    if(!target) target = window;

    target->draw(background);
}
