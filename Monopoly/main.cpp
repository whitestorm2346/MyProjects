#include <iostream>
#include "Functions.h"
#include "LinkedList.h"

void fn_Intro();

int main()
{
    fn_SetOutputPos(0, 0);
    fn_Intro();

    std::dll<int> dll_Num;

    return 0;
}

void fn_Intro()
{
    fn_Line();

    std::cout<< "\n\n                     ";

    fn_SetColor(BRIGHT_WHITE, FOREGROUND);

    std::cout<<"MONOPOLY\n\n";
    std::cout<< "\n         < Press Keyboard To Start Game >\n\n";

    fn_Line();

    return;
}
