#include <iostream>
#include <cstdlib>

template <class c1_C1>
    class Unit  //element
    {
    public:
        c1_C1 o_Field;
        Unit* op_Next;
        Unit* op_Pre;

        Unit(c1_C1 o_Field);
    };

template <class c1_C1>
    class Que
    {
    public:
        Unit<c1_C1>* op_Front;
        Unit<c1_C1>* op_Rear;
        int i_Size;

        Que();

        void fn_PushE(Unit<c1_C1>* op_Ele);
        void fn_PopE();
        void fn_InsertE(Unit<c1_C1>* op_Ele, int int_Index);

        c1_C1 fn_ShowFrE()
        {
            return (op_Front != nullptr) ? op_Front->o_Field : NULL;
        }

        c1_C1 fn_ShowReE()
        {
            return (op_Rear != nullptr) ? op_Rear->o_Field : NULL;
        }
    };


int main()
{
    Que<int> o_Que;

    o_Que.fn_PushE(new Unit<int>(3));
    o_Que.fn_PushE(new Unit<int>(5));
    o_Que.fn_PushE(new Unit<int>(7));

    o_Que.fn_InsertE(new Unit<int>(1), 0);

    std::cout<< "The Front element is "<< o_Que.fn_ShowFrE() << "; the last one is "<< o_Que.fn_ShowReE() <<"\n";

    o_Que.fn_PopE();

    std::cout<< "The Front element is "<< o_Que.fn_ShowFrE() << "; the last one is "<< o_Que.fn_ShowReE() <<"\n";

    o_Que.fn_PopE();

    std::cout<< "The Front element is "<< o_Que.fn_ShowFrE() << "; the last one is "<< o_Que.fn_ShowReE() <<"\n";

    o_Que.fn_PopE();

    std::cout<< "The Front element is "<< o_Que.fn_ShowFrE() << "; the last one is "<< o_Que.fn_ShowReE() <<"\n";

    o_Que.fn_PopE();

    return 0;
}

template <typename c1_C1> // 建立格子
    Unit<c1_C1>::Unit(c1_C1 o_Field)
    {
        this->o_Field = o_Field;
        op_Next = nullptr;
        op_Pre  = nullptr;
    }

template <typename c1_C1> // 建立空佇列
    Que<c1_C1>::Que()
    {
        op_Front = nullptr;
        op_Rear  = nullptr;
        i_Size   = 0;
    }

template <typename c1_C1> // 將格子填入佇列後方
    void Que<c1_C1>::fn_PushE(Unit<c1_C1>* op_Ele)
    {
        if(op_Front == op_Rear && op_Front == nullptr)// COM: nothing
        {
            op_Front= op_Rear = op_Ele;
        }
        else// COM: existing objects
        {
            op_Rear->op_Next = op_Ele;
            op_Ele->op_Pre   = op_Rear;
            op_Rear = op_Ele;
        }

        i_Size++;

        std::cerr<< "Push the item" << op_Ele->o_Field << "\n";
    }

template <typename c1_C1> // 將格子從佇列前方取出
    void Que<c1_C1>::fn_PopE()
    {
        if(op_Front == op_Rear && op_Front == nullptr)
        {
            std::cerr<< "No items for popping\n";
            return;
        }
        else
        {
            std::cerr<< "Pop the item: " << op_Front->o_Field << "\n";

            if(op_Front == op_Rear)// COM: Pop the last one item
            {
                delete op_Front;

                op_Front = nullptr;
                op_Rear  = nullptr;
            }
            else
            {
                Unit<c1_C1>* op_PreTmp = op_Front->op_Next;
                op_PreTmp->op_Pre = nullptr;

                delete op_Front;

                op_Front = op_PreTmp;
            }

            i_Size--;
        }
    }

template <typename c1_C1> // 將格子插入佇列中指定位置
    void Que<c1_C1>::fn_InsertE(Unit<c1_C1>* op_Ele, int int_Index)
    {
        int int_Count = int_Index;

        if(int_Index == 0)// COM: nothing
        {
            op_Front->op_Pre = op_Ele;
            op_Ele->op_Next = op_Front;
            op_Front = op_Ele;
            op_Front->op_Pre = nullptr;
        }
        else if(int_Index > 0)// COM: existing objects
        {
            Unit<c1_C1>* op_Temp = op_Front;

            while(int_Count--) op_Temp = op_Temp->op_Next;

            (op_Temp->op_Pre)->op_Next = op_Ele;
            op_Ele->op_Pre = (op_Temp->op_Pre);
            op_Temp->op_Pre = op_Ele;
            op_Ele->op_Next = op_Temp;
        }

        i_Size++;

        std::cerr<< "Insert the item" << op_Ele->o_Field << " at " << int_Index << "\n";
    }
