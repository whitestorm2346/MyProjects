#include "MainMenuState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow* window,
                             std::map<std::string, int>* supportedKeys,
                             std::stack<State*>* states)
    : State(window, supportedKeys, states)
{
    initFonts();
    initKeybinds();
    initButtons();

    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color::Cyan);
}
MainMenuState::~MainMenuState()
{
    for(std::map<std::string, Button*>::iterator iter = buttons.begin();
        iter != buttons.end(); ++iter)
    {
        delete iter->second;
    }
}

void MainMenuState::initFonts()
{
    if(!font.loadFromFile("Font/consola.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}
void MainMenuState::initButtons()
{
    buttons["GAME_STATE"] = new Button(
        100, 100, 150, 50,
        &font, "New Game",
        sf::Color(70, 70, 70, 200),
        sf::Color(150, 150, 150, 255),
        sf::Color(20, 20, 20, 200)
    );

    buttons["EXIT_STATE"] = new Button(
        100, 300, 150, 50,
        &font, "Quit",
        sf::Color(100, 100, 100, 200),
        sf::Color(150, 150, 150, 255),
        sf::Color(20, 20, 20, 200)
    );
}
void MainMenuState::initKeybinds()
{
    std::ifstream ifs("Config/mainMenuStateKeybinds.ini");

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
void MainMenuState::updateButtons()
{
    for(std::map<std::string, Button*>::iterator iter = buttons.begin();
        iter != buttons.end(); ++iter)
    {
        iter->second->update(mousePosView);
    }

    if(buttons["GAME_STATE"]->isPressed()) states->push(new GameState(window, supportedKeys, states));

    if(buttons["EXIT_STATE"]->isPressed()) quit = true;
}
void MainMenuState::update(const float& deltaTime)
{
    updateMousePositions();
    updateInput(deltaTime);
    updateButtons();
}
void MainMenuState::renderButtons(sf::RenderTarget* target /** = nullptr */)
{
    for(std::map<std::string, Button*>::iterator iter = buttons.begin();
        iter != buttons.end(); ++iter)
    {
        iter->second->render(target);
    }
}
void MainMenuState::render(sf::RenderTarget* target /** = nullptr */)
{
    if(!target) target = window;

    target->draw(background);

    renderButtons(target);
}
