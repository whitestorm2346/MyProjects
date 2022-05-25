#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>
#include <conio.h>
#include <windows.h>

#define FIELD_WIDTH  60
#define FIELD_HEIGHT 30

#define OBSTACLE_COUNT_MIN 5
#define OBSTACLE_COUNT_MAX 10

#define OBSTACLE_SIZE_MIN 3
#define OBSTACLE_SIZE_MAX 10

#define SizeOfItemType 4
enum ItemType{
    FAST = 1,
    SLOW,
    BOMB,
    TURN
};

#define SizeOfMonsterType 4
enum MonsterType{
    REGULAR = 1,
    BERSERKER,
    SHOOTER,
    PHANTOMS
};

enum Direction{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

// finished part
template <typename Type> class Node; // doubly node
template <typename Type> class List; // circular linked list
class Obstacle;
class Field;
class Timer;
class Distance;
class Character;

// unfinished part
class Player;
class Monster;
class Item;
class UserInterface;
class Game;

template <typename Type>
class Node{
private:
    Type _data_;
    Node<Type>* _prev_;
    Node<Type>* _next_;

public:
    Node(Type data);

    void setPrev(Node<Type>* prev);
    void setNext(Node<Type>* next);
    Type data();
    Node<Type>* prev();
    Node<Type>* next();
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
    void pop_front();
    void pop_back();
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
    std::pair<int, int> getSize();
    std::pair<int, int> getPosition();
};

class Field{
private:
    List<Obstacle*>* obstacles;
    std::string matrix[FIELD_HEIGHT + 2];

public:
    Field();
    virtual ~Field();

    void addObstacle();
    void generate();
    void print();
    void setMatrix(int x, int y, char code);
    char getMatrix(int x, int y);
};

class Timer{
private:
    clock_t checkPoint;
    double timeGap; // unit: second

public:
    Timer(double timeGap = 1.0);
    virtual ~Timer();

    void resetTimer();
    void setTimeGap(double timeGap);
    bool exceedTimeGap();
};

class Distance{
private:
    Player* player;
    Field* field;
    int distance[FIELD_HEIGHT][FIELD_HEIGHT];

public:
    Distance(Player* player, Field* field);
    virtual ~Distance();

    bool isInside(int x, int y);
    void setPlayer(Player* player);
    void setField(Field* field);
    void calculate();
};

class Character{
private:
    std::pair<int, int> position;
    char name;
    double speed; // unit: seconds per step
    Timer* timer;

public:
    Character(int x, int y, char name);
    virtual ~Character();

    virtual void move(int direction) = 0;
    virtual void action() = 0;
    virtual void print();
    virtual bool checkCollide(int x, int y, Field* field);
    virtual std::pair<int, int> getPosition();
};

class Player: public Character{
private:
public:
    Player(int x, int y);
    virtual ~Player();

    void move(int direction);
    void action();
};

class Monster: public Character{
private:
    int type;
    Timer* skillCountDown;

public:
    Monster(int x, int y, int type);
    virtual ~Monster();

    void move(int direction);
    void action();
};

class Item{
private:
    Timer* duration;
    std::pair<int, int> position;
    char type;

public:
    Item(int x, int y, char type);
    virtual ~Item();

    void print();
};

class UserInterface{
public:
    UserInterface();
    virtual ~UserInterface();

    int action();
};

class Game{
private:
    bool gameOver;
    bool noChange;
    int  score;
    int  duration;
    Timer* overOneSecond;
    Timer* generateCharacter;
    Timer* generateItem;
    Field* field;
    Distance* distance;
    UserInterface* control;
    List<Character*>* characters;
    List<Item*>* items;

public:
    Game();
    virtual ~Game();

    void run();
    void printField();
    void printCharacters();
    void printItems();
    void printInformation();
    std::pair<int, int> getRandomSpace();
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
    gameOver = false;
    noChange = false;
    score = 0;
    duration = 0;
    overOneSecond = new Timer(1.0);
    generateCharacter = new Timer(20.0);
    generateItem = new Timer(10.0);
    field = new Field();
    distance = new Distance(nullptr, field);
    control = new UserInterface();
    characters = new List<Character*>();
    items = new List<Item*>();
}
Game::~Game(){
    delete overOneSecond;
    delete generateCharacter;
    delete generateItem;
    delete field;
    delete control;
    delete characters;
    delete items;
}
void Game::run(){
    srand(time(nullptr));

    field->generate();

    characters->insert(new Node<Character*>(new Player(0, 0)));
    characters->insert(new Node<Character*>(new Monster(3, 3, REGULAR)));

    distance->setPlayer(reinterpret_cast<Player*>(characters->getFront()->data()));
    distance->calculate();

    while(!gameOver){
        if(!noChange){
            printField();
            printItems();
            printCharacters();

            noChange = true;
        }

        if(overOneSecond->exceedTimeGap()){
            ++score;
            ++duration;
            overOneSecond->resetTimer();
        }

        if(generateCharacter->exceedTimeGap()){
            std::pair<int, int> position = getRandomSpace();

            switch(rand() % SizeOfMonsterType + 1){
                case REGULAR:
                    characters->insert(new Node<Character*>(new Monster(position.first, position.second, REGULAR)));
                    break;

                case BERSERKER:
                    characters->insert(new Node<Character*>(new Monster(position.first, position.second, BERSERKER)));
                    break;

                case SHOOTER:
                    characters->insert(new Node<Character*>(new Monster(position.first, position.second, SHOOTER)));
                    break;

                case PHANTOMS:
                    characters->insert(new Node<Character*>(new Monster(position.first, position.second, PHANTOMS)));
                    break;
            }

            noChange = false;

            generateCharacter->resetTimer();
        }

        if(generateItem->exceedTimeGap()){
            std::pair<int, int> position = getRandomSpace();

            switch(rand() % SizeOfItemType + 1){
                case FAST:
                    items->insert(new Node<Item*>(new Item(position.first, position.second, 'F')));
                    break;

                case SLOW:
                    items->insert(new Node<Item*>(new Item(position.first, position.second, 'S')));
                    break;

                case BOMB:
                    items->insert(new Node<Item*>(new Item(position.first, position.second, 'B')));
                    break;

                case TURN:
                    items->insert(new Node<Item*>(new Item(position.first, position.second, 'T')));
                    break;
            }

            noChange = false;

            generateItem->resetTimer();
        }

        switch(control->action()){
            case UP:
            case RIGHT:
            case DOWN:
            case LEFT:
            default: break;
        }

        printInformation();
    }
}
void Game::printField(){
    gotoxy(0, 0);
    field->print();
    hideCursor();
}
void Game::printCharacters(){
    Node<Character*>* curr = characters->getFront();

    for(int i = 0; i < characters->size(); i++, curr = curr->next()){
        curr->data()->print();
    }

    hideCursor();
}
void Game::printItems(){
    Node<Item*>* curr = items->getFront();

    for(int i = 0; i < items->size(); i++, curr = curr->next()){
        curr->data()->print();
    }
}
void Game::printInformation(){
    gotoxy(0, FIELD_HEIGHT + 4);
    hideCursor();

    std::cout<< "Score: " << score << '\n';
    std::cout<< "Time: " << duration << '\n';
}
std::pair<int, int> Game::getRandomSpace(){
    int y = rand() % FIELD_HEIGHT;
    int x = rand() % FIELD_WIDTH;

    while(field->getMatrix(x + 1, y + 1) != ' '){
        x = rand() % FIELD_WIDTH;
    }

    return {x, y};
}

UserInterface::UserInterface(){

}
UserInterface::~UserInterface(){

}
int UserInterface::action(){
    if(kbhit())
    {
        int key = getch();

        if(key == 224)
        {
            key = getch();

            switch(key)
            {
                case 72: return UP;
                case 75: return LEFT;
                case 80: return DOWN;
                case 77: return RIGHT;
            }
        }
        else
        {
            switch(key)
            {
                case 'W': case 'w': return UP;
                case 'A': case 'a': return LEFT;
                case 'S': case 's': return DOWN;
                case 'D': case 'd': return RIGHT;
            }
        }
    }

    return -1;
}

Item::Item(int x, int y, char type): position({x, y}), type(type){

}
Item::~Item(){

}
void Item::print(){
    gotoxy(position.first + 1, position.second + 1);
    hideCursor();
    std::cout<< type;
}

Monster::Monster(int x, int y, int type): Character(x, y, (type + '0')), type(type){

}
Monster::~Monster(){

}
void Monster::move(int direction){

}
void Monster::action(){

}

Player::Player(int x, int y): Character(x, y, 'P'){

}
Player::~Player(){

}
void Player::move(int direction){

}
void Player::action(){

}

Character::Character(int x, int y, char name){
    this->name = name;
    position = {x, y};
    speed = 0.5;
    timer = new Timer(speed);
}
Character::~Character(){
    delete timer;
}
void Character::print(){
    gotoxy(position.first + 1, position.second + 1);
    hideCursor();
    std::cout<< name;
}
bool Character::checkCollide(int x, int y, Field* field){
    return (field->getMatrix(x, y) == '#') || (field->getMatrix(x, y) == '*');
}
std::pair<int, int> Character::getPosition(){
    return position;
}

Distance::Distance(Player* player, Field* field): player(player), field(field){

}
Distance::~Distance(){

}
bool Distance::isInside(int x, int y){
    return (x >= 0 && x < FIELD_WIDTH) && (y >= 0 && y < FIELD_HEIGHT);
}
void Distance::setPlayer(Player* player){
    this->player = player;
}
void Distance::setField(Field* field){
    this->field = field;
}
void Distance::calculate(){ // BFS
    bool check[FIELD_HEIGHT][FIELD_WIDTH] = {};

    List<std::pair<int, int>>* que = new List<std::pair<int, int>>();
    std::pair<int, int> playerPosition = player->getPosition();

    que->insert(new Node<std::pair<int, int>>(playerPosition));
    distance[playerPosition.second][playerPosition.first] = 0;

    while(!que->empty()){
        std::pair<int, int> currPos = que->getFront()->data();
        int x = currPos.first;
        int y = currPos.second;

        que->pop_front();

        //std::cout<< que->size() << " -> " << x << ' ' << y << '\n';

        check[y][x] = true;

        // up
        if(isInside(x, y - 1)){
            if((!check[y - 1][x]) && (field->getMatrix(x + 1, y) == ' ')){
                distance[y - 1][x] = distance[y][x] + 1;
                que->insert(new Node<std::pair<int, int>>({x, y - 1}));
            }
        }

        // right
        if(isInside(x + 1, y)){
            if((!check[y][x + 1]) && (field->getMatrix(x + 2, y + 1) == ' ')){
                distance[y][x + 1] = distance[y][x] + 1;
                que->insert(new Node<std::pair<int, int>>({x + 1, y}));
            }
        }

        // down
        if(isInside(x, y + 1)){
            if((!check[y + 1][x]) && (field->getMatrix(x + 1, y + 2) == ' ')){
                distance[y + 1][x] = distance[y][x] + 1;
                que->insert(new Node<std::pair<int, int>>({x, y + 1}));
            }
        }

        // left
        if(isInside(x - 1, y)){
            if((!check[y][x - 1]) && (field->getMatrix(x, y + 1) == ' ')){
                distance[y][x - 1] = distance[y][x] + 1;
                que->insert(new Node<std::pair<int, int>>({x - 1, y}));
            }
        }
    }

    delete que;
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

Field::Field(){ // initialize the field
    obstacles = new List<Obstacle*>();

    for(int i = 0; i < FIELD_WIDTH + 2; i++){
        matrix[0] += '#';
        matrix[FIELD_HEIGHT + 1] += '#';
    }

    for(int i = 1; i < FIELD_HEIGHT + 1; i++){
        matrix[i] += '#';

        for(int j = 1; j < FIELD_WIDTH + 1; j++){
            matrix[i] += ' ';
        }

        matrix[i] += '#';
    }
}
Field::~Field(){
    delete obstacles;
}
void Field::addObstacle(){
    obstacles->insert(new Node<Obstacle*>(
        new Obstacle(
            rand() % FIELD_WIDTH + 1, // x
            rand() % FIELD_HEIGHT + 1, // y
            rand() % (OBSTACLE_SIZE_MAX - OBSTACLE_SIZE_MIN + 1) + OBSTACLE_SIZE_MIN, // width
            rand() % (OBSTACLE_SIZE_MAX - OBSTACLE_SIZE_MIN + 1) + OBSTACLE_SIZE_MIN) // height
        )
    );
}
void Field::generate(){
    for(int times = rand() % (OBSTACLE_COUNT_MAX - OBSTACLE_COUNT_MIN + 1) + OBSTACLE_COUNT_MIN; times >= 0; --times){
        addObstacle();
    }

    Node<Obstacle*>* curr = obstacles->getFront();

    for(int i = 0; i < obstacles->size(); i++, curr = curr->next()){
        std::pair<int, int> size = curr->data()->getSize();
        std::pair<int, int> position = curr->data()->getPosition();

        for(int i = 0; i < size.second; i++){
            for(int j = 0; j < size.first; j++){
                int x = j + position.first + 1;
                int y = i + position.second + 1;

                if((x <= 0 || x >= FIELD_WIDTH + 1) ||
                   (y <= 0 || y >= FIELD_HEIGHT + 1)) continue;

                matrix[y][x] = '*';
            }
        }
    }
}
void Field::print(){
    for(int i = 0; i < FIELD_HEIGHT + 2; i++){
        std::cout<< matrix[i] << '\n';
    }
}
void Field::setMatrix(int x, int y, char code){
    matrix[y][x] = code;
}
char Field::getMatrix(int x, int y){
    return matrix[y][x];
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
std::pair<int, int> Obstacle::getSize(){
    return size;
}
std::pair<int, int> Obstacle::getPosition(){
    return position;
}

template <typename Type>
Node<Type>::Node(Type data){
    this->_data_ = data;
    _prev_ = nullptr;
    _next_ = nullptr;
}
template <typename Type>
void Node<Type>::setPrev(Node<Type>* prev){
    _prev_ = prev;
}
template <typename Type>
void Node<Type>::setNext(Node<Type>* next){
    _next_ = next;
}
template <typename Type>
Type Node<Type>::data(){
    return _data_;
}
template <typename Type>
Node<Type>* Node<Type>::prev(){
    return _prev_;
}
template <typename Type>
Node<Type>* Node<Type>::next(){
    return _next_;
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
        pop_back();
    }
}
template <typename Type>
void List<Type>::insert(Node<Type>* newNode){
    if(nodeCount == 0){
        front = back = newNode;
        newNode->setNext(newNode);
        newNode->setPrev(newNode);
    }
    else{
        front->setPrev(newNode);
        back->setNext(newNode);
        newNode->setNext(front);
        newNode->setPrev(back);
        back = newNode;
    }

    nodeCount++;
}
template <typename Type>
void List<Type>::pop_front(){
    if(nodeCount <= 0) return;

    Node<Type>* temp = front;

    if(nodeCount == 1){
        front = nullptr;
        back = nullptr;
    }
    else{
        back->setNext(front->next());
        front->next()->setPrev(back);
        front = front->prev();
    }

    nodeCount--;

    delete temp;
}
template <typename Type>
void List<Type>::pop_back(){
    if(nodeCount <= 0) return;

    Node<Type>* temp = back;

    if(nodeCount == 1){
        front = nullptr;
        back = nullptr;
    }
    else{
        front->setPrev(back->prev());
        back->prev()->setNext(front);
        back = back->prev();
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
