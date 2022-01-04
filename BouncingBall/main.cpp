#include <SFML/Graphics.hpp>
#include "ball.hpp"

#define getMousePosInWindow mousePosInWindow(window_Main.getPosition(), sf::Mouse::getPosition())
#define getMousePosDisplacement mousePosDisplacement(mouseLastPos, mouseCurrPos)

int main()
{
    sf::RenderWindow window_Main(sf::VideoMode(winWidth, winHeight), "Bouncing Ball", sf::Style::Close);
    sf::Vector2i mouseLastPos = getMousePosInWindow;
    sf::Vector2i mouseCurrPos = getMousePosInWindow;
    sf::Vector2i dropping;

    window_Main.setFramerateLimit(90);
    Ball bouncingBall;

    while(window_Main.isOpen())
    {
        sf::Event event;

        while(window_Main.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window_Main.close();

                    break;

                case sf::Event::MouseButtonPressed:
                    switch(event.key.code)
                    {
                        case sf::Mouse::Right:
                            bouncingBall.setRandomColor();

                            break;

                        case sf::Mouse::Left:
                            if(isInCircle(bouncingBall.ball.getPosition(), getMousePosInWindow))
                               bouncingBall.isDrag = true;

                            break;

                        default: break;
                    }

                    break;

                case sf::Event::MouseButtonReleased:
                    switch(event.key.code)
                    {
                        case sf::Mouse::Right: break;

                        case sf::Mouse::Left:
                            bouncingBall.isDrag = false;
                            bouncingBall.velocity = 0;

                            break;

                        default: break;
                    }

                    break;

                case sf::Event::MouseMoved:
                    mouseCurrPos = getMousePosInWindow;

                    break;

                case sf::Event::MouseWheelMoved:
                    bouncingBall.setBallRadius(event.mouseWheel.delta);

                    break;

                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Space:
                            bouncingBall.velocity = -75;

                            break;

                        default: break;
                    }

                default: break;
            }

            if(bouncingBall.isDrag) bouncingBall.setBallPos(getMousePosDisplacement);

            mouseLastPos = mouseCurrPos;
        }

        if(!bouncingBall.isDrag)
        {
            bouncingBall.velocity += bouncingBall.accelery;
            dropping.x = 0;
            dropping.y = bouncingBall.velocity;

            bouncingBall.setBallPos(dropping);
        }

        window_Main.clear(sf::Color::Black);

        window_Main.draw(bouncingBall.ball);

        window_Main.display();
    }

    return EXIT_SUCCESS;
}

