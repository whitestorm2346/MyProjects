#include "GameState.hpp"

GameState::GameState(sf::RenderWindow* window,
                     std::map<std::string, int>* supportedKeys,
                     std::stack<State*>* states)
    : State(window, supportedKeys, states)
{
    initKeybinds();
}
GameState::~GameState()
{

}

void GameState::initKeybinds()
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
    updateMousePositions();
    updateInput(deltaTime);

    player.update(deltaTime);
}
void GameState::render(sf::RenderTarget* target /** = nullptr */)
{
    if(!target) target = window;

    player.render(target);
}
