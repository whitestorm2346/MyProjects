#include <iostream>
#include <conio.h>
#include <string>
#include "function.hpp"

int main()
{
    const int titleHeight = 2;
    int bodyHeight = 5, bodyWidth = 30, option;

    std::cout<< "========= Random Seat =========\n\n";
    std::cout<< "Press any key to continue...\n\n";

    for(int input = 0; input != 13; )
    {
        gotoXY(28, 2);

        input = getch();
    }

    gotoXY(0, 2);

    do
    {
        cleanBoard(bodyWidth, bodyHeight + 5);

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

        int size = rowCount * colCount;
        int* Seat = new int[size];

        bodyHeight = colCount * 2;
        bodyWidth = (rowCount * 4 < 25) ? 25 : (rowCount * 4);

        for(int i = 0; i < size; i++)
        {
            Seat[i] = i + 1;
        }

        do
        {
            cleanBoard();

            std::cout<< '\n';

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



            for(option = 0; option < 1 || option > 3;)
            {
                gotoXY(0, titleHeight + bodyHeight);

                std::cout<< "(1) Reset rows & columns\n";
                std::cout<< "(2) New random seat\n";
                std::cout<< "(3) End the program\n";
                std::cout<< "choise:     \b\b\b\b";
                std::cin>> option;
            }
        }
        while(option == 2);

        delete [] Seat;
    }
    while(option == 1);

    cleanBoard(bodyWidth, bodyHeight + 5);

    std::cout<< "\n             E N D\n\n";
    std::cout<< "===============================\n";

    return 0;
}

