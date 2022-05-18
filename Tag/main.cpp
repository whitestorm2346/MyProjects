#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>
#include <conio.h>
#include <windows.h>

#define FIELD_WIDTH  30
#define FIELD_HEIGHT 30

template <typename Type> class Node; // doubly node
template <typename Type> class List; // circular linked list

class Obstacle;
class Field;
class Timer;
class Distance;
class Character;
class Player;
class Monster;
class Item;
class UserInterface;
class Game;

template <typename Type>
class Node{
public:
    Type data;
    Node<Type>* prev;
    Node<Type>* next;

    Node(Type data);
};

template <typename Type>
class List{
private:
    Node<Type>* front;
    Node<Type>* back;
    int nodeCount;

public:
    List();
    virtual ~List();

    void insert(Node<Type>* newNode);
    void erase();
    bool empty();
    int  size();

    Node<Type>* getFront();
    Node<Type>* getBack();
};

class Obstacle{
private:
    std::pair<int, int> size;
    std::pair<int, int> position;

public:
    Obstacle(int x, int y, int width, int height);
    virtual ~Obstacle();

    void setSize(int width, int height);
    void setPosition(int x, int y);
};

class Field{
private:
    std::pair<int, int> size;
    List<Obstacle*>* obstacles;

public:
    char** matrix;

    Field(int width, int height);
    virtual ~Field();

    void setSize(int width, int height);
    void addObstacle();
    void generate();
    void print();
};

class Timer{
private:
    clock_t checkPoint;
    double timeGap;

public:
    Timer(double timeGap = 1.0);
    virtual ~Timer();

    void resetTimer();
    void setTimeGap(double timeGap);
    bool exceedTimeGap();
};

class Distance{
private:
    std::pair<int, int> position;
    Field* field;
    int** distance;

public:
    Distance();
    virtual ~Distance();

    void setField();
    void countDistance();
};

class Character{
private:
    std::string name;
    std::pair<int, int> position;
    double speed; // unit: seconds per step
    Timer* timer;

public:
    Character();
    virtual ~Character();

    virtual void move() = 0;
    virtual bool checkCollide();
};

class Player: public Character{
private:
public:
    Player();
    virtual ~Player();

    void move();
};

class Monster: public Character{
private:
public:
    Monster();
    virtual ~Monster();

    void move();
};

class Item{
private:
    std::pair<int, int> position;
    int type;

public:
    Item();
    virtual ~Item();
};

class UserInterface{
public:
    UserInterface();
    virtual ~UserInterface();

    void action();
};

class Game{
private:
    std::pair<int, int> size;
    bool gameOver;
    Field* field;
    UserInterface* control;
    List<Character*>* characters;

public:
    Game();
    virtual ~Game();

    void run();
};

void gotoxy(int x, int y);
void hideCursor();

int main(){
    Game game;

    game.run();

    return 0;
}

void gotoxy(int x, int y){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {static_cast<short>(x), static_cast<short>(y)};

    SetConsoleCursorPosition(hOut, pos);
}
void hideCursor(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hOut, &cursorInfo);

    cursorInfo.bVisible = false;

    SetConsoleCursorInfo(hOut, &cursorInfo);
}

Game::Game(){
    srand(time(nullptr));

    size = {FIELD_WIDTH, FIELD_HEIGHT};
    gameOver = false;
    field = new Field(size.first, size.second);
    control = new UserInterface();
    characters = new List<Character*>();
}
Game::~Game(){
    delete field;
    delete control;
    delete characters;
}
void Game::run(){
    while(!gameOver){

    }
}

UserInterface::UserInterface(){

}
UserInterface::~UserInterface(){

}
void UserInterface::action(){

}

Item::Item(std::pair<int, int> position, int type): position(position), type(type){

}
Item::~Item(){

}

Monster::Monster(){

}
Monster::~Monster(){

}
void Monster::move(){

}

Player::Player(){

}
Player::~Player(){

}
void Player::move(){

}

Character::Character(){
    name = "O";
    position = {0, 0};
    speed = 0.5;
    timer = new Timer(speed);
}
Character::~Character(){
    delete timer;
}
bool Character::checkCollide(){
    return true;
}

Distance::Distance(){

}
Distance::~Distance(){

}
void Distance::setField(){

}
void Distance::countDistance(){

}

Timer::Timer(double timeGap): checkPoint(clock()), timeGap(timeGap){

}
Timer::~Timer(){

}
void Timer::resetTimer(){
    checkPoint = clock();
}
void Timer::setTimeGap(double timeGap){
    this->timeGap = timeGap;
}
bool Timer::exceedTimeGap(){
    return (static_cast<double>(clock() - checkPoint) / CLK_TCK >= timeGap);
}

Field::Field(int width, int height){
    size = {width, height};
    obstacles = new List<Obstacle*>();
    matrix = new char*[height];

    for(int i = 0; i < height; i++){
        matrix[i] = new char[width];

        for(int j = 0; j < width; j++){
            matrix[i][j] = ' ';
        }
    }
}
Field::~Field(){
    for(int i = 0; i < size.second; i++){
        delete [] matrix[i];
    }

    delete [] matrix;
    delete obstacles;
}
void Field::setSize(int width, int height){
    size = {width, height};
}
void Field::addObstacle(){
    obstacles->insert(new Node<Obstacle*>(
        new Obstacle(
            rand() % size.first,
            rand() % size.second,
            rand() % (size.first / 10) + 1,
            rand() % (size.second / 10) + 1)
        )
    );
}
void Field::generate(){
    /**
        wait to be implemented
    */
}
void Field::print(){
    for(int i = 0; i < size.second; i++){
        for(int j = 0; j < size.second; j++){
            std::cout<< matrix[i][j];
        }

        std::cout<< '\n';
    }
}

Obstacle::Obstacle(int x, int y, int width, int height){
    size = {width, height};
    position = {x, y};
}
Obstacle::~Obstacle(){

}
void Obstacle::setSize(int width, int height){
    size = {width, height};
}
void Obstacle::setPosition(int x, int y){
    position = {x, y};
}

template <typename Type>
Node<Type>::Node(Type data){
    this->data = data;
    prev = nullptr;
    next = nullptr;
}
template <typename Type>
List<Type>::List(){
    front = nullptr;
    back = nullptr;
    nodeCount = 0;
}
template <typename Type>
List<Type>::~List(){
    while(!empty()){
        erase();
    }
}
template <typename Type>
void List<Type>::insert(Node<Type>* newNode){
    if(nodeCount == 0){
        front = back = newNode;
        newNode->next = newNode->prev = newNode;
    }
    else{
        front->prev = back->next = newNode;
        newNode->next = front;
        newNode->prev = back;
        back = newNode;
    }

    nodeCount++;
}
template <typename Type>
void List<Type>::erase(){
    if(nodeCount <= 0) return;

    Node<Type>* temp = back;

    if(nodeCount == 1){
        front = nullptr;
        back = nullptr;
    }
    else{
        front->prev = back->prev;
        back->prev->next = front;
        back = back->prev;
    }

    nodeCount--;

    delete temp;
}
template <typename Type>
bool List<Type>::empty(){
    return (nodeCount == 0);
}
template <typename Type>
int List<Type>::size(){
    return nodeCount;
}
template <typename Type>
Node<Type>* List<Type>::getFront(){
    return front;
}
template <typename Type>
Node<Type>* List<Type>::getBack(){
    return back;
}
