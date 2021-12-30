#ifndef FUNCTION_HPP_INCLUDED
#define FUNCTION_HPP_INCLUDED

#include <windows.h>
#include <cstdlib>
#include <ctime>

const int regularWidth = 31;
const int regularHeight = 4;

void gotoXY(short int x, short int y)
{
    COORD pos = {x, y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(hOut, pos);
}
void cleanBoard(int rowSize = regularWidth, int colSize = regularHeight)
{
    gotoXY(0, 1);

    for(int i = 0; i < colSize; i++)
    {
        for(int j = 0; j < rowSize; j++)
        {
            std::cout<< ' ';
        }

        std::cout<< '\n';
    }

    gotoXY(0, 1);
}
void RandomSeat(int* Seat, int size)
{
    srand(time(nullptr));

    for(int i = 0; i < size; i++)
    {
        int randIdx = rand() % size;

        std::swap(Seat[i], Seat[randIdx]);
    }
}

#endif // FUNCTION_HPP_INCLUDED
