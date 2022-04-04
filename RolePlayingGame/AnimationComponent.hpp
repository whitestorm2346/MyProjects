#ifndef ANIMATIONCOMPONENT_HPP_INCLUDED
#define ANIMATIONCOMPONENT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <string>
#include <map>

class AnimationComponent
{
private:
    class Animation
    {
    public:
        sf::Sprite& sprite;
        sf::Texture& textureSheet;
        float animationTimer;
        float timer;
        int width;
        int height;
        sf::IntRect startRect;
        sf::IntRect currRect;
        sf::IntRect endRect;

        Animation(sf::Sprite& sprite, sf::Texture& textureSheet,
                  float animationTimer,
                  int start_frame_x, int start_frame_y,
                  int frames_x, int frames_y,
                  int width, int height);

        void play(const float& deltaTime);
        void reset();
    };

    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    std::map<std::string, Animation*> animations;

public:
    AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
    virtual ~AnimationComponent();

    void addAnimation(const std::string key,
                      float animationTimer,
                      int start_frame_x, int start_frame_y,
                      int frames_x, int frames_y,
                      int width, int height);

    void play(const std::string key, const float& deltaTime);
};

#endif // ANIMATIONCOMPONENT_HPP_INCLUDED
