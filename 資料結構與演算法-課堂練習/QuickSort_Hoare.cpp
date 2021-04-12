#include <iostream>

int main()
{
    int int_Var = 18;

    (--int_Var)%=(--int_Var)++;

    std::cout<< int_Var;

    return 0;
}



