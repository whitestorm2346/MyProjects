#include <iostream>

template <typename Type>
    Type fn_Partition(Type* typptr_Arr, int int_LowIdx, int int_HighIdx)
    {
        Type typ_Pivot = typptr_Arr[int_HighIdx];
        int int_Idx1 = int_LowIdx - 1;

        for(int int_Idx2 = int_LowIdx; int_Idx2 < int_HighIdx; int_Idx2++)
        {
            if(typptr_Arr[int_Idx2] >= typ_Pivot)
            {
                int_Idx1++;
                Type typ_Temp = typptr_Arr[int_Idx1];
                typptr_Arr[int_Idx1] = typptr_Arr[int_Idx2];
                typptr_Arr[int_Idx2] = typ_Temp;
            }
        }

        Type typ_Temp = typptr_Arr[int_HighIdx];
        typptr_Arr[int_HighIdx]  = typptr_Arr[int_Idx1 + 1];
        typptr_Arr[int_Idx1 + 1] = typ_Temp;

        return int_Idx1 + 1;
    }

template <typename Type>
    void fn_Lomuto(Type* typptr_Arr, int int_LowIdx, int int_HighIdx)
    {
        if(int_LowIdx < int_HighIdx)
        {
            int int_PivotIdx = fn_Partition<Type>(typptr_Arr, int_LowIdx, int_HighIdx);

            fn_Lomuto(typptr_Arr, int_LowIdx, int_PivotIdx - 1);
            fn_Lomuto(typptr_Arr, int_PivotIdx - 1, int_HighIdx);
        }

        return;
    }

int main()
{
    int intarr_Num[] = {10, 7, 8, 9, 1, 5};
    int int_Num = sizeof(intarr_Num) / sizeof(int);

    fn_Lomuto(intarr_Num, 0, int_Num - 1);

    std::cout<< "Sorted Results\n";

    for(int i = 0; i < int_Num; i++)
    {
        std::cout<< intarr_Num[i] << ' ';
    }

    std::cout<< '\n';

    return 0;
}
