#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>

#define winWidth 800
#define winHeight 1000
#define ballRadius 75

#define getMousePosInWindow mousePosInWindow(window_Main.getPosition(), sf::Mouse::getPosition())
#define getMousePosDisplacement mousePosDisplacement(mouseLastPos, mouseCurrPos)

class Ball
{
public:
    bool isCollide;
    bool isDrag;
    float velocity;
    const float accelery = 2.5f;
    sf::CircleShape ball;

    Ball()
    {
        isCollide = false;
        isDrag = false;
        velocity = 0;
        ball.setRadius(ballRadius);
        ball.setFillColor(sf::Color::White);
        ball.setOrigin(ballRadius + 1, ballRadius + 1);
        ball.setPosition(winWidth / 2, winHeight - ballRadius);
    }
    ~Ball(){}
};

sf::Vector2i mousePosInWindow(const sf::Vector2i&, const sf::Vector2i&);
sf::Vector2i mousePosDisplacement(const sf::Vector2i&, const sf::Vector2i&);
void setRandomColor(Ball&);
void setBallPos(Ball&, sf::Vector2i);
bool isInCircle(const sf::Vector2f, const sf::Vector2i);

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
                            setRandomColor(bouncingBall);

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

                    if(bouncingBall.isDrag) setBallPos(bouncingBall, getMousePosDisplacement);

                    break;

                default: break;
            }

            if(!bouncingBall.isDrag)
            {
                bouncingBall.velocity += bouncingBall.accelery;
                dropping.x = 0;
                dropping.y = bouncingBall.velocity;

                setBallPos(bouncingBall, dropping);
            }

            mouseLastPos = mouseCurrPos;
        }

        window_Main.clear(sf::Color::Black);

        window_Main.draw(bouncingBall.ball);

        window_Main.display();
    }

    return EXIT_SUCCESS;
}

sf::Vector2i mousePosInWindow(const sf::Vector2i& windowPos, const sf::Vector2i& mousePos)
{
    sf::Vector2i _mousePosInWindow;

    _mousePosInWindow.x = mousePos.x - windowPos.x;
    _mousePosInWindow.y = mousePos.y - windowPos.y;

    return _mousePosInWindow;
}
sf::Vector2i mousePosDisplacement(const sf::Vector2i& lastPos, const sf::Vector2i& currPos)
{
    sf::Vector2i _mousePosDisplacement;

    _mousePosDisplacement.x = currPos.x - lastPos.x;
    _mousePosDisplacement.y = currPos.y - lastPos.y;

    return _mousePosDisplacement;
}
void setRandomColor(Ball& obj)
{
    auto color = sf::Color{rand() % 206 + 50, rand() % 206 + 50, rand() % 206 + 50};

    obj.ball.setFillColor(color);
}
void setBallPos(Ball& obj, sf::Vector2i displacement)
{
    sf::Vector2f objPos = obj.ball.getPosition();

    objPos.x += displacement.x;
    objPos.y += displacement.y;

    if(objPos.x < ballRadius)
    {
        objPos.x = ballRadius;
        //setRandomColor(obj);
    }
    else if(objPos.x > winWidth - ballRadius)
    {
        objPos.x = winWidth - ballRadius;
        //setRandomColor(obj);
    }

    if(objPos.y < ballRadius)
    {
        objPos.y = ballRadius;
        obj.isCollide = false;
    }
    else if(objPos.y > winHeight - ballRadius)
    {
        if(!obj.isCollide) setRandomColor(obj);

        objPos.y = winHeight - ballRadius;
        obj.isCollide = true;
    }
    else obj.isCollide = false;

    obj.ball.setPosition(objPos);
}
bool isInCircle(const sf::Vector2f objPos, const sf::Vector2i mousePos)
{
    double x_gap = abs(objPos.x - mousePos.x);
    double y_gap = abs(objPos.y - mousePos.y);

    return (x_gap * x_gap + y_gap * y_gap) < (ballRadius * ballRadius);
}
