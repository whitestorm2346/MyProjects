#include "MainMenuState.hpp"

MainMenuState::MainMenuState(sf::RenderWindow* window,
                             std::map<std::string, int>* supportedKeys,
                             std::stack<State*>* states)
    : State(window, supportedKeys, states)
{
    initVariables();
    initBackground();
    initFonts();
    initKeybinds();
    initButtons();
}
MainMenuState::~MainMenuState()
{
    for(std::map<std::string, Button*>::iterator iter = buttons.begin();
        iter != buttons.end(); ++iter)
    {
        delete iter->second;
    }
}

void MainMenuState::initVariables()
{

}
void MainMenuState::initBackground()
{
    background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x),
                                    static_cast<float>(window->getSize().y)));

    if(!backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
    {
        throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_BACKGROUND");
    }

    background.setTexture(&backgroundTexture);
}
void MainMenuState::initFonts()
{
    if(!font.loadFromFile("Font/consola.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
    }
}
void MainMenuState::initButtons()
{
    buttons["GAME_STATE"] = new Button(
        1275, 750, 150, 50,
        &font, "New Game",
        sf::Color(100, 100, 100, 200),
        sf::Color(150, 150, 150, 255),
        sf::Color(20, 20, 20, 200)
    );

    buttons["SETTINGS"] = new Button(
        1100, 750, 150, 50,
        &font, "Settings",
        sf::Color(100, 100, 100, 200),
        sf::Color(150, 150, 150, 255),
        sf::Color(20, 20, 20, 200)
    );

    buttons["EXIT_STATE"] = new Button(
        925, 750, 150, 50,
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
void MainMenuState::updateInput(const float& deltaTime)
{

}
void MainMenuState::updateButtons()
{
    for(std::map<std::string, Button*>::iterator iter = buttons.begin();
        iter != buttons.end(); ++iter)
    {
        iter->second->update(mousePosView);
    }

    if(buttons["GAME_STATE"]->isPressed()) states->push(new GameState(window, supportedKeys, states));

    if(buttons["SETTINGS"]->isPressed());

    if(buttons["EXIT_STATE"]->isPressed()) endState();
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
        iter != buttons.end(); ++iter){
        iter->second->render(target);
    }
}
void MainMenuState::render(sf::RenderTarget* target /** = nullptr */)
{
    if(!target) target = window;

    target->draw(background);
    renderButtons(target);

    /**
    sf::Text mouseText;
    mouseText.setPosition(mousePosView.x, mousePosView.y - 30);
    mouseText.setFont(font);
    mouseText.setColor(sf::Color::Black);
    mouseText.setCharacterSize(20);
    std::stringstream ss;
    ss<< mousePosView.x << ' ' << mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);
    */
}
