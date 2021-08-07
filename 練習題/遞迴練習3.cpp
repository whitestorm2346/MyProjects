#include <iostream>
#include <string>

bool IsPalindrome(std::string str_Input)
{
    if(str_Input.size() == 1 || str_Input[0] != str_Input[str_Input.size() - 1]) return false;

    return (str_Input.size() == 2) ? true : IsPalindrome(str_Input.substr(1, str_Input.size() - 2));
}

int main()
{
    std::string str_Input;

    std::cin>> str_Input;
    std::cout<< IsPalindrome(str_Input);

    return 0;
}


