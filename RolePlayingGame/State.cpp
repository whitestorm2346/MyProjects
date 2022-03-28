#include "State.hpp"

State::State(sf::RenderWindow* window)
{
    this->window = window;
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) quit = true;
}
