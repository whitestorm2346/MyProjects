#include <iostream>

template <typename Type>
int fn_Partition(Type* typptr_Arr, int int_LIdx, int int_RIdx);

template <typename Type>
void fn_QuickSort(Type* typptr_Arr, int int_LIdx, int int_RIdx);

int main()
{
    int intarr_Num[] = {5, 1, 2, 8, 9, 10};
    int int_Size = sizeof(intarr_Num) / sizeof(int);

    fn_QuickSort<int>(intarr_Num, 0, int_Size - 1);

    std::cout<< "Sorted array: ";

    for(int i = 0; i < int_Size; i++)
    {
        std::cout<< intarr_Num[i] << ' ';
    }

    return 0;
}

template <typename Type>
int fn_Partition(Type* typptr_Arr, int int_LIdx, int int_RIdx)
{
    Type typ_Pivot = typptr_Arr[int_LIdx];
    int i = int_LIdx - 1;
    int j = int_RIdx + 1;

    for(;;)
    {
        do
        {
            i++;
        }
        while(typptr_Arr[i] > typ_Pivot);

        do
        {
            j--;
        }
        while(typptr_Arr[j] < typ_Pivot);

        if(i >= j) return j;
        else
        {
            Type typ_Temp = typ_Pivot;

            typ_Pivot = typptr_Arr[i - 1];
            typptr_Arr[i - 1] = typ_Temp;
        }
    }
}

template <typename Type>
void fn_QuickSort(Type* typptr_Arr, int int_LIdx, int int_RIdx)
{
    if(int_LIdx < int_RIdx)
    {
        int int_PivIdx = fn_Partition<Type>(typptr_Arr, int_LIdx, int_RIdx);

        fn_QuickSort(typptr_Arr, int_LIdx, int_PivIdx);
        fn_QuickSort(typptr_Arr, int_PivIdx + 1, int_RIdx);
    }

    return;
}

