#ifndef BALL_HPP_INCLUDED
#define BALL_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cstdlib>
#include <ctime>
#include <cmath>

const float winWidth = 800.f;
const float winHeight = 1000.f;
const float ElasticityCoefficient = 0.95f;
float ballRadius = 100.f;

sf::SoundBuffer sBuffer;
sf::Sound Collide;

template <typename type>
struct Coordinate
{
    type x;
    type y;
};

class Ball
{
public:
    bool isDrag;
    Coordinate<bool> isCollide;
    Coordinate<float> v;
    Coordinate<float> a;
    sf::CircleShape ball;

    Ball();
    ~Ball(){}

    void setRandomColor();
    void setBallPos(sf::Vector2i);
    void setBallRadius(int);
};

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
Ball::Ball()
{
    isDrag = false;
    isCollide.x = false;
    isCollide.y = true;
    v.x = 0;
    v.y = 0;
    a.x = 0;
    a.y = 5.f;
    ball.setRadius(ballRadius);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(ballRadius + 1, ballRadius + 1);
    ball.setPosition(winWidth / 2, winHeight - ballRadius);

    if(!sBuffer.loadFromFile("gameBallBounce.wav")) exit(1);

    Collide.setBuffer(sBuffer);
}
void Ball::setRandomColor()
{
    auto color = sf::Color{
        static_cast<unsigned char>(rand() % 256),
        static_cast<unsigned char>(rand() % 256),
        static_cast<unsigned char>(rand() % 256)
    };

    ball.setFillColor(color);
}
void Ball::setBallPos(sf::Vector2i displacement)
{
    sf::Vector2f objPos = ball.getPosition();

    objPos.x += displacement.x;
    objPos.y += displacement.y;

    if(objPos.x <= ballRadius)
    {
        if(!isCollide.x && !isDrag)
        {
            setRandomColor();
            Collide.play();
        }

        objPos.x = ballRadius;
        isCollide.x = true;
        v.x = -(v.x * ElasticityCoefficient);
    }
    else if(objPos.x >= winWidth - ballRadius)
    {
        if(!isCollide.x && !isDrag)
        {
            setRandomColor();
            Collide.play();
        }

        objPos.x = winWidth - ballRadius;
        isCollide.x = true;
        v.x = -(v.x * ElasticityCoefficient);
    }
    else isCollide.x = false;

    if(objPos.y >= winHeight - ballRadius) // drop on floor
    {
        if(!isCollide.y && !isDrag)
        {
            setRandomColor();
            Collide.play();
        }

        objPos.y = winHeight - ballRadius;
        isCollide.y = true;
        v.x *= ElasticityCoefficient;
        v.y = -(v.y * ElasticityCoefficient);
    }
    else isCollide.y = false;

    ball.setPosition(objPos);
}
bool isInCircle(const sf::Vector2f objPos, const sf::Vector2i mousePos)
{
    double x_gap = abs(objPos.x - mousePos.x);
    double y_gap = abs(objPos.y - mousePos.y);

    return (x_gap * x_gap + y_gap * y_gap) < (ballRadius * ballRadius);
}
void Ball::setBallRadius(int delta)
{
    ballRadius += static_cast<float>(delta);

    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius + 1, ballRadius + 1);
}

#endif // BALL_HPP_INCLUDED
