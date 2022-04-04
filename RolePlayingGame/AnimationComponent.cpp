#include "AnimationComponent.hpp"

AnimationComponent::Animation::Animation(
    sf::Sprite& sprite, sf::Texture& textureSheet,
    float animationTimer,
    int start_frame_x, int start_frame_y,
    int frames_x, int frames_y,
    int width, int height
):  sprite(sprite), textureSheet(textureSheet), animationTimer(animationTimer),
    width(width), height(height)
{
    timer = 0.f;
    startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
    currRect = startRect;
    endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

    sprite.setTexture(textureSheet, true);
    sprite.setTextureRect(startRect);
}

void AnimationComponent::Animation::play(const float& deltaTime)
{
    timer += 100.f * deltaTime;

    if(timer >= animationTimer)
    {
        timer = 0.f;

        if(currRect != endRect) currRect.left += width;
        else currRect.left = startRect.left;

        sprite.setTextureRect(currRect);
    }
}
void AnimationComponent::Animation::reset()
{
    timer = 0.f;
    currRect = startRect;
}

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
    : sprite(sprite), textureSheet(textureSheet)
{

}
AnimationComponent::~AnimationComponent()
{
    for(auto &i: animations)
    {
        delete i.second;
    }
}

void AnimationComponent::addAnimation(
    const std::string key,
    float animationTimer,
    int start_frame_x, int start_frame_y,
    int frames_x, int frames_y,
    int width, int height)
{
    animations[key] = new Animation(
                            sprite, textureSheet, animationTimer,
                            start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}
void AnimationComponent::play(const std::string key, const float& deltaTime)
{
    animations[key]->play(deltaTime);
}
