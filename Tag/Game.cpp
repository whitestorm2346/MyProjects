#include "Game.hpp"

Game::Game()
{
    srand(time(nullptr));

    size = {30, 30};
    gameOver = false;
    field = new Field(size.first, size.second);
    control = new UserInterface();
    characters = new List<Character*>();
}
Game::~Game()
{
    delete field;
    delete control;
    delete characters;
}

void Game::run()
{
    while(!gameOver)
    {

    }
}
