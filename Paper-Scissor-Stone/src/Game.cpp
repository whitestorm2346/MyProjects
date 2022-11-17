#include "Game.hpp"

void Game::init(){
    // init window
    root = new sf::RenderWindow(
               sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
               WINDOW_TITLE,
               sf::Style::Close
           );

    // init fields
    event = new sf::Event();
    dtClock = new sf::Clock();
    icon = new sf::Image();
    deltaTime = 0.f;

    icon->loadFromFile(ICON_PATH);

}

Game::Game(){
    init();
}

Game::~Game(){
    delete root;
    delete dtClock;
    delete icon;
}

void Game::run(){
    while(root->isOpen()){
        while(root->pollEvent(*event)){
            if(event->type == sf::Event::Closed) root->close();
        }

        root->clear();
        // root->draw();
        root->display();
    }
}
