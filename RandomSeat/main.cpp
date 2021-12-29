#include <iostream>
#include <conio.h>
#include "function.hpp"

int main()
{
    srand(time(nullptr));

    const int titleHeight = 5;
    int bodyHeight = 5;

    printLine(50);
    printLine(50, ' ');
    printLine(20, ' ', false);

    std::cout<< "Random Seat\n";

    printLine(50, ' ');
    printLine(50);
    printLine(50, ' ');

    std::cout<< "Press \"enter\" to start...\n";

    printLine(50, ' ');
    printLine(50); // gotoXY(0, 5);

    for(int input = 0; input != 13; input = getch())
    {
        gotoXY(25, 6);
    }




    gotoXY(0, titleHeight + bodyHeight);

    return 0;
}

