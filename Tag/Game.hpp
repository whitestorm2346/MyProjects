#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <utility>

#include "UserInterface.hpp"
#include "Charactor.hpp"
#include "List.hpp"
#include "Field.hpp"

class Game
{
private:
    std::pair<int, int> size;
    bool gameOver;
    Field* field;
    UserInterface* control;
    List<Character*>* characters;

public:
    Game();
    ~Game();

    void run();
};

#endif // GAME_HPP_INCLUDED
