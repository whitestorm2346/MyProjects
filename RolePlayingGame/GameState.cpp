#include "GameState.hpp"

GameState::GameState(sf::RenderWindow* window,
                     std::map<std::string, int>* supportedKeys,
                     std::stack<State*>* states)
    : State(window, supportedKeys, states)
{
    initKeybinds();
    initTextures();
    initPlayers();
}
GameState::~GameState()
{
    delete player;
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
void GameState::initTextures()
{
    if(!textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Sprites/Player/idle.png"))
    {
        throw("ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE");
    }
}
void GameState::initPlayers()
{
    player = new Player(0, 0, textures["PLAYER_IDLE"]);
}
void GameState::updateInput(const float& deltaTime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
        player->move(0.f, -1.f, deltaTime);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
        player->move(-1.f, 0.f, deltaTime);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
        player->move(0.f, 1.f, deltaTime);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
        player->move(1.f, 0.f, deltaTime);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
        endState();
}
void GameState::update(const float& deltaTime)
{
    updateMousePositions();
    updateInput(deltaTime);

    player->update(deltaTime);
}
void GameState::render(sf::RenderTarget* target /** = nullptr */)
{
    if(!target) target = window;

    player->render(target);
}
