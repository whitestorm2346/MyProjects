#include "State.hpp"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
{
    this->window = window;
    this->supportedKeys = supportedKeys;
    quit = false;
}
State::~State()
{

}

const bool& State::getQuit() const
{
    return quit;
}
void State::checkForQuit()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE")))) quit = true;
}
void State::updateMousePositions()
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
}
