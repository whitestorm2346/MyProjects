#include <iostream>

void fn_CutGold(int* intarr_Price, int int_Curr);

int main()
{
    int int_Gold, int_Length;

    std::cin>> int_Gold;

    if(int_Gold < 8) int_Length = 9;
    else int_Length = int_Gold + 1;

    int intarr_Price[int_Length] = {0, 2, 5, 9, 10, 15, 16, 19, 26};

    fn_CutGold(intarr_Price, int_Gold);

    std::cout<< intarr_Price[int_Gold] << '\n';

    return 0;
}

void fn_CutGold(int* intarr_Price, int int_Curr)
{
    for(int i = 2; i <= int_Curr; i++)
    {
        int int_Max = -1;

        for(int j = i; j >= int_Curr / 2; j--)
        {
            int int_Temp = intarr_Price[i - j] + intarr_Price[j];

            if(int_Temp > int_Max) int_Max = int_Temp;
        }

        intarr_Price[int_Curr] = int_Max;
    }
}
