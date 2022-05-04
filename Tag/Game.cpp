#include "Game.hpp"

Game::Game()
{
    size = {30, 30};
    gameOver = false;
    control = new UserInterface();
}
Game::~Game()
{
    delete control;
}

void Game::run()
{
    while(!gameOver)
    {

    }
}
