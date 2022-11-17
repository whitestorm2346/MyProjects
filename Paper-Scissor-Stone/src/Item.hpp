#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Image.hpp>

#define PAPER_PATH   "src/images/paper.png"
#define SCISSOR_PATH "src/images/scissor.png"
#define STONE_PATH   "src/images/stone.png"

enum Type{
    PAPER = 0,
    SCISSCOR,
    STONE
};

class Item{
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Image image;
    int type;

public:
    Item(int type);
    virtual ~Item();

    void collision();
};

#endif // ITEM_HPP_INCLUDED
