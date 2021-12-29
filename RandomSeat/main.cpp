#include <iostream>
#include <conio.h>
#include <string>
#include "function.hpp"

int main()
{
    const int titleHeight = 2;
    int bodyHeight = 5;

    std::cout<< "========= Random Seat =========\n\n";
    std::cout<< "Press any key to continue...\n\n";

    for(int input = 0; input != 13; )
    {
        gotoXY(28, 2);

        input = getch();
    }

    gotoXY(0, 2);

    std::cout<< "                                 \r";

    int rowCount = 0, colCount = 0;

    for(; rowCount <= 0 || rowCount > 20;)
    {
        gotoXY(0, 2);

        std::cout<< "set row count(1~20):    \b\b\b";
        std::cin>> rowCount;
    }

    for(; colCount <= 0 || colCount > 20;)
    {
        gotoXY(0, 3);

        std::cout<< "set column count(1~20):    \b\b\b";
        std::cin>> colCount;
    }

    cleanBoard();

    std::cout<< '\n';

    int size = rowCount * colCount;
    int* Seat = new int[size];

    bodyHeight = colCount * 2;

    for(int i = 0; i < size; i++)
    {
        Seat[i] = i + 1;
    }

    RandomSeat(Seat, size);

    for(int i = 0; i < colCount; i++)
    {
        for(int j = 0; j < rowCount; j++)
        {
            if(size < 10) printf(" %0d", *(Seat + i * rowCount + j));
            else if(size < 100) printf(" %02d", *(Seat + i * rowCount + j));
            else printf(" %03d", *(Seat + i * rowCount + j));
        }

        std::cout<< "\n\n";
    }

    delete [] Seat;

    gotoXY(0, titleHeight + bodyHeight);

    return 0;
}

