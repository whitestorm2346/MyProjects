#include "Button.hpp"

Button::Button(float x, float y, float width, float height,
           sf::Font* font, std::string text,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    buttonState = BTN_IDLE;

    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(20);
    this->text.setOrigin(
        this->text.getGlobalBounds().left + this->text.getGlobalBounds().width / 2.f,
        this->text.getGlobalBounds().top + this->text.getGlobalBounds().height / 2.f
    );
    this->text.setPosition(
        shape.getPosition().x + width / 2.f,
        shape.getPosition().y + height / 2.f
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    shape.setFillColor(idleColor);
}
Button::~Button()
{

}

const bool Button::isPressed() const
{
    return buttonState == BTN_ACTIVE;
}
void Button::update(const sf::Vector2f mousePos)
{
    buttonState = BTN_IDLE;

    if(shape.getGlobalBounds().contains(mousePos))
    {
        buttonState = BTN_HOVER;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) buttonState = BTN_ACTIVE;
    }

    switch(buttonState)
    {
        case BTN_IDLE:
            shape.setFillColor(idleColor);
            break;

        case BTN_HOVER:
            shape.setFillColor(hoverColor);
            break;

        case BTN_ACTIVE:
            shape.setFillColor(activeColor);
            break;

        default:
            shape.setFillColor(sf::Color::Red);
            break;
    }
}
void Button::render(sf::RenderTarget* target)
{
    target->draw(shape);
    target->draw(text);
}
