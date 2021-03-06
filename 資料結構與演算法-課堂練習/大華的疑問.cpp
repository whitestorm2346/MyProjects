#include <iostream>
#include <string>

char chrarr_KeyBoard[40][2] = {
    {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'},
    {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'},

    {'Q'}, {'W'}, {'E'}, {'R'}, {'T'}, {'Y'}, {'U'}, {'I'}, {'O'}, {'P'},
    {'A'}, {'S'}, {'D'}, {'F'}, {'G'}, {'H'}, {'J'}, {'K'}, {'L'}, {';', ':'},
    {'Z'}, {'X'}, {'C'}, {'V'}, {'B'}, {'N'}, {'M'}, {',', '<'}, {'.', '>'}, {'/', '?'}
};

int main()
{
    int int_Times;

    std::cin>> int_Times;

    while(int_Times--)
    {
        char chr_Test;
        int  int_Direction, int_NowX, int_NowY;

        std::cin>> chr_Test >> int_Direction;

        for(int i = 0; i < 40; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                if(chrarr_KeyBoard[i][j] == chr_Test)
                {
                    int_NowY = i / 10;
                    int_NowX = i % 10;
                }
            }
        }

        switch(int_Direction)
        {
            case 1: int_NowY--; if(int_NowY < 0) int_NowY +=  4; break;
            case 2: int_NowY++; if(int_NowY > 3) int_NowY -=  4; break;
            case 3: int_NowX++; if(int_NowX > 9) int_NowY -= 10; break;
            case 4: int_NowX--; if(int_NowX < 0) int_NowY += 10; break;
        }

        std::cout<< chrarr_KeyBoard[int_NowY * 10 + int_NowX][0] << '\n';
    }

    return 0;
}
