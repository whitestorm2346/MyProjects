#include "Item.hpp"

Item::Item(){
    velocity.x = static_cast<float>(rand() % 3 - 1);
    velocity.y = static_cast<float>(rand() % 3 - 1);

    sprite.setTextureRect(sf::IntRect(0, 0, 512, 512));
    sprite.setScale(sf::Vector2f(ITEM_WIDTH / 512.f, ITEM_HEIGHT / 512.f));
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

void Item::setPosition(float x, float y){
    sprite.setPosition(sf::Vector2f(x, y));
}

void Item::print(sf::RenderWindow& window){
    window.draw(sprite);
}

void Item::move(){
    sf::Vector2f currPos = sprite.getPosition();

    sprite.move(currPos.x + velocity.x, currPos.y + velocity.y);
}

bool Item::collision(Item item){
    return sprite.getGlobalBounds().intersects(item.getSprite().getGlobalBounds());
}

sf::Sprite& Item::getSprite(){
    return sprite;
}
