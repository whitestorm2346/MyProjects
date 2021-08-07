#include <iostream>
#include <cmath>

bool IsPrimeNumber(int int_Num)
{
    for(int i = 2; i <= std::sqrt(int_Num); i++)
    {
        if(int_Num % i == 0) return false;
    }

    return true;
}

int PrimeNumberCount(int int_Num)
{
    if(int_Num == 2) return 1;

    if(IsPrimeNumber(int_Num)) return 1 + PrimeNumberCount(int_Num - 1);
    else PrimeNumberCount(int_Num - 1);
}

int main()
{
    int int_Num;

    std::cin>> int_Num;
    std::cout<< PrimeNumberCount(int_Num);

    return 0;
}


