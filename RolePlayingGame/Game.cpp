#include "Game.hpp"

Game::Game()
{
    initWindow();
    initState();
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

void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");
    std::string title = "title";
    sf::VideoMode window_bounds(800, 600);
    unsigned int framerate_limit = 120;
    bool vertical_sync_enabled = false;

    if(ifs.is_open())
    {
        std::getline(ifs, title);

        ifs>> window_bounds.width >> window_bounds.height;
        ifs>> framerate_limit;
        ifs>> vertical_sync_enabled;
    }

    ifs.close();

    window = new sf::RenderWindow(window_bounds, title);

    window->setFramerateLimit(framerate_limit);
    window->setVerticalSyncEnabled(vertical_sync_enabled);
}
void Game::initState()
{
    states.push(new GameState(window));
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

    if(!states.empty()) states.top()->update(deltaTime);
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
