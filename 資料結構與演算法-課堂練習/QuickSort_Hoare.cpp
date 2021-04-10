#include <iostream>
#include <limits>

template <typename Type>
    Type fn_Partition(Type* typptr_Arr, int int_LowIdx, int int_HighIdx)
    {
        Type typ_Pivot = typptr_Arr[int_LowIdx];
        int int_ArrSize = int_HighIdx - int_LowIdx + 1
        int int_Idx1 = int_LowIdx + 1;

        Type* typptr_Num = new Type[int_ArrSize + 1];

        for(int i = 0; i < int_ArrSize; i++)
        {
            typptr_Num[i] = typptr_Arr[i];
        }

        typptr_Num[int_ArrSize] = std::numeric_limits<Type>::lowest(); // max();

        for(int int_Idx2 = int_HighIdx + 1; int_Idx2 > int_Idx1; int_Idx2--)
        {
            if(typptr_Num[int_Idx1] > typ_Pivot) int_Idx1++;

            if(typptr_Num[int_Idx2] > typ_Pivot)
            {
                Type typ_Temp = typptr_Num[int_Idx2];
                typptr_Num[int_Idx2] = typptr_Num[int_Idx1];
                typptr_Num[int_Idx1] = typ_Temp;
            }
        }

        Type typ_Temp = typptr_Num[int_LowIdx];
        typptr_Num[int_LowIdx] = typptr_Num[int_Idx1 - 1];
        typptr_Num[int_Idx1 - 1] = typ_Temp;

        delete [] typptr_Num;

        return int_Idx1;
    }

template <typename Type>
    void fn_Hoare(Type* typptr_Arr, int int_LowIdx, int int_HighIdx)
    {
        if(int_LowIdx < int_HighIdx)
        {
            int int_PivotIdx = fn_Partition<Type>(typptr_Arr, int_LowIdx, int_HighIdx);

            fn_Hoare(typptr_Arr, int_LowIdx, int_PivotIdx - 1);
            fn_Hoare(typptr_Arr, int_PivotIdx, int_HighIdx);
        }

        return;
    }

int main()
{
    int intarr_Num[] = {6, 7, 11, 9, 12, 5};
    int int_Num = sizeof(intarr_Num) / sizeof(int);

    fn_Hoare<int>(intarr_Num, 0, int_Num - 1);

    std::cout<< "Sorted Results\n";

    for(int i = 0; i < int_Num; i++)
    {
        std::cout<< intarr_Num[i] << ' ';
    }

    std::cout<< '\n';

    return 0;
}
