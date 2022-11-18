#include "Item.hpp"

Item::Item(){
    position.x = 0.f;
    position.y = 0.f;
    velocity.x = 0.f;
    velocity.y = 0.f;

    sprite.setScale(sf::Vector2f(ITEM_WIDTH, ITEM_HEIGHT));
}

Item::~Item(){
}

void Item::setType(int type){
    this->type = type;

    switch(type){
        case PAPER:
            texture.loadFromFile(PAPER_PATH);
            break;

        case SCISSCOR:
            texture.loadFromFile(SCISSOR_PATH);
            break;

        case STONE:
            texture.loadFromFile(STONE_PATH);
            break;
    }

    sprite.setTexture(texture);
}

bool Item::collision(Item item){
    return sprite.getGlobalBounds().intersects(item.getSprite().getGlobalBounds());
}

sf::Sprite& Item::getSprite(){
    return sprite;
}
