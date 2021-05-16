#include <iostream>
#define CirQue_Size 7

template <typename Type>
    class CirQue
    {
    public:
        Type typ_Arr[CirQue_Size + 1];
        int int_FrontIndex;
        int int_BackIndex;

        CirQue();

        void fn_Push(Type typ_Ele);
        void fn_Pop();
        Type fn_Front();
        Type fn_Back();
    };

int main()
{
    CirQue<int> cque_1;

    for(int i = 10; i < 17; i++)
    {
        cque_1.fn_Push(i);
    }

    for(int i = 0; i < 7; i++)
    {
        cque_1.fn_Pop();
    }

    return 0;
}

template <typename Type>
    CirQue<Type>::CirQue()
    {
        int_FrontIndex = int_BackIndex  = 0;
    }

template <typename Type>
    void CirQue<Type>::fn_Push(Type typ_Ele)
    {
        if(int_BackIndex == (int_FrontIndex + CirQue_Size) % (CirQue_Size + 1))
        {
            std::cerr<< "No space can save this element!\n";

            return;
        }
        else
        {
            std::cerr<< "Push " << typ_Ele << " into the queue.\n";

            typ_Arr[int_BackIndex] = typ_Ele;

            ++int_BackIndex %= (CirQue_Size + 1);

            std::cerr<< "BackIndex: " << int_BackIndex << '\n';

            return;
        }
    }

template <typename Type>
    void CirQue<Type>::fn_Pop()
    {
        if(int_FrontIndex == int_BackIndex)
        {
            std::cerr<< "No item can pop out!\n";

            return;
        }
        else
        {
            std::cerr<< "Pop " << typ_Arr[int_FrontIndex] << " out.\n";

            typ_Arr[int_FrontIndex] = NULL;

            ++int_FrontIndex %= (CirQue_Size + 1);

            std::cerr<< "FrontIndex: " << int_FrontIndex << '\n';

            return;
        }
    }

template <typename Type>
    Type CirQue<Type>::fn_Front()
    {
        std::cerr<< "Front: " << typ_Arr[int_FrontIndex] << '\n';

        return typ_Arr[int_FrontIndex];
    }

template <typename Type>
    Type CirQue<Type>::fn_Back()
    {
        std::cerr<< "Back: " << typ_Arr[int_BackIndex - 1] << '\n';

        return typ_Arr[int_BackIndex - 1];
    }
