#include <iostream>

int int_M, int_N;

int fn_GetPath(int* intarr_Block, bool* blarr_Check,  int i, int j);

int main()
{
    std::cin>> int_M >> int_N;

    int intarr_Block[int_M + 1][int_N + 1];
    bool blarr_Check[int_M + 1][int_N + 1];

    for(int i = 0; i <= int_M; i++)
    {
        for(int j = 0; j <= int_N; j++)
        {
            intarr_Block[i][j] = 0;
            blarr_Check[i][j] = false;
        }
    }

    intarr_Block[1][1] = 1;
    blarr_Check[1][1] = true;

    for(int i = 0; i <= int_M; i++) blarr_Check[i][0] = true;
    for(int i = 0; i <= int_N; i++) blarr_Check[0][i] = true;

    fn_GetPath(reinterpret_cast<int*>(intarr_Block), reinterpret_cast<bool*>(blarr_Check), int_M, int_N);

    std::cout<< intarr_Block[int_M][int_N] << '\n';

    return 0;
}

int fn_GetPath(int* intarr_Block, bool* blarr_Check, int i, int j)
{
    if(*(blarr_Check + i * int_N + j) == true) return *(intarr_Block + i * int_N + j);
    else
    {
        *(blarr_Check + i * int_N + j) = true;
        *(intarr_Block + i * int_N + j) = fn_GetPath(intarr_Block, blarr_Check, i - 1, j) + fn_GetPath(intarr_Block, blarr_Check, i, j - 1);

        return *(intarr_Block + i * int_N + j);
    }
}
