#include <iostream>
#include <string>

int main()
{
    std::string str_Answer;
    int intarr_Ans[10] = {};
    int int_TestCount;
    bool bl_RightAns = false;
    bool bl_IsRepeat = false;

    std::cin>> str_Answer >> int_TestCount;

    for(unsigned int i = 0; i < str_Answer.length(); i++)
    {
        if(++intarr_Ans[str_Answer[i] - '0'] > 1)
        {
            bl_IsRepeat = true;
            break;
        }
    }

    if(bl_IsRepeat) std::cout<< "Error, number repeated.\n";
    else
    {
        for(int i = 0; i < int_TestCount; i++)
        {
            std::string str_Guess;
            int int_A = 0, int_B = 0;
            int intarr_Guess[10] = {};

            for(int j = 0; j < 10; j++)
            {
                intarr_Ans[j] = 0;
            }

            std::cout<< "Guess Number:";
            std::cin>> str_Guess;

            if(str_Answer.length() != str_Guess.length())
            {
                std::cout<< "Length difference!\n";
                break;
            }

            for(unsigned int j = 0; j < str_Answer.length(); j++)
            {
                if(str_Answer[j] == str_Guess[j]) int_A++;
                else
                {
                    intarr_Ans[str_Answer[j] - '0']++;

                    if(++intarr_Guess[str_Guess[j] - '0'] > 1)
                    {
                        bl_IsRepeat = true;
                        break;
                    }
                }
            }

            if(bl_IsRepeat)
            {
                std::cout<< "Error, number repeated.\n";
                break;
            }

            for(int j = 1; j < 10; j++)
            {
                int_B += (intarr_Ans[j] < intarr_Guess[j]) ? intarr_Ans[j] : intarr_Guess[j];
            }

            std::cout<< "Message:" << int_A << 'A' << int_B << "B\n";

            if(int_A == 4)
            {
                bl_RightAns = true;

                std::cout<< "You are right!\n";

                break;
            }
        }

        if(!bl_RightAns && !bl_IsRepeat) std::cout<< "You do not guess the right number!\n";
    }


    return 0;
}


