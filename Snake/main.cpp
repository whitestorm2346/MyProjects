#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <queue>
#include <string>

#define MATRIX_SIZE 10

enum Direction
{
    RIGHT = 0,
    LEFT,
    UP,
    DOWN
};

void gotoXY(short, short);
void hideCursor();
void setColor(int, bool);

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
    int score;
    void setGame();
    void printMatrix();
    HANDLE hOut;

public:
    std::string matrix[MATRIX_SIZE + 2][MATRIX_SIZE + 2];
    Snake snake;

    Game();
    ~Game();
    bool isCollide();
    bool isEat();
    void printHead();
    void removeTail();
    void generateFood();
    void printScore(int);
};

int main()
{
    Game* game = new Game();
    bool gameOver = false;

    game->printHead();
    game->generateFood();
    game->printScore(0);

    do
    {
        int key = 0;

        if(kbhit()) key = getch();

        if(key == 244)
        {
            key = getch();

            switch(key)
            {
                case 72:
                    if(game->snake.direction != DOWN) game->snake.direction = UP; break;

                case 75:
                    if(game->snake.direction != RIGHT) game->snake.direction = LEFT; break;

                case 80:
                    if(game->snake.direction != UP) game->snake.direction = DOWN; break;

                case 77:
                    if(game->snake.direction != LEFT) game->snake.direction = RIGHT; break;
            }
        }
        else
        {
            switch(key)
            {
                case 'w': case 'W':
                    if(game->snake.direction != DOWN) game->snake.direction = UP; break;

                case 'a': case 'A':
                    if(game->snake.direction != RIGHT) game->snake.direction = LEFT; break;

                case 's': case 'S':
                    if(game->snake.direction != UP) game->snake.direction = DOWN; break;

                case 'd': case 'D':
                    if(game->snake.direction != LEFT) game->snake.direction = RIGHT; break;
            }
        }

        game->snake.newHead();

        if(!game->isEat()) game->removeTail();
        else
        {
            game->generateFood();
            game->snake.speed -= 3;
            game->printScore(5);
        }

        if(game->isCollide()) gameOver = true;

        game->printHead();

        Sleep(game->snake.speed);
    }
    while(!gameOver);

    delete game;

    system("pause");

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
    body.push(new Body(MATRIX_SIZE / 2, MATRIX_SIZE / 2));
    direction = RIGHT;
    speed = 400;
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

    for(int i = 0; i < MATRIX_SIZE + 2; i++)
    {
        matrix[0][i] = "―";
        matrix[MATRIX_SIZE + 1][i] = "―";
    }

    for(int i = 1; i < MATRIX_SIZE + 1; i++)
    {
        matrix[i][0] = "―";
        matrix[i][MATRIX_SIZE + 1] = "―";
    }

    for(int i = 1; i < MATRIX_SIZE + 1; i++)
    {
        for(int j = 1; j < MATRIX_SIZE + 1; j++)
        {
            matrix[i][j] = "  ";
        }
    }
}
void Game::printMatrix()
{
    gotoXY(0, 0);
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
    hideCursor();

    for(int i = 0; i < MATRIX_SIZE + 2; i++)
    {
        for(int j = 0; j < MATRIX_SIZE + 2; j++)
        {
            std::cout<< matrix[i][j];
        }

        std::cout<< '\n';
    }

    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
Game::Game()
{
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    system("pause");
    setGame();
    printMatrix();
}
Game::~Game()
{
    gotoXY(0, MATRIX_SIZE + 5);

    std::cout<< "GAME OVER!!\n\n";
}
bool Game::isCollide()
{
    std::pair<short, short> headPos = snake.body.back()->pos;

    return matrix[headPos.second][headPos.first] == "―";
}
bool Game::isEat()
{
    std::pair<short, short> headPos = snake.body.back()->pos;

    return matrix[headPos.second][headPos.first] == "〃";
}
void Game::printHead()
{
    std::pair<short, short> headPos = snake.body.back()->pos;

    gotoXY(headPos.first * 2, headPos.second);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    std::cout<< "―";

    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    matrix[headPos.second][headPos.first] = "―";
}
void Game::removeTail()
{
    std::pair<short, short> tailPos = snake.body.front()->pos;

    gotoXY(tailPos.first * 2, tailPos.second);

    std::cout<< "  ";

    delete snake.body.front();

    snake.body.pop();

    matrix[tailPos.second][tailPos.first] = "  ";
}
void Game::generateFood()
{
    srand(time(NULL));

    int x, y;

    do
    {
        x = rand() % MATRIX_SIZE + 1;
        y = rand() % MATRIX_SIZE + 1;
    }
    while(matrix[y][x] != "  ");

    matrix[y][x] = "〃";

    gotoXY(x * 2, y);
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    std::cout<< "〃";

    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void Game::printScore(int delta)
{
    score += delta;

    gotoXY(0, MATRIX_SIZE + 3);
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    std::cout<< "Score: " << score;
}
