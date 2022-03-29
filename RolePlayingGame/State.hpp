#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

#include "Entity.hpp"

class State
{
protected:
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int>  keybinds;
    std::vector<sf::Texture> textures;
    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    virtual void initKeybinds() = 0;

public:
    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
    virtual ~State();

    const bool& getQuit() const;

    virtual void checkForQuit();
    virtual void endState() = 0;
    virtual void updateMousePositions();
    virtual void updateInput(const float& deltaTime) = 0;
    virtual void update(const float& deltaTime) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif // STATE_HPP_INCLUDED
