#include <iostream>

int intarr_Area[100] = {};
int intarr_Direction[8] = {1, 2, 3, 3, 4, 4, 1, 1};

bool  fn_CheckInArea(int int_Num1, int int_Num2);
void  fn_SetNum(int int_Num);
void  fn_Output();

int main()
{
    int int_Input;

    for(int i = 0; i < 10; i++)
    {
        std::cin>> int_Input;

        fn_SetNum(int_Input);
    }

    fn_Output();

    return 0;
}

bool  fn_CheckInArea(int int_NowX, int int_NowY)
{
    return (int_NowX >= 0 && int_NowX < 10) && (int_NowY >= 0 && int_NowY < 10);
}

void  fn_SetNum(int int_Num)
{
    int int_NowX = int_Num % 10;
    int int_NowY = int_Num / 10;

    intarr_Area[int_Num] = -1;

    for(int i = 0; i < 8; i++)
    {
        switch(intarr_Direction[i])
        {
            case 1:
                if(fn_CheckInArea(int_NowX, --int_NowY))
                {
                    if(intarr_Area[int_NowY * 10 + int_NowX] != -1)
                       intarr_Area[int_NowY * 10 + int_NowX]++;
                }

                break;

            case 2:
                if(fn_CheckInArea(++int_NowX, int_NowY))
                {
                    if(intarr_Area[int_NowY * 10 + int_NowX] != -1)
                       intarr_Area[int_NowY * 10 + int_NowX]++;
                }

                break;

            case 3:
                if(fn_CheckInArea(int_NowX, ++int_NowY))
                {
                    if(intarr_Area[int_NowY * 10 + int_NowX] != -1)
                       intarr_Area[int_NowY * 10 + int_NowX]++;
                }

                break;

            case 4:
                if(fn_CheckInArea(--int_NowX, int_NowY))
                {
                    if(intarr_Area[int_NowY * 10 + int_NowX] != -1)
                       intarr_Area[int_NowY * 10 + int_NowX]++;
                }
        }
    }

    return;
}

void  fn_Output()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            switch(intarr_Area[i * 10 + j])
            {
                case -1: std::cout<< '*'; break;
                case  0: std::cout<< ' '; break;
                default: std::cout<< intarr_Area[i * 10 + j];
            }
        }

        std::cout<< '\n';
    }

    return;
}
