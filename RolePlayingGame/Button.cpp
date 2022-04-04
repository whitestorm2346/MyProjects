#include "Button.hpp"

Button::Button(float x, float y, float width, float height,
           sf::Font* font, std::string text, unsigned character_size,
           sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    buttonState = BTN_IDLE;

    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(idleColor);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(textIdleColor);
    this->text.setCharacterSize(character_size);
    this->text.setOrigin(
        this->text.getGlobalBounds().left + this->text.getGlobalBounds().width / 2.f,
        this->text.getGlobalBounds().top + this->text.getGlobalBounds().height / 2.f
    );
    this->text.setPosition(
        shape.getPosition().x + width / 2.f,
        shape.getPosition().y + height / 2.f
    );

    this->textIdleColor = textIdleColor;
    this->textHoverColor = textHoverColor;
    this->textActiveColor = textActiveColor;

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;
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
            text.setFillColor(textIdleColor);
            break;

        case BTN_HOVER:
            shape.setFillColor(hoverColor);
            text.setFillColor(textHoverColor);
            break;

        case BTN_ACTIVE:
            shape.setFillColor(activeColor);
            text.setFillColor(textActiveColor);
            break;

        default:
            shape.setFillColor(sf::Color::Red);
            text.setFillColor(sf::Color::White);
            break;
    }
}
void Button::render(sf::RenderTarget* target)
{
    target->draw(shape);
    target->draw(text);
}
