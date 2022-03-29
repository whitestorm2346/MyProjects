#include "GameState.hpp"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
    : State(window, supportedKeys)
{
    initKeybinds();
}
GameState::~GameState()
{

}

void GameState::initKeybinds()
{
    keybinds["CLOSE"] = supportedKeys->at("Escape");
    keybinds["MOVE_LEFT"] = supportedKeys->at("A");
    keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
    keybinds["MOVE_UP"] = supportedKeys->at("W");
    keybinds["MOVE_DOWN"] = supportedKeys->at("S");
}
void GameState::endState()
{
    std::cout<< "Ending GameState!\n";
}
void GameState::updateInput(const float& deltaTime)
{
    checkForQuit();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
        player.move(deltaTime, 0.f, -1.f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
        player.move(deltaTime, -1.f, 0.f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
        player.move(deltaTime,  0.f, 1.f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
        player.move(deltaTime,  1.f, 0.f);
}
void GameState::update(const float& deltaTime)
{
    updateInput(deltaTime);

    player.update(deltaTime);
}
void GameState::render(sf::RenderTarget* target /** = nullptr */)
{
    if(!target) target = window;

    player.render(target);
}
