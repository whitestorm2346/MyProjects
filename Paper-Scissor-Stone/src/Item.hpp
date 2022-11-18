#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#define PAPER_PATH   "src/images/paper.png"
#define SCISSOR_PATH "src/images/scissor.png"
#define STONE_PATH   "src/images/stone.png"

#define ITEM_WIDTH  20
#define ITEM_HEIGHT 20

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
    bool collision(Item item);
    sf::Sprite& getSprite();
};

#endif // ITEM_HPP_INCLUDED
