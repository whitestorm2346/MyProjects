#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <queue>

#define MATRIX_HEIGHT 10
#define MATRIX_WIDTH (2 * MATRIX_HEIGHT)

enum Direction
{
    RIGHT = 0,
    LEFT,
    UP,
    DOWN
};

void gotoXY(short, short);
void hideCursor();

class Body
{
public:
    std::pair<short, short> pos;

    Body(short, short);
};

class Snake
{
public:
    std::queue<Body*> body;
    int direction;
    int speed;

    Snake();
    ~Snake();
    void newHead();
    void cutTail();
};

class Game
{
    void setGame();
    void printMatrix();

public:
    int score;
    char matrix[MATRIX_HEIGHT + 2][MATRIX_WIDTH + 2];
    Snake snake;

    Game();
    ~Game();
    bool isCollide();
    bool isEat();
    void printHead();
    void removeTail();
    void generateFood();
};

int main()
{
    hideCursor();

    Game game;
    bool gameOver = false;

    game.printHead();
    game.generateFood();

    do
    {
        char key;

        if(kbhit()) key = getch();

        switch(key)
        {
            case 'w': case 'W': game.snake.direction = UP; break;
            case 'a': case 'A': game.snake.direction = LEFT; break;
            case 's': case 'S': game.snake.direction = DOWN; break;
            case 'd': case 'D': game.snake.direction = RIGHT; break;
        }

        game.snake.newHead();

        if(!game.isEat()) game.removeTail();
        else game.generateFood();

        if(game.isCollide()) gameOver = true;

        game.printHead();

        Sleep(game.snake.speed);
    }
    while(!gameOver);

    return 0;
}

void gotoXY(short x, short y)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};

    SetConsoleCursorPosition(hOut, pos);
}
void hideCursor()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hOut, &cursorInfo);

    cursorInfo.bVisible = false;

    SetConsoleCursorInfo(hOut, &cursorInfo);
}
Body::Body(short x, short y)
{
    pos.first = x;
    pos.second = y;
}
Snake::Snake()
{
    body.push(new Body(MATRIX_WIDTH / 2, MATRIX_HEIGHT / 2));
    direction = RIGHT;
    speed = 500;
}
Snake::~Snake()
{
    for(; !body.empty();)
    {
        delete body.front();
        body.pop();
    }
}
void Snake::newHead()
{
    std::pair<short, short> lastPos = body.back()->pos;

    switch(direction)
    {
        case RIGHT: body.push(new Body(lastPos.first + 1, lastPos.second)); break;
        case LEFT:  body.push(new Body(lastPos.first - 1, lastPos.second)); break;
        case UP:    body.push(new Body(lastPos.first, lastPos.second - 1)); break;
        case DOWN:  body.push(new Body(lastPos.first, lastPos.second + 1)); break;
    }
}
void Game::setGame()
{
    score = 0;

    for(int i = 0; i < MATRIX_WIDTH + 2; i++)
    {
        matrix[0][i] = '#';
        matrix[MATRIX_HEIGHT + 1][i] = '#';
    }

    for(int i = 1; i < MATRIX_HEIGHT + 1; i++)
    {
        matrix[i][0] = '#';
        matrix[i][MATRIX_WIDTH + 1] = '#';
    }

    for(int i = 1; i < MATRIX_HEIGHT + 1; i++)
    {
        for(int j = 1; j < MATRIX_WIDTH + 1; j++)
        {
            matrix[i][j] = ' ';
        }
    }
}
void Game::printMatrix()
{
    gotoXY(0, 0);

    for(int i = 0; i < MATRIX_HEIGHT + 2; i++)
    {
        for(int j = 0; j < MATRIX_WIDTH + 2; j++)
        {
            std::cout<< matrix[i][j];
        }

        std::cout<< '\n';
    }
}
Game::Game()
{
    setGame();
    printMatrix();
}
Game::~Game()
{
    gotoXY(0, MATRIX_HEIGHT + 4);

    std::cout<< "GAME OVER!!";
}
bool Game::isCollide()
{
    std::pair<short, short> headPos = snake.body.back()->pos;

    return (matrix[headPos.second][headPos.first] == '#') ||
           (matrix[headPos.second][headPos.first] == 'O');
}
bool Game::isEat()
{
    std::pair<short, short> headPos = snake.body.back()->pos;

    return matrix[headPos.second][headPos.first] == '@';
}
void Game::printHead()
{
    std::pair<short, short> headPos = snake.body.back()->pos;

    gotoXY(headPos.first, headPos.second);

    std::cout<< 'O';

    matrix[headPos.second][headPos.first] = 'O';
}
void Game::removeTail()
{
    std::pair<short, short> tailPos = snake.body.front()->pos;

    gotoXY(tailPos.first, tailPos.second);

    std::cout<< ' ';

    delete snake.body.front();

    snake.body.pop();

    matrix[tailPos.second][tailPos.first] = ' ';
}
void Game::generateFood()
{
    srand(time(NULL));

    int x, y;

    do
    {
        x = rand() % MATRIX_WIDTH + 1;
        y = rand() % MATRIX_HEIGHT + 1;
    }
    while(matrix[y][x] != ' ');

    matrix[y][x] = '@';

    gotoXY(x, y);

    std::cout<< '@';
}
