#include <iostream>
#include <string>

#define int_CmdCount 15
#define SINGLY_LINKED_LIST 1
#define DOUBLY_LINKED_LIST 2
#define SINGLY_CIRCULAR_LINKED_LIST 3
#define DOUBLY_CIRCULAR_LINKED_LIST 4

template <typename Type>
class Singly_Node
{
public:
    Type typ_Field;
    Singly_Node* nodptr_Next;

    Singly_Node(Type typ_Field);
};

template <typename Type>
class Singly_Linked_List
{
private:
    int int_NodCount;

public:
    Singly_Node<Type>* nodptr_Start;
    Singly_Node<Type>* nodptr_Curr;

    Singly_Linked_List();
    ~Singly_Linked_List();

    void fn_AddNode(Type typ_Field);
    void fn_Trace();
    void fn_Insert(int int_Idx, Type typ_Field);
    void fn_Renew(int int_Idx, Type typ_Field);
    bool fn_DelNode(int int_Idx);
};

template <typename Type>
class Singly_Circular_Linked_List
{
private:
    int int_NodCount;

public:
    Singly_Node<Type>* nodptr_Start;
    Singly_Node<Type>* nodptr_Curr;

    Singly_Circular_Linked_List();
    ~Singly_Circular_Linked_List();

    void fn_AddNode(Type typ_Field);
    void fn_Trace();
    void fn_Insert(int int_Idx, Type typ_Field);
    void fn_Renew(int int_Idx, Type typ_Field);
    bool fn_DelNode(int int_Idx);
};

template <typename Type>
class Doubly_Node
{
public:
    Type typ_Field;
    Doubly_Node* nodptr_Next;
    Doubly_Node* nodptr_Prev;

    Doubly_Node(Type typ_Field);
};

template<typename Type>
class Doubly_Linked_List
{
private:
    int int_NodCount;

public:
    Doubly_Node<Type>* nodptr_Start;
    Doubly_Node<Type>* nodptr_End;

    Doubly_Linked_List();
    ~Doubly_Linked_List();

    void fn_Trace();
    void fn_AddNode(Type typ_Field);
    void fn_UpdNode(int int_Idx, Type typ_Field);
    void fn_InsNode(int int_Idx, Type typ_Field);
    bool fn_DelNode(int int_Idx);
};

template<typename Type>
class Doubly_Circular_Linked_List
{
private:
    int int_NodCount;

public:
    Doubly_Node<Type>* nodptr_Start;
    Doubly_Node<Type>* nodptr_End;

    Doubly_Circular_Linked_List();
    ~Doubly_Circular_Linked_List();

    void fn_Trace();
    void fn_AddNode(Type typ_Field);
    void fn_UpdNode(int int_Idx, Type typ_Field);
    void fn_InsNode(int int_Idx, Type typ_Field);
    bool fn_DelNode(int int_Idx);
};

void fn_SetLinkedList(int &int_Case);
void fn_SetCmd(std::string *strarr_Cmd);
void fn_ShowAllCmd(std::string *strarr_Cmd);
void fn_RunCmd(std::string str_Input, int int_Case);

Singly_Linked_List<int>* sll_ptr = nullptr;
Doubly_Linked_List<int>* dll_ptr = nullptr;
Singly_Circular_Linked_List<int>* scll_ptr = nullptr;
Doubly_Circular_Linked_List<int>* dcll_ptr = nullptr;

int main()
{
    std::string str_Input, str_Cmd[int_CmdCount];
    int int_CurrCase = 0;

    std::cout<< "[system] You have to set the linked list first.\n";

    fn_SetLinkedList(int_CurrCase);

    switch(int_CurrCase)
    {
        case SINGLY_LINKED_LIST: sll_ptr = new Singly_Linked_List<int>(); break;
        case DOUBLY_LINKED_LIST: dll_ptr = new Doubly_Linked_List<int>(); break;
        case SINGLY_CIRCULAR_LINKED_LIST: scll_ptr = new Singly_Circular_Linked_List<int>(); break;
        case DOUBLY_CIRCULAR_LINKED_LIST: dcll_ptr = new Doubly_Circular_Linked_List<int>(); break;
    }

    std::cout<< "[system] Now you can use command \"/help\" to check all commands.\n\n";

    fn_SetCmd(str_Cmd);

    while(std::cin>> str_Input)
    {
        if(str_Input == "/end") break;
        else if(str_Input == "/help") fn_ShowAllCmd(str_Cmd);
        else fn_RunCmd(str_Input, int_CurrCase);

        std::cout<< '\n';
    }

    switch(int_CurrCase)
    {
        case SINGLY_LINKED_LIST: delete sll_ptr; break;
        case DOUBLY_LINKED_LIST: delete dll_ptr; break;
        case SINGLY_CIRCULAR_LINKED_LIST: delete scll_ptr; break;
        case DOUBLY_CIRCULAR_LINKED_LIST: delete dcll_ptr; break;
    }

    std::cout<< "\n[system] End up successfully.\n";

    return 0;
}

void fn_SetLinkedList(int &int_Case)
{
    std::cout<< "[system] Please choose a kind of linked list.\n\n";
    std::cout<< "(1) Singly Linked List\n";
    std::cout<< "(2) Doubly Linked List\n";
    std::cout<< "(3) Singly Circular Linked List\n";
    std::cout<< "(4) Doubly Circular Linked List\n\n";

    while(true)
    {
        std::cout<< "[system] Input a number.\n";
        std::cin>> int_Case;

        if(int_Case == 1 || int_Case == 2 || int_Case == 3 || int_Case == 4) break;

        std::cout<< "\n[system] Illegal input! Please input again.\n";
    }

    std::cout<< "\n[system] Finished setting.\n";
}

void fn_SetCmd(std::string *strarr_Cmd)
{
    strarr_Cmd[0]  = "/add";
    strarr_Cmd[1]  = "/del";
    strarr_Cmd[2]  = "/modify";
    strarr_Cmd[3]  = "/insert";
    strarr_Cmd[4]  = "/get_elem";
    strarr_Cmd[5]  = "/get_adrs";
    strarr_Cmd[6]  = "/elem_trace";
    strarr_Cmd[7]  = "/adrs_trace";
    strarr_Cmd[8]  = "/create_ptr";
    strarr_Cmd[9]  = "/get_curr_elem";
    strarr_Cmd[10] = "/get_curr_adrs";
    strarr_Cmd[11] = "/ptr_to_next";
    strarr_Cmd[12] = "/ptr_to_prev";
    strarr_Cmd[13] = "/del_ptr";
    strarr_Cmd[14] = "/end";
}

void fn_ShowAllCmd(std::string *strarr_Cmd)
{
    std::cout<< '\n';

    for(int i = 0; i < int_CmdCount; i++)
    {
        std::cout<< strarr_Cmd[i] << '\n';
    }
}

void fn_RunCmd(std::string str_Input, int int_Case)
{
    if(str_Input == "/add")
    {
        int int_Num;

        std::cout<< "[system] Input a number.\n";
        std::cin>> int_Num;

        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: sll_ptr->fn_AddNode(int_Num); break;
            case DOUBLY_LINKED_LIST: dll_ptr->fn_AddNode(int_Num); break;
            case SINGLY_CIRCULAR_LINKED_LIST: scll_ptr->fn_AddNode(int_Num); break;
            case DOUBLY_CIRCULAR_LINKED_LIST: dcll_ptr->fn_AddNode(int_Num); break;
        }

        return;
    }
    else if(str_Input == "/del")
    {
        int int_Idx;

        std::cout<< "[system] Input an index number.\n";
        std::cin>> int_Idx;

        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: sll_ptr->fn_DelNode(int_Idx); break;
            case DOUBLY_LINKED_LIST: dll_ptr->fn_DelNode(int_Idx); break;
            case SINGLY_CIRCULAR_LINKED_LIST: scll_ptr->fn_DelNode(int_Idx); break;
            case DOUBLY_CIRCULAR_LINKED_LIST: dcll_ptr->fn_DelNode(int_Idx); break;
        }

        return;
    }
    else if(str_Input == "/modify")
    {
        int int_NewNum, int_Idx;

        std::cout<< "[system] Input an index number.\n";
        std::cin>> int_Idx;

        std::cout<< "[system] Input a new number.\n";
        std::cin>> int_NewNum;

        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: sll_ptr->fn_Renew(int_Idx, int_NewNum); break;
            case DOUBLY_LINKED_LIST: dll_ptr->fn_UpdNode(int_Idx, int_NewNum); break;
            case SINGLY_CIRCULAR_LINKED_LIST: scll_ptr->fn_Renew(int_Idx, int_NewNum); break;
            case DOUBLY_CIRCULAR_LINKED_LIST: dcll_ptr->fn_UpdNode(int_Idx, int_NewNum); break;
        }

        return;
    }
    else if(str_Input == "/insert")
    {
        int int_Num, int_Idx;

        std::cout<< "[system] Input an index number.\n";
        std::cin>> int_Idx;

        std::cout<< "[system] Input a number.\n";
        std::cin>> int_Num;

        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: sll_ptr->fn_Insert(int_Idx, int_Num); break;
            case DOUBLY_LINKED_LIST: dll_ptr->fn_InsNode(int_Idx, int_Num); break;
            case SINGLY_CIRCULAR_LINKED_LIST: scll_ptr->fn_Insert(int_Idx, int_Num); break;
            case DOUBLY_CIRCULAR_LINKED_LIST: dcll_ptr->fn_InsNode(int_Idx, int_Num); break;
        }

        return;
    }
    else if(str_Input == "/get_elem")
    {
        std::cout<< "[system] This command hasn\'t finished yet.\n";

        /*switch(int_Case)
        {
            case 1:
            case 2:
            case 3:
            case 4:
        }*/

        return;
    }
    else if(str_Input == "/get_adrs")
    {
        std::cout<< "[system] This command hasn\'t finished yet.\n";

        /*switch(int_Case)
        {
            case 1:
            case 2:
            case 3:
            case 4:
        }*/

        return;
    }
    else if(str_Input == "/elem_trace")
    {
        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: sll_ptr->fn_Trace(); break;
            case DOUBLY_LINKED_LIST: dll_ptr->fn_Trace(); break;
            case SINGLY_CIRCULAR_LINKED_LIST: scll_ptr->fn_Trace(); break;
            case DOUBLY_CIRCULAR_LINKED_LIST: dcll_ptr->fn_Trace(); break;
        }

        return;
    }
    else if(str_Input == "/adrs_trace")
    {
        std::cout<< "[system] This command hasn\'t finished yet.\n";

        /*switch(int_Case)
        {
            case 1:
            case 2:
            case 3:
            case 4:
        }*/

        return;
    }
    else if(str_Input == "/create_ptr")
    {
        std::cout<< "[system] This command hasn\'t finished yet.\n";

        /*switch(int_Case)
        {
            case 1:
            case 2:
            case 3:
            case 4:
        }*/

        return;
    }
    else if(str_Input == "/get_curr_elem")
    {
        std::cout<< "[system] This command hasn\'t finished yet.\n";

        /*switch(int_Case)
        {
            case 1:
            case 2:
            case 3:
            case 4:
        }*/

        return;
    }
    else if(str_Input == "/get_curr_adrs")
    {
        std::cout<< "[system] This command hasn\'t finished yet.\n";

        /*switch(int_Case)
        {
            case 1:
            case 2:
            case 3:
            case 4:
        }*/

        return;
    }
    else if(str_Input == "/ptr_to_next")
    {
        std::cout<< "[system] This command hasn\'t finished yet.\n";

        /*switch(int_Case)
        {
            case 1:
            case 2:
            case 3:
            case 4:
        }*/

        return;
    }
    else if(str_Input == "/ptr_to_prev")
    {
        std::cout<< "[system] This command hasn\'t finished yet.\n";

        /*switch(int_Case)
        {
            case 1:
            case 2:
            case 3:
            case 4:
        }*/

        return;
    }
    else if(str_Input == "/del_ptr")
    {
        std::cout<< "[system] This command hasn\'t finished yet.\n";

        /*switch(int_Case)
        {
            case 1:
            case 2:
            case 3:
            case 4:
        }*/

        return;
    }

    std::cout<< "[system] Illegal command!\n";

    return;
}

template <typename Type>
Singly_Node<Type>::Singly_Node(Type typ_Field)
{
    this->typ_Field = typ_Field;
    nodptr_Next = nullptr;
}

template <typename Type>
Singly_Linked_List<Type>::Singly_Linked_List()
{
    nodptr_Start = nodptr_Curr = nullptr;
    int_NodCount = 0;
}

template <typename Type>
Singly_Linked_List<Type>::~Singly_Linked_List()
{
    for(Singly_Node<Type>* nodptr_Temp1 = nodptr_Start; nodptr_Temp1 != nullptr;)
    {
        Singly_Node<Type>* nodptr_Temp2 = nodptr_Temp1->nodptr_Next;
        delete nodptr_Temp1;
        nodptr_Temp1 = nodptr_Temp2;
    }
}

template <typename Type>
void Singly_Linked_List<Type>::fn_AddNode(Type typ_Field)
{
    Singly_Node<Type>* nod_ptr = new Singly_Node<Type>(typ_Field);

    if(nodptr_Start == nullptr) nodptr_Start = nodptr_Curr = nod_ptr;
    else
    {
        nodptr_Curr->nodptr_Next = nod_ptr;
        nodptr_Curr = nod_ptr;
    }

    int_NodCount++;
}

template <typename Type>
void Singly_Linked_List<Type>::fn_Trace()
{
    std::cout<< "start -> ";

    for(Singly_Node<Type>* nodptr_Temp = nodptr_Start; nodptr_Temp != nullptr; nodptr_Temp = nodptr_Temp->nodptr_Next)
    {
        std::cout<< nodptr_Temp->typ_Field << " -> ";
    }

    std::cout<< " nullptr\n";
}

template <typename Type>
void Singly_Linked_List<Type>::fn_Insert(int int_Idx, Type typ_Field)
{
    Singly_Node<Type>* nodptr_Input = new Singly_Node<Type>(typ_Field);

    if(int_Idx == 0)
    {
        nodptr_Input->nodptr_Next = nodptr_Start;
        nodptr_Start = nodptr_Input;
    }
    else
    {
        Singly_Node<Type>* nodptr_Temp = nodptr_Start;

        while(--int_Idx)
        {
            nodptr_Temp = nodptr_Temp->nodptr_Next;
        }

        if(nodptr_Temp->nodptr_Next == nullptr)nodptr_Input->nodptr_Next = nullptr;
        else nodptr_Input->nodptr_Next = nodptr_Temp->nodptr_Next;

        nodptr_Temp->nodptr_Next = nodptr_Input;
    }

    delete nodptr_Input;
}

template <typename Type>
void Singly_Linked_List<Type>::fn_Renew(int int_Idx, Type typ_Field)
{
    Singly_Node<Type>* nodptr_Temp = nodptr_Start;

    while(int_Idx--)
    {
        nodptr_Temp = nodptr_Temp->nodptr_Next;
    }

    nodptr_Temp->typ_Field = typ_Field;
}

template <typename Type>
bool Singly_Linked_List<Type>::fn_DelNode(int int_Idx)
{
    bool bl_IsSuccess = true;

    if(int_Idx > int_NodCount - 1) bl_IsSuccess = false;
    else
    {
        Singly_Node<Type>* nodptr_TmpCurr = nodptr_Start;
        Singly_Node<Type>* nodptr_TmpPrev = nodptr_Start;

        for(int i = 1; i < int_Idx + 1; i++)
        {
            nodptr_TmpPrev = nodptr_TmpCurr;
            nodptr_TmpCurr = nodptr_TmpCurr->nodptr_Next;
        }

        if(int_Idx == 0)
        {
            nodptr_Start = nodptr_Start->nodptr_Next;
            nodptr_Curr = nullptr;
        }
        else if(int_Idx == int_NodCount - 1 && int_Idx != 0)
        {
            nodptr_Curr = nodptr_TmpPrev;
            nodptr_TmpPrev->nodptr_Next = nullptr;
        }
        else nodptr_TmpPrev->nodptr_Next = nodptr_TmpCurr->nodptr_Next;

        delete nodptr_TmpCurr;

        int_NodCount--;
    }

    return bl_IsSuccess;
}

template <typename Type>
Singly_Circular_Linked_List<Type>::Singly_Circular_Linked_List()
{
    nodptr_Start = nodptr_Curr = nullptr;
    int_NodCount = 0;
}

template <typename Type>
Singly_Circular_Linked_List<Type>::~Singly_Circular_Linked_List()
{
    for(Singly_Node<Type>* nodptr_Temp1 = nodptr_Start; nodptr_Temp1 != nullptr;)
    {
        Singly_Node<Type>* nodptr_Temp2 = nodptr_Temp1->nodptr_Next;
        delete nodptr_Temp1;
        nodptr_Temp1 = nodptr_Temp2;
    }
}

template <typename Type>
void Singly_Circular_Linked_List<Type>::fn_AddNode(Type typ_Field)
{
    Singly_Node<Type>* nodptr_Ele = new Singly_Node<Type>(typ_Field);

    if(int_NodCount == 0) nodptr_Start = nodptr_Curr = nodptr_Ele;
    else
    {
        nodptr_Ele->nodptr_Next = nodptr_Start;
        nodptr_Curr->nodptr_Next = nodptr_Ele;
        nodptr_Curr = nodptr_Ele;
    }

    int_NodCount++;
}

template <typename Type>
void Singly_Circular_Linked_List<Type>::fn_Trace()
{
    std::cout<< "start -> ";

    int i = 0;

    for(Singly_Node<Type>* nodptr_Temp = nodptr_Start; i < int_NodCount; nodptr_Temp = nodptr_Temp->nodptr_Next, i++)
    {
        std::cout<< nodptr_Temp->typ_Field << " -> ";
    }

    std::cout<< " start\n";
}

template <typename Type>
void Singly_Circular_Linked_List<Type>::fn_Insert(int int_Idx, Type typ_Field)
{
    Singly_Node<Type>* nodptr_Input = new Singly_Node<Type>(typ_Field);

    if(int_Idx == 0)
    {
        nodptr_Input->nodptr_Next = nodptr_Start;
        nodptr_Start = nodptr_Input;
    }
    else
    {
        Singly_Node<Type>* nodptr_Temp = nodptr_Start;

        while(--int_Idx)
        {
            nodptr_Temp = nodptr_Temp->nodptr_Next;
        }

        if(nodptr_Temp->nodptr_Next == nodptr_Start)nodptr_Input->nodptr_Next = nodptr_Start;
        else nodptr_Input->nodptr_Next = nodptr_Temp->nodptr_Next;

        nodptr_Temp->nodptr_Next = nodptr_Input;
    }

    int_NodCount++;
}

template <typename Type>
void Singly_Circular_Linked_List<Type>::fn_Renew(int int_Idx, Type typ_Field)
{
    Singly_Node<Type>* nodptr_Temp = nodptr_Start;

    while(int_Idx--)
    {
        nodptr_Temp = nodptr_Temp->nodptr_Next;
    }

    nodptr_Temp->typ_Field = typ_Field;
}

template <typename Type>
bool Singly_Circular_Linked_List<Type>::fn_DelNode(int int_Idx)
{
    bool bl_IsSuccess = true;

    if(int_Idx > int_NodCount - 1) bl_IsSuccess = false;
    else
    {
        Singly_Node<Type>* nodptr_TmpCurr = nodptr_Start;
        Singly_Node<Type>* nodptr_TmpPrev = nodptr_Start;

        for(int i = 1; i < int_Idx + 1; i++)
        {
            nodptr_TmpPrev = nodptr_TmpCurr;
            nodptr_TmpCurr = nodptr_TmpCurr->nodptr_Next;
        }

        if(int_Idx == 0)
        {
            nodptr_Start = nodptr_Start->nodptr_Next;
            nodptr_Curr = nullptr;
        }
        else if(int_Idx == int_NodCount - 1 && int_Idx != 0)
        {
            nodptr_Curr = nodptr_TmpPrev;
            nodptr_TmpPrev->nodptr_Next = nullptr;
        }
        else nodptr_TmpPrev->nodptr_Next = nodptr_TmpCurr->nodptr_Next;

        delete nodptr_TmpCurr;

        int_NodCount--;
    }

    return bl_IsSuccess;
}

template <typename Type>
Doubly_Node<Type>::Doubly_Node(Type typ_Field)
{
    this->typ_Field = typ_Field;
    nodptr_Next = nodptr_Prev = nullptr;
}

template <typename Type>
Doubly_Linked_List<Type>::Doubly_Linked_List()
{
    nodptr_Start = nodptr_End = nullptr;
    int_NodCount = 0;
}

template <typename Type>
Doubly_Linked_List<Type>::~Doubly_Linked_List()
{
    for(Doubly_Node<Type>* nodptr_Curr = nodptr_Start; nodptr_Curr != nullptr;)
    {
        Doubly_Node<Type>* nodptr_Temp = nodptr_Curr->nodptr_Next;

        delete nodptr_Curr;

        nodptr_Curr = nodptr_Temp;
    }
}

template <typename Type>
void Doubly_Linked_List<Type>::fn_Trace()
{
    std::cout<< "(nullptr->)start->";

    for(Doubly_Node<Type>* nodptr_Curr = nodptr_Start; nodptr_Curr != nullptr; nodptr_Curr = nodptr_Curr->nodptr_Next)
    {
        std::cout<< nodptr_Curr->typ_Field << "->";
    }

    std::cout<< "nullptr\n";
}

template <typename Type>
void Doubly_Linked_List<Type>::fn_AddNode(Type typ_Field)
{
    Doubly_Node<Type>* nodptr_Elem = new Doubly_Node<Type>(typ_Field);

    if(nodptr_Start == nullptr)
    {
        nodptr_Elem->nodptr_Prev = nullptr;
        nodptr_Start = nodptr_Elem;
        nodptr_End = nodptr_Elem;
    }
    else
    {
        nodptr_Elem->nodptr_Prev = nodptr_End;
        nodptr_End->nodptr_Next = nodptr_Elem;
        nodptr_End = nodptr_Elem;
    }

    int_NodCount++;
}

template <typename Type>
void Doubly_Linked_List<Type>::fn_UpdNode(int int_Idx, Type typ_Field)
{
    Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

    for(; int_Idx > 0; int_Idx--)
    {
        nodptr_Curr = nodptr_Curr->nodptr_Next;
    }

    nodptr_Curr->typ_Field = typ_Field;
}

template <typename Type>
void Doubly_Linked_List<Type>::fn_InsNode(int int_Idx, Type typ_Field)
{
    Doubly_Node<Type>* nodptr_Elem = new Doubly_Node<Type>(typ_Field);

    if(int_Idx == 0)
    {
        nodptr_Start->nodptr_Prev = nodptr_Elem;
        nodptr_Elem->nodptr_Next = nodptr_Start;
        nodptr_Start = nodptr_Elem;
    }
    else
    {
        Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

        if(int_Idx < int_NodCount / 2)
        {
            for(int i = 0; i < int_Idx; i++)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Next;
            }
        }
        else
        {
            nodptr_Curr = nodptr_End;

            for(int i = int_NodCount - 1; i > int_Idx; i--)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Prev;
            }
        }

        nodptr_Curr->nodptr_Prev->nodptr_Next = nodptr_Elem;
        nodptr_Elem->nodptr_Prev = nodptr_Curr->nodptr_Prev;
        nodptr_Elem->nodptr_Next = nodptr_Curr;
        nodptr_Curr->nodptr_Prev = nodptr_Elem;
    }

    int_NodCount++;
}

template <typename Type>
bool Doubly_Linked_List<Type>::fn_DelNode(int int_Idx)
{
    bool bl_IsSuccess = true;

    if(int_Idx > int_NodCount - 1) bl_IsSuccess = false;
    else
    {
        Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

        if(int_Idx < int_NodCount / 2)
        {
            for(int i = 0; i < int_Idx; i++)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Next;
            }
        }
        else
        {
            nodptr_Curr = nodptr_End;

            for(int i = int_NodCount; i > int_Idx; i--)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Prev;
            }
        }

        if(int_Idx == 0)
        {
            nodptr_Start = nodptr_Start->nodptr_Next;
            nodptr_Start->nodptr_Prev = nullptr;

            if(int_NodCount == 1) nodptr_End = nullptr;
        }
        else if(int_Idx == int_NodCount -1) nodptr_End = nodptr_Curr->nodptr_Prev;
        else
        {
            nodptr_Curr->nodptr_Prev->nodptr_Next = nodptr_Curr->nodptr_Next;
            nodptr_Curr->nodptr_Next->nodptr_Prev = nodptr_Curr->nodptr_Prev;
        }

        delete nodptr_Curr;

        int_NodCount--;
    }

    return bl_IsSuccess;
}

template <typename Type>
Doubly_Circular_Linked_List<Type>::Doubly_Circular_Linked_List()
{
    nodptr_Start = nodptr_End = nullptr;
    int_NodCount = 0;
}

template <typename Type>
Doubly_Circular_Linked_List<Type>::~Doubly_Circular_Linked_List()
{
    for(Doubly_Node<Type>* nodptr_Curr = nodptr_Start; nodptr_Curr != nodptr_End;)
    {
        Doubly_Node<Type>* nodptr_Temp = nodptr_Curr->nodptr_Next;

        delete nodptr_Curr;

        nodptr_Curr = nodptr_Temp;
    }

    delete nodptr_End;
}

template <typename Type>
void Doubly_Circular_Linked_List<Type>::fn_Trace()
{
    if(int_NodCount == 0)
    {
        std::cerr<< "This list is empty.\n";

        return;
    }

    std::cout<< "start -> ";

    for(Doubly_Node<Type>* nodptr_Curr = nodptr_Start; nodptr_Curr != nodptr_End; nodptr_Curr = nodptr_Curr->nodptr_Next)
    {
        std::cout<< nodptr_Curr->typ_Field << " -> ";
    }

    std::cout<< nodptr_End->typ_Field << " -> start\n";
}

template <typename Type>
void Doubly_Circular_Linked_List<Type>::fn_AddNode(Type typ_Field)
{
    Doubly_Node<Type>* nodptr_Elem = new Doubly_Node<Type>(typ_Field);

    if(int_NodCount == 0)
    {
        nodptr_Start = nodptr_End = nodptr_Elem;
        nodptr_Elem->nodptr_Next = nodptr_Elem->nodptr_Prev = nodptr_Elem;
    }
    else
    {
        nodptr_Start->nodptr_Prev = nodptr_End->nodptr_Next = nodptr_Elem;
        nodptr_Elem->nodptr_Next = nodptr_Start;
        nodptr_Elem->nodptr_Prev = nodptr_End;
        nodptr_End = nodptr_Elem;
    }

    int_NodCount++;
}

template <typename Type>
void Doubly_Circular_Linked_List<Type>::fn_UpdNode(int int_Idx, Type typ_Field)
{
    Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

    if(int_Idx < int_NodCount / 2)
    {
        for(int i = 0; i < int_Idx; i++)
        {
            nodptr_Curr = nodptr_Curr->nodptr_Next;
        }
    }
    else
    {
        nodptr_Curr = nodptr_End;

        for(int i = int_NodCount - 1; i > int_Idx; i--)
        {
            nodptr_Curr = nodptr_Curr->nodptr_Prev;
        }
    }

    nodptr_Curr->typ_Field = typ_Field;
}

template <typename Type>
void Doubly_Circular_Linked_List<Type>::fn_InsNode(int int_Idx, Type typ_Field)
{
    Doubly_Node<Type>* nodptr_Elem = new Doubly_Node<Type>(typ_Field);

    if(int_Idx == 0)
    {
        nodptr_Elem->nodptr_Next = nodptr_Start;
        nodptr_Elem->nodptr_Prev = nodptr_End;
        nodptr_Start->nodptr_Prev = nodptr_End->nodptr_Next = nodptr_Elem;
        nodptr_Start = nodptr_Elem;
    }
    else if(int_Idx >= int_NodCount)
    {
        std::cerr<< "This linked list just has " << int_NodCount << " elements!\n";

        return;
    }
    else
    {
        Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

        if(int_Idx < int_NodCount / 2)
        {
            for(int i = 0; i < int_Idx; i++)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Next;
            }
        }
        else
        {
            nodptr_Curr = nodptr_End;

            for(int i = int_NodCount - 1; i > int_Idx; i--)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Prev;
            }
        }

        nodptr_Elem->nodptr_Prev = nodptr_Curr->nodptr_Prev;
        nodptr_Elem->nodptr_Next = nodptr_Curr;
        nodptr_Curr->nodptr_Prev = nodptr_Curr->nodptr_Prev->nodptr_Next = nodptr_Elem;
    }

    int_NodCount++;
}

template <typename Type>
bool Doubly_Circular_Linked_List<Type>::fn_DelNode(int int_Idx)
{
    bool bl_IsSuccess = true;

    if(int_Idx > int_NodCount - 1) bl_IsSuccess = false;
    else
    {
        Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

        if(int_Idx < int_NodCount / 2)
        {
            for(int i = 0; i < int_Idx; i++)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Next;
            }
        }
        else
        {
            nodptr_Curr = nodptr_End;

            for(int i = int_NodCount; i > int_Idx; i--)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Prev;
            }
        }

        if(int_Idx == 0)
        {
            nodptr_Start = nodptr_Start->nodptr_Next;
            nodptr_Start->nodptr_Prev = nullptr;

            if(int_NodCount == 1) nodptr_End = nullptr;
        }
        else if(int_Idx == int_NodCount -1) nodptr_End = nodptr_Curr->nodptr_Prev;
        else
        {
            nodptr_Curr->nodptr_Prev->nodptr_Next = nodptr_Curr->nodptr_Next;
            nodptr_Curr->nodptr_Next->nodptr_Prev = nodptr_Curr->nodptr_Prev;
        }

        delete nodptr_Curr;

        int_NodCount--;
    }

    return bl_IsSuccess;
}
