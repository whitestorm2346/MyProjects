#include <iostream>
#include <string>

int main()
{
    std::string str_ID;
    bool bl_Check = true;

    std::cin>> str_ID;

    if(str_ID.length() != 10)
    {
        std::cout<< "The length of input is not equal to 10.\n";

        bl_Check = false;
    }

    if(str_ID[0] >= 'a' && str_ID[0] <= 'z') str_ID[0] -= 32;

    if(str_ID[0] < 'A' || str_ID[0] > 'Z')
    {
        std::cout<< "The first term of string is not an alphabet.\n";

        bl_Check = false;
    }

    for(int i = 1; i < 10; i++)
    {
        if(str_ID[i] < '0' || str_ID[i] > '9')
        {
            std::cout<< "The second to 10th terms should be numeric terms.\n";

            bl_Check = false;

            break;
        }
    }

    if(str_ID[1] >= '3')
    {
        std::cout<< "The number of gender should be equal to 1 or 2.\n";

        bl_Check = false;
    }

    if(bl_Check)
    {
        int int_Letter = str_ID[0] - 'A' + 10;
        int int_Sum = 0;

        if(int_Letter == 18) int_Letter = 34;
        else if(int_Letter == 24) int_Letter = 35;
        else if(18 < int_Letter && int_Letter < 24) int_Letter--;
        else if((24 < int_Letter && int_Letter < 32) || int_Letter == 35) int_Letter -= 2;
        else if(32 < int_Letter && int_Letter < 35) int_Letter -= 3;

        int_Sum += int_Letter / 10 + (int_Letter % 10) * 9;

        for(int i = 1; i < 9; i++)
        {
            int_Sum += (str_ID[i] - '0') * (9 - i);
        }

        int_Sum += str_ID[9] - '0';

        if(int_Sum % 10 == 0) std::cout<< "ID is legal.\n";
        else std::cout<< "ID is illegal.\n";
    }

    return 0;
}
