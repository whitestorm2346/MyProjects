#ifndef OUTPUTCONTROL_HPP_INCLUDED
#define OUTPUTCONTROL_HPP_INCLUDED

#include <windows.h>

void gotoxy(int x, int y)
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

void setFontColor(int color)
{

}

void setBackgroundColor(int color)
{

}

#endif // OUTPUTCONTROL_HPP_INCLUDED
