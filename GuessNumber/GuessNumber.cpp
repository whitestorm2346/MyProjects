#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));

    int int_Answer = rand() % 101, int_Input;
    int int_Left = 0, int_Right = 100;
    bool bl_HumanFirst = rand() % 2;

    std::cout<< "Guess the number(0~100)\n\n";

    do
    {
        if(bl_HumanFirst)
        {
            std::cout<< "Your turn:\n";
            std::cout<< "Guess: ";
            std::cin>> int_Input;

            if(int_Input > int_Answer)
            {
                std::cout<< "This number is bigger than answer.\n\n";

                int_Right = int_Input - 1;
            }
            else if(int_Input < int_Answer)
            {
                std::cout<< "This number is smaller than answer.\n\n";

                int_Left = int_Input + 1;
            }
            else std::cout<< "You Win!!\n\n";
        }
        else
        {
            std::cout<< "Computer\'s turn:\n";
            std::cout<< "Guess: ";

            int_Input = rand() % (int_Right - int_Left + 1) + int_Left;

            std::cout<< int_Input << '\n';

            if(int_Input > int_Answer)
            {
                std::cout<< "This number is bigger than answer.\n\n";

                int_Right = int_Input - 1;
            }
            else if(int_Input < int_Answer)
            {
                std::cout<< "This number is smaller than answer.\n\n";

                int_Left = int_Input + 1;
            }
            else std::cout<< "Computer Win!!\n\n";
        }

        bl_HumanFirst = !bl_HumanFirst;
    }
    while(int_Input != int_Answer);

    system("pause");

    return 0;
}
