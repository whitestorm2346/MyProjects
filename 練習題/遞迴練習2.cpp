#include <iostream>

int Factorial(int int_Num)
{
    if(int_Num == 0 || int_Num == 1) return 1;
    else return int_Num * Factorial(int_Num - 1);
}

int main()
{
    int int_Num;

    std::cin>> int_Num;
    std::cout<< Factorial(int_Num);

    return 0;
}


