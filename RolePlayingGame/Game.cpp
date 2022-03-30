#include "Game.hpp"

Game::Game()
{
    initWindow();
    initKeys();
    initStates();
}
Game::~Game()
{
    delete window;

    while(!states.empty())
    {
        delete states.top();

        states.pop();
    }
}

void Game::initVariables()
{
    window = nullptr;
    deltaTime = 0.f;
    fullscreen = false;
}
void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");
    videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "title";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    unsigned int framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    fullscreen = false;

    if(ifs.is_open())
    {
        std::getline(ifs, title);

        ifs>> window_bounds.width >> window_bounds.height;
        ifs>> fullscreen;
        ifs>> framerate_limit;
        ifs>> vertical_sync_enabled;
        ifs>> antialiasing_level;
    }

    ifs.close();

    windowSettings.antialiasingLevel = antialiasing_level;

    if(fullscreen)
        window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    else
        window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

    window->setFramerateLimit(framerate_limit);
    window->setVerticalSyncEnabled(vertical_sync_enabled);
}
void Game::initStates()
{
    states.push(new MainMenuState(window, &supportedKeys, &states));
}
void Game::initKeys()
{
    std::ifstream ifs("Config/supportedKeys.ini");

    if(ifs.is_open())
    {
        std::string key;
        int value;

        for(; ifs>> key >> value;)
        {
            supportedKeys[key] = value;
        }
    }

    ifs.close();
}
void Game::endApplication()
{
    std::cout<< "Ending Application!\n";
}
void Game::updateDeltaTime()
{
    deltaTime = dtClock.restart().asSeconds();
}
void Game::updateSFMLEvents()
{
    while(window->pollEvent(sfEvent))
    {
        if(sfEvent.type == sf::Event::Closed) window->close();
    }
}
void Game::update()
{
    updateSFMLEvents();

    if(!states.empty())
    {
        states.top()->update(deltaTime);

        if(states.top()->getQuit())
        {
            states.top()->endState();

            delete states.top();

            states.pop();
        }
    }
    else
    {
        endApplication();
        window->close();
    }
}
void Game::render()
{
    window->clear();

    if(!states.empty()) states.top()->render(window);

    window->display();
}
void Game::run()
{
    while(window->isOpen())
    {
        updateDeltaTime();
        update();
        render();
    }
}
