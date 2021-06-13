#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

//  0: air
// -1: obstacle
// -2: nail
//  1: score point
//  2: pinball

int int2arr_Board[13][11] = {
    {-1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
    {-1, -2,  0, -2,  0, -2,  0, -2,  0, -2, -1},
    {-1,  0, -2,  0, -2,  0, -2,  0, -2,  0, -1},
    {-1, -2,  0, -2,  0, -2,  0, -2,  0, -2, -1},
    {-1,  0, -2,  0, -2,  0, -2,  0, -2,  0, -1},
    {-1, -2,  0, -2,  0, -2,  0, -2,  0, -2, -1},
    {-1,  0, -2,  0, -2,  0, -2,  0, -2,  0, -1},
    {-1, -2,  0, -2,  0, -2,  0, -2,  0, -2, -1},
    {-1,  0, -2,  0, -2,  0, -2,  0, -2,  0, -1},
    {-1, -2,  0, -2,  0, -2,  0, -2,  0, -2, -1},
    {-1,  0, -2,  0, -2,  0, -2,  0, -2,  0, -1},
    {-1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1},
    {-1,  0, -1,  0, -1,  0, -1,  0, -1,  0, -1}
};

int int_NowX, int_NowY;

void  fn_Line();
void  fn_Delay(int int_Time);
void  fn_RorL(int int_Direction);
void  fn_Fall();
void  fn_SetScorePoint(int* intptr_ScorePointX, int int_Size);
void  fn_Display();
void  fn_ResetLastLine();

int main()
{
    srand(time(NULL));

    int int_PinballCount = 5;
    bool bl_KeepPlaying;

    do
    {
        int int_PutBall, int_RandPoint = rand() % 3 + 1;
        int intarr_ScorePoint[int_RandPoint];
        int intarr_CheckNum[5] = {};
        int* intptr_ScorePointX = intarr_ScorePoint;

        int_NowY = 0;
        int_NowX = rand() % 9 + 1;
        int2arr_Board[0][int_NowX] = 2;
        fn_ResetLastLine();
        fn_Line();

        std::cout<< "\n彈珠數: " << int_PinballCount << "\n\n"
                 << "要放入的彈珠數:";

        while(true)
        {
            std::cin>> int_PutBall;

            if(int_PutBall <= 0)
            {
                std::cout<< "\n[系統] 輸入格式不符，請再次輸入!\n";
            }
            else if(int_PutBall > int_PinballCount)
            {
                std::cout<< "\n[系統] 彈珠數不足，請再次輸入!\n";
            }
            else break;
        }

        int_PinballCount -= int_PutBall;

        for(int i = 0; i < int_RandPoint; i++)
        {
            int int_Num;

            while(true)
            {
                int_Num = rand() % 5;

                if(intarr_CheckNum[int_Num] == 0)
                {
                    intarr_CheckNum[int_Num]++;

                    break;
                }
            }

            intarr_ScorePoint[i] = 1 + 2 * int_Num;
        }

        std::sort(intarr_ScorePoint, intarr_ScorePoint + int_RandPoint);

        fn_SetScorePoint(intptr_ScorePointX, int_RandPoint);
        fn_Delay(1000);
        fn_Line();
        fn_Display();
        fn_Delay(1000);

        while(12 - int_NowY)
        {
            fn_Fall();
            fn_Display();
            fn_Delay(1000);
        }

        fn_Line();

        for(int i = 0; i < int_RandPoint; i++)
        {
            if(intarr_ScorePoint[i] == int_NowX)
            {
                switch(int_RandPoint)
                {
                    case 1:
                        int_PinballCount += 5 * int_PutBall;

                        std::cout<< "\n[系統] 贏得" << 5 * int_PutBall << "顆彈珠!\n\n";

                        break;

                    case 2:
                        int_PinballCount += 3 * int_PutBall;

                        std::cout<< "\n[系統] 贏得" << 3 * int_PutBall << "顆彈珠!\n\n";

                        break;

                    case 3:
                        int_PinballCount += 1 * int_PutBall;

                        std::cout<< "\n[系統] 贏得" << 1 * int_PutBall << "顆彈珠!\n\n";

                        break;
                }

                break;
            }

            if(i == int_RandPoint - 1) std::cout<< "\n[系統] 再接再厲!\n\n";
        }

        if(int_PinballCount > 0)
        {
            std::string str_Ans;

            std::cout<< "是否要繼續遊玩？(輸入 yes 或 no)\n回答：";

            while(true)
            {
                std::cin>> str_Ans;

                std::transform(str_Ans.begin(), str_Ans.end(), str_Ans.begin(), ::tolower);

                if(str_Ans == "yes")
                {
                    bl_KeepPlaying = true;

                    std::cout<< '\n';

                    break;
                }
                else if(str_Ans == "no")
                {


                    std::cout<< '\n';

                    fn_Line();

                    std::cout<< "\n           遊戲結束            \n\n";

                    fn_Line();

                    break;
                }
                else std::cout<< "\n[系統] 輸入格式不符，請再次輸入!\n回答：";
            }
        }
        else
        {
            bl_KeepPlaying = false;

            std::cout<< "[系統] 你沒有彈珠了!\n\n";

            fn_Line();

            std::cout<< "\n           遊戲結束            \n\n";

            fn_Line();
        }
    }
    while(bl_KeepPlaying);

	return 0;
}

void  fn_Line()
{
    std::cout<< "===============================\n";

    return;
}

void  fn_Delay(int int_Time)
{
    clock_t now = clock();

    while(clock() - now < int_Time);

    return;
}

void  fn_RorL(int int_Direction)
{
    if(int_Direction)
    {
        int2arr_Board[int_NowY++][int_NowX++] = 0;
        int2arr_Board[int_NowY][int_NowX] = 2;
    }
    else
    {
        int2arr_Board[int_NowY++][int_NowX--] = 0;
        int2arr_Board[int_NowY][int_NowX] = 2;
    }

    return;
}

void  fn_Fall()
{
    if(int2arr_Board[int_NowY + 1][int_NowX] != 1 &&
       int2arr_Board[int_NowY + 1][int_NowX] != 0)
    {
        switch(int_NowX)
        {
            case 1: fn_RorL(1); break;
            case 9: fn_RorL(0); break;
            default: fn_RorL(rand() % 2);
        }
    }
    else
    {
        int2arr_Board[int_NowY++][int_NowX] = 0;
        int2arr_Board[int_NowY][int_NowX] = 2;
    }

    return;
}

void  fn_SetScorePoint(int* intptr_ScorePointX, int int_Size)
{
    for(int i = 0; i < int_Size; i++)
    {
        int2arr_Board[12][*(intptr_ScorePointX + i)] = 1;
    }

    return;
}

void  fn_Display()
{
    fn_Line();

    for(int i = 0; i < 13; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            switch(int2arr_Board[i][j])
            {
                case -1: std::cout<< "|  "; break;
                case -2: std::cout<< "*  "; break;
                case  0: std::cout<< "   "; break;
                case  1: std::cout<< "$  "; break;
                case  2: std::cout<< "o  "; break;
            }
        }

        std::cout<< '\n';
    }

    fn_Line();

    return;
}

void  fn_ResetLastLine()
{
    for(int i = 1; i < 11; i += 2)
    {
        int2arr_Board[12][i] = 0;
    }

    return;
}
