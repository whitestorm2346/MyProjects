#include <iostream>
#include <string>

int main()
{
    std::string str_Input;

    while(getline(std::cin, str_Input, '\n'))
    {
        int intarr_Letter[26] = {};

        for(int i = 0; i < str_Input.length(); i++)
        {
            if(str_Input[i] >= 97 && str_Input[i] <= 122)
            {
                intarr_Letter[static_cast<int>(str_Input[i]) - 97]++;
            }
        }

        for(int i = 0; i < 26; i++)
        {
            if(intarr_Letter[i] != 0)
            {
                std::cout<< static_cast<char>(i + 97) << ": "
                         << intarr_Letter[i] << '\n';
            }
        }
    }

    return 0;
}
