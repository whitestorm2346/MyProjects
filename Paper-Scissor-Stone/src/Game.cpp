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
    background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    background.setFillColor(sf::Color(255, 255, 255));
    //icon.loadFromFile(ICON_PATH);

    // init items
    items = new Item[ITEM_COUNT];

    for(int i = 0; i < ITEM_COUNT; i++){
        items[i].setType(i % 3);
    }
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

        root->draw(background);

        for(int i = 0; i < ITEM_COUNT; i++){
            items[i].print(*root);
        }

        root->display();
    }
}
