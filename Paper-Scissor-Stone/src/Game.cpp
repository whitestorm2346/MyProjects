#include "Game.hpp"

Game::Game(){
    // init window
    root = new sf::RenderWindow(
               sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
               WINDOW_TITLE,
               sf::Style::Close
           );

    // init fields
    deltaTime = 0.f;
    icon.loadFromFile(ICON_PATH);

    // init items
    items = new Item[ITEM_COUNT];
}

Game::~Game(){
    delete root;
    delete [] items;
}

void Game::run(){
    while(root->isOpen()){
        while(root->pollEvent(event)){
            if(event.type == sf::Event::Closed) root->close();
        }

        root->clear();
        // root->draw();
        root->display();
    }
}
