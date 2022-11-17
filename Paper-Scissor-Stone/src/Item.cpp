#include "Item.hpp"

Item::Item(int type){
    this->type = type;
    position.x = 0.f;
    position.y = 0.f;
    velocity.x = 0.f;
    velocity.y = 0.f;

    switch(type){
        case PAPER:
            image.loadFromFile(PAPER_PATH);
            break;

        case SCISSCOR:
            image.loadFromFile(SCISSOR_PATH);
            break;

        case STONE:
            image.loadFromFile(STONE_PATH);
            break;
    }
}

Item::~Item(){
}

void Item::collision(){
}
