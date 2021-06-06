#include <windows.h>
#include <conio.h>

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#define BLACK  0
#define BLUE   1
#define GREEN  2
#define AQUA   3
#define RED    4
#define PURPLE 5
#define YELLOW 6
#define WHITE  7
#define GRAY   8
#define LIGHT_BLUE   9
#define LIGHT_GREEN  10
#define LIGHT_AQUA   11
#define LIGHT_RED    12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

#define FOREGROUND true
#define BACKGROUND false

HANDLE hdl_Console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD  cor_Pos = {0, 0};

void fn_SetOutputPos(int int_X, int int_Y)
{
    cor_Pos.X = int_X;
    cor_Pos.Y = int_Y;

    SetConsoleCursorPosition(hdl_Console, cor_Pos);
}

void fn_Line()
{
    for(int i = 0; i < 50; i++) std::cout<< '=';

    std::cout<< '\n';
}

void fn_SetColor(int int_Color, bool bl_Fore)
{
    if(bl_Fore)
    {
        switch(int_Color)
        {
            case  0: SetConsoleTextAttribute(hdl_Console, NULL); break;
            case  1: SetConsoleTextAttribute(hdl_Console, FOREGROUND_BLUE); break;
            case  2: SetConsoleTextAttribute(hdl_Console, FOREGROUND_GREEN); break;
            case  3: SetConsoleTextAttribute(hdl_Console, FOREGROUND_BLUE | FOREGROUND_GREEN); break;
            case  4: SetConsoleTextAttribute(hdl_Console, FOREGROUND_RED); break;
            case  5: SetConsoleTextAttribute(hdl_Console, FOREGROUND_RED | FOREGROUND_BLUE); break;
            case  6: SetConsoleTextAttribute(hdl_Console, FOREGROUND_RED | FOREGROUND_GREEN); break;
            case  7: SetConsoleTextAttribute(hdl_Console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
            case  8: SetConsoleTextAttribute(hdl_Console, FOREGROUND_INTENSITY); break;
            case  9: SetConsoleTextAttribute(hdl_Console, FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
            case 10: SetConsoleTextAttribute(hdl_Console, FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
            case 11: SetConsoleTextAttribute(hdl_Console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
            case 12: SetConsoleTextAttribute(hdl_Console, FOREGROUND_RED | FOREGROUND_INTENSITY); break;
            case 13: SetConsoleTextAttribute(hdl_Console, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
            case 14: SetConsoleTextAttribute(hdl_Console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
            case 15: SetConsoleTextAttribute(hdl_Console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
        }
    }
    else
    {
        switch(int_Color)
        {
            case  1: SetConsoleTextAttribute(hdl_Console, BACKGROUND_BLUE); break;
            case  2: SetConsoleTextAttribute(hdl_Console, BACKGROUND_GREEN); break;
            case  3: SetConsoleTextAttribute(hdl_Console, BACKGROUND_BLUE | BACKGROUND_GREEN); break;
            case  4: SetConsoleTextAttribute(hdl_Console, BACKGROUND_RED); break;
            case  5: SetConsoleTextAttribute(hdl_Console, BACKGROUND_RED | BACKGROUND_BLUE); break;
            case  6: SetConsoleTextAttribute(hdl_Console, BACKGROUND_RED | BACKGROUND_GREEN); break;
            case  7: SetConsoleTextAttribute(hdl_Console, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE); break;
            case  8: SetConsoleTextAttribute(hdl_Console, BACKGROUND_INTENSITY); break;
            case  9: SetConsoleTextAttribute(hdl_Console, BACKGROUND_BLUE | BACKGROUND_INTENSITY); break;
            case 10: SetConsoleTextAttribute(hdl_Console, BACKGROUND_GREEN | BACKGROUND_INTENSITY); break;
            case 11: SetConsoleTextAttribute(hdl_Console, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY); break;
            case 12: SetConsoleTextAttribute(hdl_Console, BACKGROUND_RED | BACKGROUND_INTENSITY); break;
            case 13: SetConsoleTextAttribute(hdl_Console, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY); break;
            case 14: SetConsoleTextAttribute(hdl_Console, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY); break;
            case 15: SetConsoleTextAttribute(hdl_Console, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY); break;
        }
    }
}

#endif // FUNCTIONS_H_INCLUDED
