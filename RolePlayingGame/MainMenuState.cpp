#include "MainMenuState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
    : State(window, supportedKeys)
{
    gameState_btn = new Button(
        100, 100, 150, 50,
        &font, "New Game",
        sf::Color(70, 70, 70, 200),
        sf::Color(150, 150, 150, 255),
        sf::Color(20, 20, 20, 200)
    );

    initFonts();
    initKeybinds();

    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color::Magenta);
}
MainMenuState::~MainMenuState()
{
    delete gameState_btn;
}

void MainMenuState::initFonts()
{
    if(!font.loadFromFile("Font/consola.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
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

    gameState_btn->update(mousePosView);
}
void MainMenuState::render(sf::RenderTarget* target /** = nullptr */)
{
    if(!target) target = window;

    target->draw(background);

    gameState_btn->render(target);
}
