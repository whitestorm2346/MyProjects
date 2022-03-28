#include "GameState.hpp"

GameState::GameState(sf::RenderWindow* window): State(window)
{

}
GameState::~GameState()
{

}

void GameState::endState()
{
    std::cout<< "Ending GameState!\n";
}
void GameState::updateKeybinds(const float& deltaTime)
{
    checkForQuit();
}
void GameState::update(const float& deltaTime)
{
    updateKeybinds(deltaTime);

    player.update(deltaTime);
}
void GameState::render(sf::RenderTarget* target /** = nullptr */)
{
    player.render(target);
}
