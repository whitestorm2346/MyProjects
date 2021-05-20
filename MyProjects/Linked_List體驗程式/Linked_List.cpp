#include <iostream>
#include <string>

#define int_CmdCount 14

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

void fn_SetCmd(std::string *strarr_Cmd);
void fn_ShowAllCmd(std::string *strarr_Cmd);
void fn_RunCmd(std::string str_Input);

int main()
{
    std::string str_Input, str_Cmd[int_CmdCount];

    std::cout<< "[system] Use command \"/help\" to check all commands.\n\n";

    fn_SetCmd(str_Cmd);

    while(std::cin>> str_Input)
    {
        if(str_Input == "/end") break;
        else if(str_Input == "/help") fn_ShowAllCmd(str_Cmd);
        else fn_RunCmd(str_Input);

        std::cout<< '\n';
    }

    std::cout<< "\n[system] End up successfully.\n";

    return 0;
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
    strarr_Cmd[10] = "/ptr_to_next";
    strarr_Cmd[11] = "/ptr_to_prev";
    strarr_Cmd[12] = "/del_ptr";
    strarr_Cmd[13] = "/end";
}

void fn_ShowAllCmd(std::string *strarr_Cmd)
{
    std::cout<< '\n';

    for(int i = 0; i < int_CmdCount; i++)
    {
        std::cout<< strarr_Cmd[i] << '\n';
    }
}

void fn_RunCmd(std::string str_Input)
{
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
