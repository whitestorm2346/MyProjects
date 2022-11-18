#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#define PAPER_PATH   "src/images/paper.png"
#define SCISSOR_PATH "src/images/scissor.png"
#define STONE_PATH   "src/images/stone.png"

#define ITEM_WIDTH  50
#define ITEM_HEIGHT 50

enum Type{
    PAPER = 0,
    SCISSCOR,
    STONE
};

class Item{
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Texture texture;
    sf::Sprite sprite;
    int type;

public:
    Item();
    virtual ~Item();

    void setType(int type);
    void setPosition();
    void print(sf::RenderWindow& window);
    void move();
    bool collision(Item item);
    sf::Sprite& getSprite();
};

#endif // ITEM_HPP_INCLUDED
