#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>

enum button_state{
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

class Button
{
private:
    unsigned short buttonState;

    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

public:
    Button(float x, float y, float width, float height,
           sf::Font* font, std::string text, unsigned character_size,
           sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    ~Button();

    const bool isPressed() const;
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
};

#endif // BUTTON_HPP_INCLUDED
