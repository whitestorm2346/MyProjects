#include <iostream>
#include <string>
#include <stack>

int main()
{
    std::stack<char> stk_Char;
    std::string str_Input;
    bool bl_Illegal = false;

    std::cin>> str_Input;

    for(int i = 0; i < str_Input.length(); i++)
    {
        if(str_Input[i] == '(' ||
           str_Input[i] == '[' ||
           str_Input[i] == '{')
        {
            stk_Char.push(str_Input[i]);
        }
        else
        {
            switch(str_Input[i])
            {
                case ')':
                    if(stk_Char.top() == '(') stk_Char.pop();
                    else bl_Illegal = true;
                    break;

                case ']':
                    if(stk_Char.top() == ']') stk_Char.pop();
                    else bl_Illegal = true;
                    break;

                case '}':
                    if(stk_Char.top() == '}') stk_Char.pop();
                    else bl_Illegal = true;
                    break;
            }
        }
    }

    if(bl_Illegal) std::cout<< "True\n";
    else std::cout<< "False\n";

    return 0;
}
