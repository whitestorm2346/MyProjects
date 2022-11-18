#include "Item.hpp"

Item::Item(){
    position.x = 0.f;
    position.y = 0.f;
    velocity.x = 0.f;
    velocity.y = 0.f;

    sprite.setTextureRect(sf::IntRect(0, 0, 512, 512));
    sprite.setScale(sf::Vector2f(0.15f, 0.15f));
    sprite.setPosition(sf::Vector2f(0, 0));
}

Item::~Item(){
}

void Item::setType(int type){
    this->type = type;

    switch(type){
        case PAPER:
            if(!texture.loadFromFile(PAPER_PATH)) std::cout<< "error\n";
            else std::cout<< "Load paper.png\n";
            break;

        case SCISSCOR:
            if(!texture.loadFromFile(SCISSOR_PATH)) std::cout<< "error\n";
            else std::cout<< "Load scissor.png\n";
            break;

        case STONE:
            if(!texture.loadFromFile(STONE_PATH)) std::cout<< "error\n";
            else std::cout<< "Load stone.png\n";
            break;
    }

    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(0, 0, 0));
}

void Item::print(sf::RenderWindow& window){
    window.draw(sprite);
}

bool Item::collision(Item item){
    return sprite.getGlobalBounds().intersects(item.getSprite().getGlobalBounds());
}

sf::Sprite& Item::getSprite(){
    return sprite;
}
