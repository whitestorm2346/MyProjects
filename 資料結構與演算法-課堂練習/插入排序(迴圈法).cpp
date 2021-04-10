#include <iostream>

template <typename Type>    // 修改這邊以改變排序方式
    bool fn_Compare(Type typ_Num1, Type typ_Num2)
    {
        return typ_Num1 > typ_Num2;
    }

int main()
{
    int intarr_Num[] = {2, 1, 3, 5, 7, 8, 10};

    for(int i = 1; i < sizeof(intarr_Num) / sizeof(int); i++)
    {
        for(int j = i; j > 0; j--)
        {
            if(fn_Compare<int>(intarr_Num[j], intarr_Num[j - 1]))
            {
                int int_Temp = intarr_Num[j - 1];

                intarr_Num[j - 1] = intarr_Num[j];
                intarr_Num[j] = int_Temp;
            }
            else break;
        }
    }

    for(int i = 0; i < sizeof(intarr_Num) / sizeof(int); i++)
    {
        std::cout<< intarr_Num[i] << '\n';
    }

    return 0;
}
