#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>
#include <queue> // only for BFS
#include <conio.h>
#include <windows.h>

#define DEFAULT -1

#define KILL_MONSTER 5

#define GENERATE_CHARACTER_COUNT_DOWN 20.0
#define GENERATE_ITEM_COUNT_DOWN 10.0

#define FIELD_WIDTH  60
#define FIELD_HEIGHT 30

#define PLAYER_SPEED 0.3
#define MONSTER_SPEED 0.6

#define OBSTACLE_COUNT_MIN 5
#define OBSTACLE_COUNT_MAX 10

#define OBSTACLE_SIZE_MIN 5
#define OBSTACLE_SIZE_MAX 10

#define FAST_DURATION 5.0
#define SLOW_DURATION 5.0
#define BOMB_DURATION 0.0
#define TURN_DURATION 5.0

#define REGULAR_COUNT_DOWN 0.0
#define BERSERKER_COUNT_DOWN 20.0
#define PHANTOMS_COUNT_DOWN 10.0

#define REGULAR_DURATION 0.0
#define BERSERKER_DURATION 5.0
#define PHANTOMS_DURATION 3.0

#define SizeOfItemType 4
enum ItemType{
    FAST = 1,
    SLOW,
    BOMB,
    TURN
};

#define SizeOfMonsterType 3
enum MonsterType{
    REGULAR = 1,
    BERSERKER,
    PHANTOMS
};

enum Direction{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
    IDLE
};

template <typename Type> class Node; // doubly node
template <typename Type> class List; // circular linked list

class Obstacle;
class Field;
class Timer;
class Distance;
class UserInterface;

class Character;
class Player;
class Monster;
class RegularMonster;
class BerserkerMonster;
class PhantomsMonster;

class Item;
class FastItem;
class SlowItem;
class BombItem;
class TurnItem;

class Game;

template <typename Type>
class Node{ // doubly node
private:
    Type _data_;
    Node<Type>* _prev_;
    Node<Type>* _next_;

public:
    Node(Type data);

    void setPrev(Node<Type>* prev);
    void setNext(Node<Type>* next);
    void pop_self(); // use for killing monsters or collecting items
    Type data();
    Node<Type>* prev();
    Node<Type>* next();
};

template <typename Type>
class List{ // circular linked list
private:
    Node<Type>* front;
    Node<Type>* back;
    int nodeCount;

public:
    List();
    ~List();

    void insert(Node<Type>* newNode);
    void pop_front();
    void pop_back();
    void setFront(Node<Type>* front);
    void setBack(Node<Type>* back);
    void setSize(int size);
    bool empty();
    int  size();

    Node<Type>* getFront();
    Node<Type>* getBack();
};

class Obstacle{
private:
    std::pair<int, int> size; // rectangle shape
    std::pair<int, int> position;

public:
    Obstacle(int x, int y, int width, int height);
    ~Obstacle();

    void setSize(int width, int height);
    void setPosition(int x, int y);
    std::pair<int, int> getSize();
    std::pair<int, int> getPosition();
};

class Field{
private:
    List<Obstacle*>* obstacles;
    std::string matrix[FIELD_HEIGHT + 2]; // string.length() -> FIELD_WIDTH + 2

public:
    Field();
    ~Field();

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
    Timer(double timeGap);
    ~Timer();

    void resetTimer();
    void setTimeGap(double timeGap);
    bool exceedTimeGap();
};

class Distance{
private:
    Player* player;
    Field* field;
    int distance[FIELD_HEIGHT][FIELD_WIDTH];

public:
    Distance(Player* player, Field* field);
    ~Distance();

    int  getDistance(int x, int y);
    bool isInside(int x, int y);
    void setPlayer(Player* player);
    void setField(Field* field);
    void calculate(); // BFS
    void print(); // for testing
};

class Character{
protected:
    static bool turnItemCollected;
    std::pair<int, int> position;
    int* score;
    char name;
    bool canMove;
    bool _skill_;
    bool _characterPrint_;
    double speed; // unit: seconds per step
    Timer* timer;
	Timer* skillCountDown;

public:
    Character(int x, int y, char name, double speed, int* score);
    virtual ~Character();

    virtual void setDefaultSpeed() = 0;
    virtual void action() = 0;
    virtual void actionLose() = 0;

    virtual void move(bool& noChange, int direction = IDLE);
    virtual void print();
    virtual bool checkCollide(int x, int y, Field* field);
    virtual std::pair<int, int> getPosition();

    void addScore(int num);
    void setSpeed(double speed);
    void changeMode(bool status); // for turn item
    void SetcharacterPrint(bool status); // for Phantoms
	bool getMode();
	bool characterPrint();
    bool skill();
    bool skillTimeExpird();
    double getSpeed();
    char Type();
};

bool Character::turnItemCollected = false;

class Player: public Character{
private:
public:
    Player(int x, int y, int* score);
    ~Player();

    void action();
    void setDefaultSpeed();
    void actionLose();
};

class Monster: public Character{
protected:

public:
    Monster(int x, int y, char type, int* score);
    virtual ~Monster();

    virtual void action();
    virtual void actionLose();
    virtual void setDefaultSpeed();

    bool checkCatchPlayer(int x, int y);
};

class RegularMonster: public Monster{
private:
public:
    RegularMonster(int x, int y, int* score);
    ~RegularMonster();

    void action();
    void actionLose();
};

class BerserkerMonster: public Monster{
private:
public:
    BerserkerMonster(int x, int y, int* score);
    ~BerserkerMonster();

    void action();
    void actionLose();
};

class PhantomsMonster: public Monster{
private:
public:
    PhantomsMonster(int x, int y, int* score);
    ~PhantomsMonster();

    void action();
    void actionLose();
};

class Item{
protected:
    Timer* duration;
    std::pair<int, int> position;
    bool _isCollected_;
    char type;
    List<Character*>* characters;

public:
    Item(int x, int y, char type, double timeGap, List<Character*>* characters);
    virtual ~Item();

    virtual void print();
    virtual void effect() = 0;
    virtual void buffLoseEffectiveness() = 0;

    bool isCollected();
    bool buffTimeExpired();
    char getType();
    std::pair<int, int> getPosition();
};

class FastItem: public Item{
private:
public:
    FastItem(int x, int y, List<Character*>* characters);
    ~FastItem();

    void effect();
    void buffLoseEffectiveness();
};

class SlowItem: public Item{
private:
public:
    SlowItem(int x, int y, List<Character*>* characters);
    ~SlowItem();

    void effect();
    void buffLoseEffectiveness();
};

class BombItem: public Item{
private:
public:
    BombItem(int x, int y, List<Character*>* characters);
    ~BombItem();

    void effect();
    void buffLoseEffectiveness();
};

class TurnItem: public Item{
private:
public:
    TurnItem(int x, int y, List<Character*>* characters);
    ~TurnItem();

    void effect();
    void buffLoseEffectiveness();
};

class UserInterface{
public:
    UserInterface();
    ~UserInterface();

    int action(bool& godMode);
};

class Game{
private:
    bool godMode; // for testing
    bool gameOver;
    bool noChange; // if the view is not changed, then the field does not need to be refresh
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
    ~Game();

    static void printStatus(std::string status);

    void run();
    void printField();
    void printCharacters();
    void printItems();
    void printInformation();
    void checkOverOneSecond();
    void checkGenerateCharacter();
    void checkGenerateItem();
    void checkPlayerMoving();
    void checkPlayerCollectItem();
    void checkPlayerCaughtMonster();
    void checkMonsterMoving();
    void checkMonsterCaughtPlayer();
    void checkBuffExpired();
    void checkMonsterSkill();
    std::pair<int, int> getRandomSpot();
};

void gotoxy(int x, int y);
void hideCursor();

int main(){
    char kbInput;

    do{
        system("cls");
        gotoxy(0, 0);
        hideCursor();

        std::cout<< "###############################\n";
        std::cout<< "#                             #\n";
        std::cout<< "#        Tag Game 2022        #\n";
        std::cout<< "#                             #\n";
        std::cout<< "###############################\n";
        std::cout<< "\n>>> press any key to start!";

        getch();

        Game* game = new Game();

        game->run();

        delete game;

        kbInput = getch();
    }
    while(kbInput == 'R' || kbInput == 'r');

    Sleep(3000);

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
    godMode = false;
    gameOver = false;
    noChange = false;
    score = 0;
    duration = 0;
    overOneSecond = new Timer(1.0);
    generateCharacter = new Timer(GENERATE_CHARACTER_COUNT_DOWN);
    generateItem = new Timer(GENERATE_ITEM_COUNT_DOWN);
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
void Game::printStatus(std::string status){
    gotoxy(0, FIELD_HEIGHT + 7);

    std::cout<< "                                                                                          \r";
    std::cout<< ">>> " << status << '\n';

    hideCursor();
}
void Game::run(){ // main loop
    srand(time(nullptr));

    field->generate();

    std::pair<int, int> randomSpot;

    randomSpot = getRandomSpot();

    characters->insert(new Node<Character*>(new Player(randomSpot.first, randomSpot.second, &score)));

    randomSpot = getRandomSpot();

    characters->insert(new Node<Character*>(new RegularMonster(randomSpot.first, randomSpot.second, &score)));

    distance->setPlayer(reinterpret_cast<Player*>(characters->getFront()->data()));

    distance->calculate();

    while(godMode || !gameOver){
        if(!noChange){
            printField();
            printItems();
            printCharacters();

            noChange = true;
        }

        checkOverOneSecond();
        checkGenerateCharacter();
        checkGenerateItem();

        checkPlayerMoving();
        checkPlayerCollectItem();

        checkMonsterMoving();

        if(characters->getFront()->data()->getMode()) checkPlayerCaughtMonster();
        else checkMonsterCaughtPlayer();

        checkBuffExpired();
        checkMonsterSkill();

        printInformation();
    }

    printField();
    printItems();
    printCharacters();

    printStatus("Game Over!! Press R to play again.");

    gotoxy(0, FIELD_HEIGHT + 9);
}
void Game::printField(){
    gotoxy(0, 0);
    field->print();
    hideCursor();
}
void Game::printCharacters(){
    Node<Character*>* curr = characters->getFront();

    for(int i = 0; i < characters->size(); i++, curr = curr->next()){
    	if(curr->data()->characterPrint()){
    		curr->data()->print();
		}

    	hideCursor();
	}
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

    printf("Time: %02d:%02d\n", duration / 60, duration % 60);
    std::cout<< "Score: " << score << '\n';
}
void Game::checkOverOneSecond(){
    if(overOneSecond->exceedTimeGap()){
        ++score;
        ++duration;

        overOneSecond->resetTimer();
    }
}
void Game::checkGenerateCharacter(){
    if(generateCharacter->exceedTimeGap()){
        std::pair<int, int> position = getRandomSpot();

        switch(rand() % SizeOfMonsterType + 1){
            case REGULAR:
                characters->insert(new Node<Character*>(new RegularMonster(position.first, position.second, &score)));
                break;

            case BERSERKER:
                characters->insert(new Node<Character*>(new BerserkerMonster(position.first, position.second, &score)));
                break;

            case PHANTOMS:
                characters->insert(new Node<Character*>(new PhantomsMonster(position.first, position.second, &score)));
                break;
        }

        noChange = false;

        generateCharacter->resetTimer();
    }
}
void Game::checkGenerateItem(){
    if(generateItem->exceedTimeGap()){
        std::pair<int, int> position = getRandomSpot();

        switch(rand() % SizeOfItemType + 1){
            case FAST:
                items->insert(new Node<Item*>(new FastItem(
                                                  position.first,
                                                  position.second,
                                                  characters
                                              )));
                break;

            case SLOW:
                items->insert(new Node<Item*>(new SlowItem(
                                                  position.first,
                                                  position.second,
                                                  characters
                                              )));
                break;

            case BOMB:
                items->insert(new Node<Item*>(new BombItem(
                                                  position.first,
                                                  position.second,
                                                  characters
                                              )));
                break;

            case TURN:
                items->insert(new Node<Item*>(new TurnItem(
                                                  position.first,
                                                  position.second,
                                                  characters
                                              )));
                break;
        }

        noChange = false;

        generateItem->resetTimer();
    }
}
void Game::checkPlayerMoving(){
    Player* player = reinterpret_cast<Player*>(characters->getFront()->data());
    std::pair<int, int> playerPosition = player->getPosition();

    switch(control->action(godMode)){
        case UP:
            if(distance->isInside(playerPosition.first, playerPosition.second - 1)){
                if(!player->checkCollide(playerPosition.first + 1, playerPosition.second, field)){
                    player->move(noChange, UP);
                    distance->calculate();
                }
            }
            break;

        case RIGHT:
            if(distance->isInside(playerPosition.first + 1, playerPosition.second)){
                if(!player->checkCollide(playerPosition.first + 2, playerPosition.second + 1, field)){
                    player->move(noChange, RIGHT);
                    distance->calculate();
                }
            }
            break;

        case DOWN:
            if(distance->isInside(playerPosition.first, playerPosition.second + 1)){
                if(!player->checkCollide(playerPosition.first + 1, playerPosition.second + 2, field)){
                    player->move(noChange, DOWN);
                    distance->calculate();
                }
            }
            break;

        case LEFT:
            if(distance->isInside(playerPosition.first - 1, playerPosition.second)){
                if(!player->checkCollide(playerPosition.first, playerPosition.second + 1, field)){
                    player->move(noChange, LEFT);
                    distance->calculate();
                }
            }
            break;

        default: break;
    }
}
void Game::checkPlayerCollectItem(){
    if(items->empty()) return;

    std::pair<int, int> playerPosition = characters->getFront()->data()->getPosition();
    Node<Item*>* currItem = items->getFront();

    for(int i = 0; i < items->size(); i++, currItem = currItem->next()){
        std::pair<int, int> itemPosition = currItem->data()->getPosition();

        if(itemPosition.first == playerPosition.first &&
           itemPosition.second == playerPosition.second){
            currItem->data()->effect();

            break;
        }
    }
}
void Game::checkMonsterMoving(){
    Node<Character*>* currMonsterNode = characters->getFront()->next();

    for(int i = 1; i < characters->size(); ++i, currMonsterNode = currMonsterNode->next()){
        Monster* monster = reinterpret_cast<Monster*>(currMonsterNode->data());
        std::pair<int, int> monsterPosition = monster->getPosition();
        int currDistance = 0;
        int direction = -1;

        if(monster->getMode()){
            int maxDistance = -1;

            // up
            if(distance->isInside(monsterPosition.first, monsterPosition.second - 1)){
                if(!monster->checkCollide(monsterPosition.first + 1, monsterPosition.second, field)){
                    currDistance = distance->getDistance(monsterPosition.first, monsterPosition.second - 1);

                    if(currDistance > maxDistance){
                        maxDistance = currDistance;
                        direction = UP;
                    }
                }
            }

            // right
            if(distance->isInside(monsterPosition.first + 1, monsterPosition.second)){
                if(!monster->checkCollide(monsterPosition.first + 2, monsterPosition.second + 1, field)){
                    currDistance = distance->getDistance(monsterPosition.first + 1, monsterPosition.second);

                    if(currDistance > maxDistance){
                        maxDistance = currDistance;
                        direction = RIGHT;
                    }
                }
            }

            // down
            if(distance->isInside(monsterPosition.first, monsterPosition.second + 1)){
                if(!monster->checkCollide(monsterPosition.first + 1, monsterPosition.second + 2, field)){
                    currDistance = distance->getDistance(monsterPosition.first, monsterPosition.second + 1);

                    if(currDistance > maxDistance){
                        maxDistance = currDistance;
                        direction = DOWN;
                    }
                }
            }

            // left
            if(distance->isInside(monsterPosition.first - 1, monsterPosition.second)){
                if(!monster->checkCollide(monsterPosition.first, monsterPosition.second + 1, field)){
                    currDistance = distance->getDistance(monsterPosition.first - 1, monsterPosition.second);

                    if(currDistance > maxDistance){
                        maxDistance = currDistance;
                        direction = LEFT;
                    }
                }
            }
        }
        else{
            int minDistance = FIELD_HEIGHT * FIELD_WIDTH;

            // up
            if(distance->isInside(monsterPosition.first, monsterPosition.second - 1)){
                if(!monster->checkCollide(monsterPosition.first + 1, monsterPosition.second, field)){
                    currDistance = distance->getDistance(monsterPosition.first, monsterPosition.second - 1);

                    if(currDistance < minDistance){
                        minDistance = currDistance;
                        direction = UP;
                    }
                }
            }

            // right
            if(distance->isInside(monsterPosition.first + 1, monsterPosition.second)){
                if(!monster->checkCollide(monsterPosition.first + 2, monsterPosition.second + 1, field)){
                    currDistance = distance->getDistance(monsterPosition.first + 1, monsterPosition.second);

                    if(currDistance < minDistance){
                        minDistance = currDistance;
                        direction = RIGHT;
                    }
                }
            }

            // down
            if(distance->isInside(monsterPosition.first, monsterPosition.second + 1)){
                if(!monster->checkCollide(monsterPosition.first + 1, monsterPosition.second + 2, field)){
                    currDistance = distance->getDistance(monsterPosition.first, monsterPosition.second + 1);

                    if(currDistance < minDistance){
                        minDistance = currDistance;
                        direction = DOWN;
                    }
                }
            }

            // left
            if(distance->isInside(monsterPosition.first - 1, monsterPosition.second)){
                if(!monster->checkCollide(monsterPosition.first, monsterPosition.second + 1, field)){
                    currDistance = distance->getDistance(monsterPosition.first - 1, monsterPosition.second);

                    if(currDistance < minDistance){
                        minDistance = currDistance;
                        direction = LEFT;
                    }
                }
            }
        }

        monster->move(noChange, direction);
    }
}
void Game::checkMonsterCaughtPlayer(){
    Node<Character*>* currMonsterNode = characters->getFront()->next();
    std::pair<int, int> playerPosition = characters->getFront()->data()->getPosition();

    for(int i = 1; i < characters->size(); i++, currMonsterNode = currMonsterNode->next()){
        std::pair<int, int> monsterPosition = currMonsterNode->data()->getPosition();

        if(playerPosition.first == monsterPosition.first &&
           playerPosition.second == monsterPosition.second){
            gameOver = true;

            break;
        }
    }
}
void Game::checkPlayerCaughtMonster(){
    Node<Character*>* currMonsterNode = characters->getFront()->next();
    std::pair<int, int> playerPosition = characters->getFront()->data()->getPosition();

    while(currMonsterNode != characters->getBack()){
        std::pair<int, int> monsterPosition = currMonsterNode->data()->getPosition();

        if(playerPosition.first == monsterPosition.first &&
           playerPosition.second == monsterPosition.second){
            currMonsterNode->data()->addScore(KILL_MONSTER);

            Node<Character*>* temp = currMonsterNode->next();

            currMonsterNode->pop_self();
            characters->setSize(characters->size() - 1);

            currMonsterNode = temp;
            noChange = false;
        }
        else{
            currMonsterNode = currMonsterNode->next();
        }
    }

    if(currMonsterNode == characters->getFront()) return;

    std::pair<int, int> monsterPosition = currMonsterNode->data()->getPosition();

    if(playerPosition.first == monsterPosition.first &&
       playerPosition.second == monsterPosition.second){
        currMonsterNode->data()->addScore(KILL_MONSTER);

        characters->setBack(currMonsterNode->prev());
        characters->getBack()->setNext(characters->getFront());
        characters->getFront()->setPrev(characters->getBack());

        currMonsterNode->pop_self();
        characters->setSize(characters->size() - 1);

        noChange = false;
    }
}
void Game::checkBuffExpired(){
    Node<Item*>* currItem = items->getFront();

    if(currItem == nullptr) return;

    for(; currItem != items->getBack(); currItem = currItem->next()){
        if(currItem->data()->isCollected()){
            if(currItem->data()->buffTimeExpired()){

                if(currItem == items->getFront()){
                    currItem->data()->buffLoseEffectiveness();
                    items->setFront(currItem->next());
                    currItem->pop_self();
                    items->getFront()->setPrev(items->getBack());
                    items->getBack()->setNext(items->getFront());
                    items->setSize(items->size() - 1);
                }
                else{
                    currItem->data()->buffLoseEffectiveness();
                    currItem->pop_self();
                    items->setSize(items->size() - 1);
                }
            }
        }
    }

    if(items->getBack()->data()->isCollected()){
        if(currItem->data()->buffTimeExpired()){
            if(items->size() == 1){
                items->getFront()->data()->buffLoseEffectiveness();
                items->getFront()->pop_self();
                items->setFront(nullptr);
                items->setBack(nullptr);
                items->setSize(0);
            }
            else{
                items->getBack()->data()->buffLoseEffectiveness();
                items->setBack(items->getBack()->prev());
                items->getBack()->next()->pop_self();
                items->getFront()->setPrev(items->getBack());
                items->getBack()->setNext(items->getFront());
                items->setSize(items->size() - 1);

            }
        }
    }
}
void Game::checkMonsterSkill(){
 	Node<Character*>* currMon = characters->getFront()->next();

	if(currMon == characters->getFront()) return;


	for(; currMon != characters->getBack(); currMon = currMon->next()){
		Monster* monster = reinterpret_cast <Monster*>(currMon->data());

		if(monster->Type() == '1'){//普通

		}
		else if(monster->Type() == '2'){//狂暴
			BerserkerMonster* Bmonster = reinterpret_cast <BerserkerMonster*>(monster);

            if(Bmonster->skill()){
                if(Bmonster->skillTimeExpird()){
                    Bmonster->actionLose();
                }
            }
            else{
                if(Bmonster->skillTimeExpird()){
                    Bmonster->action();
                }
            }
		}
		else if(monster->Type() == '3'){//匿蹤
			PhantomsMonster* Pmonster = reinterpret_cast <PhantomsMonster*>(monster);

            if(Pmonster->skill()){//呼叫 actionLose();
                if(Pmonster->skillTimeExpird()){
                    Pmonster->actionLose();
                }
            }
            else{
                if(Pmonster->skillTimeExpird()){
                    Pmonster->action();
                }
            }
		}
	}
	//////////////////////////
	if(currMon == characters->getBack()){
		Monster* monster = reinterpret_cast <Monster*>(characters->getBack()->data());

		if(monster->Type() == '1'){//普通

		}
		else if(monster->Type() == '2'){//狂暴
			BerserkerMonster* Bmonster = reinterpret_cast <BerserkerMonster*>(monster);

            if(Bmonster->skill()){
                if(Bmonster->skillTimeExpird()){//時間到
                    Bmonster->actionLose();
                }
            }
            else{
                if(Bmonster->skillTimeExpird()){//時間到

                    Bmonster->action();
                }
            }
		}
		else if(monster->Type() == '3'){//匿蹤
			PhantomsMonster* Pmonster = reinterpret_cast <PhantomsMonster*>(monster);

            if(Pmonster->skill()){//呼叫 actionLose();
                if(Pmonster->skillTimeExpird()){//時間到
                    Pmonster->actionLose();
                }
            }
            else{
                if(Pmonster->skillTimeExpird()){//時間到
                    Pmonster->action();
                }
            }
		}

	}
}
std::pair<int, int> Game::getRandomSpot(){
    int x = rand() % FIELD_WIDTH;
    int y = rand() % FIELD_HEIGHT;

    while(field->getMatrix(x + 1, y + 1) != ' '){
        x = rand() % FIELD_WIDTH;
    }

    return {x, y};
}

UserInterface::UserInterface(){

}
UserInterface::~UserInterface(){

}
int UserInterface::action(bool& godMode){
    if(kbhit()){
        int key = getch();

        if(key == 224){
            key = getch();

            switch(key){
                // for movement
                case 72: return UP;
                case 75: return LEFT;
                case 80: return DOWN;
                case 77: return RIGHT;
            }
        }
        else{
            switch(key){
                // for movements
                case 'W': case 'w': return UP;
                case 'A': case 'a': return LEFT;
                case 'S': case 's': return DOWN;
                case 'D': case 'd': return RIGHT;

                // for functions
                case 'T': case 't':
                    if(godMode){
                        godMode = false;

                        Game::printStatus("God mode off");
                    }
                    else{
                        godMode = true;

                        Game::printStatus("God mode on");
                    }

                    return DEFAULT;
            }
        }
    }

    return -1;
}

Item::Item(int x, int y, char type, double timeGap, List<Character*>* characters)
    : position({x, y}), type(type), characters(characters){
    duration = new Timer(timeGap);
    _isCollected_ = false;
}
Item::~Item(){
    delete duration;
}
void Item::print(){
    if(_isCollected_) return;

    gotoxy(position.first + 1, position.second + 1);
    hideCursor();
    std::cout<< type;
}
bool Item::isCollected(){
    return _isCollected_;
}
bool Item::buffTimeExpired(){
    return duration->exceedTimeGap();
}
char Item::getType(){
    return type;
}
std::pair<int, int> Item::getPosition(){
    return position;
}

FastItem::FastItem(int x, int y, List<Character*>* characters)
    : Item(x, y, 'F', FAST_DURATION, characters){

}
FastItem::~FastItem(){

}
void FastItem::effect(){
    Player* player = reinterpret_cast<Player*>(characters->getFront()->data());

    player->setSpeed(PLAYER_SPEED / 2);

    _isCollected_ = true;
    duration->resetTimer();

    Game::printStatus("Player collected a FastItem");
}
void FastItem::buffLoseEffectiveness(){
    Player* player = reinterpret_cast<Player*>(characters->getFront()->data());

    player->setDefaultSpeed();

    Game::printStatus("FastItem lose effectiveness");
}

SlowItem::SlowItem(int x, int y, List<Character*>* characters)
    : Item(x, y, 'S', SLOW_DURATION, characters){

}
SlowItem::~SlowItem(){

}
void SlowItem::effect(){
    Node<Character*>* currMonster = characters->getFront()->next();

    for(int i = 1; i < characters->size(); i++, currMonster = currMonster->next()){
        currMonster->data()->setSpeed(MONSTER_SPEED * 2);
    }

    _isCollected_ = true;
    duration->resetTimer();

    Game::printStatus("Player collected a SlowItem");
}
void SlowItem::buffLoseEffectiveness(){
    Node<Character*>* currMonster = characters->getFront()->next();

    for(int i = 1; i < characters->size(); i++, currMonster = currMonster->next()){
        currMonster->data()->setDefaultSpeed();
    }

    Game::printStatus("SlowItem lose effectiveness");
}

BombItem::BombItem(int x, int y, List<Character*>* characters)
    : Item(x, y, 'B', BOMB_DURATION, characters){

}
BombItem::~BombItem(){

}
void BombItem::effect(){
    while(characters->size() != 1){
        characters->getFront()->next()->pop_self();
        characters->setSize(characters->size() - 1);
        characters->getFront()->data()->addScore(KILL_MONSTER);
    }

    characters->setBack(characters->getFront());
    characters->getFront()->setNext(characters->getBack());
    characters->getFront()->setPrev(characters->getFront());

    _isCollected_ = true;
    duration->resetTimer();

    Game::printStatus("Player collected a BombItem");
}
void BombItem::buffLoseEffectiveness(){

}

TurnItem::TurnItem(int x, int y, List<Character*>* characters)
    : Item(x, y, 'T', TURN_DURATION, characters){

}
TurnItem::~TurnItem(){

}
void TurnItem::effect(){
    characters->getFront()->data()->changeMode(true);

    _isCollected_ = true;
    duration->resetTimer();

    Game::printStatus("Player collected a TurnItem");
}
void TurnItem::buffLoseEffectiveness(){
    characters->getFront()->data()->changeMode(false);

    Game::printStatus("TurnItem lose effectiveness");
}

Monster::Monster(int x, int y, char type, int* score)
    : Character(x, y, type, MONSTER_SPEED, score){
	_skill_ = false;
}
Monster::~Monster(){

}
void Monster::action(){

}
void Monster::actionLose(){

}
void Monster::setDefaultSpeed(){
    setSpeed(MONSTER_SPEED);
}
bool Monster::checkCatchPlayer(int x, int y){
    return (position.first == x && position.second == y);
}

RegularMonster::RegularMonster(int x, int y, int* score): Monster(x, y, '1', score){

}
RegularMonster::~RegularMonster(){

}
void RegularMonster::action(){

}
void RegularMonster::actionLose(){

}

BerserkerMonster::BerserkerMonster(int x, int y, int* score): Monster(x, y, '2', score){
	skillCountDown->setTimeGap(BERSERKER_COUNT_DOWN);
	skillCountDown->resetTimer();
}
BerserkerMonster::~BerserkerMonster(){

}
void BerserkerMonster::action(){
	setSpeed(MONSTER_SPEED / 2);

	skillCountDown->setTimeGap(BERSERKER_DURATION);
	skillCountDown->resetTimer();

	_skill_ = true;

	Game::printStatus("Berserker using skill");
}
void BerserkerMonster::actionLose(){
	setDefaultSpeed();

	skillCountDown->setTimeGap(BERSERKER_COUNT_DOWN);
	skillCountDown->resetTimer();

	_skill_ = false;

	Game::printStatus("Berserker's skill duration expired");
}

PhantomsMonster::PhantomsMonster(int x, int y, int* score): Monster(x, y, '3', score){
	skillCountDown->setTimeGap(PHANTOMS_COUNT_DOWN);
	skillCountDown->resetTimer();
}
PhantomsMonster::~PhantomsMonster(){

}
void PhantomsMonster::action(){
	SetcharacterPrint(false);

	skillCountDown->setTimeGap(PHANTOMS_DURATION);
	skillCountDown->resetTimer();

	_skill_ = true;

	Game::printStatus("Phantoms using skill");
}
void PhantomsMonster::actionLose(){
	SetcharacterPrint(true);

	skillCountDown->setTimeGap(PHANTOMS_COUNT_DOWN);
	skillCountDown->resetTimer();

	_skill_ = false;

	Game::printStatus("Phantoms' skill duration expired");
}

Player::Player(int x, int y, int* score): Character(x, y, 'P', PLAYER_SPEED, score){

}
Player::~Player(){

}
void Player::action(){
    // no skill
}
void Player::actionLose(){
    // no skill
}
void Player::setDefaultSpeed(){
    setSpeed(PLAYER_SPEED);
}

Character::Character(int x, int y, char name, double speed, int* score){
    this->name = name;
    this->speed = speed;
    this->score = score;
    position.first = x;
    position.second = y;
    canMove = true;
    _skill_ = false;
    _characterPrint_ = true;
    timer = new Timer(speed);
    skillCountDown = new Timer(speed);
}
Character::~Character(){
    delete timer;
    delete skillCountDown;
}
void Character::move(bool& noChange, int direction /* = -1 */){
    if(timer->exceedTimeGap()){
        canMove = true;
    }
    if(canMove){
        switch(direction){
            case UP:
                position = {position.first, position.second - 1};
                break;

            case RIGHT:
                position = {position.first + 1, position.second};
                break;

            case DOWN:
                position = {position.first, position.second + 1};
                break;

            case LEFT:
                position = {position.first - 1, position.second};
                break;

            default: break;
        }

        if(direction != -1){
            canMove = false;
            noChange = false;

            timer->resetTimer();
        }
    }
}
void Character::print(){
    gotoxy(position.first + 1, position.second + 1);
    std::cout<< name;
    hideCursor();
}
bool Character::checkCollide(int x, int y, Field* field){
    return (field->getMatrix(x, y) == '#') || (field->getMatrix(x, y) == '*');
}
char Character::Type(){
	return name;
}
bool Character::skillTimeExpird(){
    return skillCountDown->exceedTimeGap();
}
bool Character::skill(){
    return _skill_;
}
bool Character::characterPrint(){
	return _characterPrint_;
}
std::pair<int, int> Character::getPosition(){
    return position;
}
void Character::addScore(int num){
    *score += num;
}
void Character::setSpeed(double speed){
    this->speed = speed;

    timer->setTimeGap(speed);
}
void Character::changeMode(bool status){
    turnItemCollected = status;
}
void Character::SetcharacterPrint(bool status){
	_characterPrint_ = status;
}
bool Character::getMode(){
    return turnItemCollected;
}
double Character::getSpeed(){
    return speed;
}

Distance::Distance(Player* player, Field* field): player(player), field(field){

}
Distance::~Distance(){

}
int Distance::getDistance(int x, int y){
    return distance[y][x];
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
    bool check[FIELD_HEIGHT][FIELD_WIDTH];

    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            check[i][j] = false;
            distance[i][j] = 99; //INT_MAX;
        }
    }

    std::queue<std::pair<int, int>> que;
    std::pair<int, int> playerPosition = player->getPosition();

    que.push(playerPosition);

    distance[playerPosition.second][playerPosition.first] = 0;
    check[playerPosition.second][playerPosition.first] = true;

    while(!que.empty()){
        int x = que.front().first;
        int y = que.front().second;
        int currDistance = distance[y][x];

        que.pop();

        // up
        if(isInside(x, y - 1)){
            if(!check[y - 1][x]){
                if((field->getMatrix(x + 1, y) != '#') &&
                   (field->getMatrix(x + 1, y) != '*')){
                    check[y - 1][x] = true;
                    distance[y - 1][x] = currDistance + 1;

                    que.push({x, y - 1});
                }
            }
        }

        // right
        if(isInside(x + 1, y)){
            if(!check[y][x + 1]){
                if((field->getMatrix(x + 2, y + 1) != '#') &&
                   (field->getMatrix(x + 2, y + 1) != '*')){
                    check[y][x + 1] = true;
                    distance[y][x + 1] = currDistance + 1;

                    que.push({x + 1, y});
                }
            }
        }

        // down
        if(isInside(x, y + 1)){
            if(!check[y + 1][x]){
                if((field->getMatrix(x + 1, y + 2) != '#') &&
                   (field->getMatrix(x + 1, y + 2) != '*')){
                    check[y + 1][x] = true;
                    distance[y + 1][x] = currDistance + 1;

                    que.push({x, y + 1});
                }
            }
        }

        // left
        if(isInside(x - 1, y)){
            if(!check[y][x - 1]){
                if((field->getMatrix(x, y + 1) != '#') &&
                   (field->getMatrix(x, y + 1) != '*')){
                    check[y][x - 1] = true;
                    distance[y][x - 1] = currDistance + 1;

                    que.push({x - 1, y});
                }
            }
        }
    }
}
void Distance::print(){
    gotoxy(0, FIELD_HEIGHT + 7);
    std::cout<< "distance to player:\n";

    for(int i = 0 ; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            printf("%2d ", distance[i][j]);
        }

        std::cout<< '\n';
    }
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
    for(int times = rand() % (OBSTACLE_COUNT_MAX - OBSTACLE_COUNT_MIN + 1) + OBSTACLE_COUNT_MIN; times > 0; --times){
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

Obstacle::Obstacle(int x, int y, int width, int height): size({width, height}), position({x, y}){

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
void Node<Type>::pop_self(){
    _prev_->setNext(_next_);
    _next_->setPrev(_prev_);

    delete this;
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
void List<Type>::setFront(Node<Type>* front){
    this->front = front;
}
template <typename Type>
void List<Type>::setBack(Node<Type>* back){
    this->back = back;
}
template <typename Type>
void List<Type>::setSize(int size){
    nodeCount = size;
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
