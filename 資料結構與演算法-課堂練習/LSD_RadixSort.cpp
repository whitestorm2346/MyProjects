#include <iostream>

int  fn_GetMax(int* intptr_Arr, int int_Size);
void fn_CountingSort(int* intarr_Input, int* intarr_Output, int int_Size, int int_Exp);
void fn_RadixSort(int* intarr_Input, int* intarr_Output, int int_Size);

int main()
{
    int intarr_Num[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int int_Size = sizeof(intarr_Num) / sizeof(int);
    int* intptr_TempArr = new int[int_Size]{};

    fn_RadixSort(intarr_Num, intptr_TempArr, int_Size);

    for(int i = 0; i < int_Size; i++)
    {
        std::cout<< intptr_TempArr[i] << ' ';
    }

    delete [] intptr_TempArr;

    return 0;
}

int  fn_GetMax(int* intptr_Arr, int int_Size)
{
    int int_Max = intptr_Arr[0];

    for(int i = 1; i < int_Size; i++)
    {
        if(intptr_Arr[i] > int_Max) int_Max = intptr_Arr[i];
    }

    return int_Max;
}

void fn_CountingSort(int* intarr_Input, int* intarr_Output, int int_Size, int int_Exp)
{
    int* intptr_CountArr = new int[10]{};

    for(int i = 0; i < int_Size; i++)
    {
        intptr_CountArr[(intarr_Input[i] / int_Exp) % 10]++;
    }

    for(int i = 1; i < 10; i++)
    {
        intptr_CountArr[i] += intptr_CountArr[i - 1];
    }

    for(int i = int_Size - 1; i >= 0; i--)
    {
        intarr_Output[(--(intptr_CountArr[(intarr_Input[i] / int_Exp) % 10]))] = intarr_Input[i];
    }

    for(int i = 0; i < int_Size; i++)
    {
        intarr_Input[i] = intarr_Output[i];
    }

    delete [] intptr_CountArr;

    return;
}

void fn_RadixSort(int* intarr_Input, int* intarr_Output, int int_Size)
{
    int int_Max = fn_GetMax(intarr_Input, int_Size);

    for(int int_Exp = 1; int_Max / int_Exp > 0; int_Exp *= 10)
    {
        fn_CountingSort(intarr_Input, intarr_Output, int_Size, int_Exp);
    }

    return;
}
