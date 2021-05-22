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

    void fn_Add(Type typ_Field);
    void fn_ElemTrace();
    void fn_AdrsTrace();
    void fn_Insert(int int_Idx, Type typ_Field);
    void fn_Modify(int int_Idx, Type typ_Field);
    bool fn_Del(int int_Idx);
    Type fn_GetElem(int int_Idx);
    Singly_Node<Type>* fn_GetAdrs(int int_Idx);
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

    void fn_Add(Type typ_Field);
    void fn_ElemTrace();
    void fn_AdrsTrace();
    void fn_Insert(int int_Idx, Type typ_Field);
    void fn_Modify(int int_Idx, Type typ_Field);
    bool fn_Del(int int_Idx);
    Type fn_GetElem(int int_Idx);
    Singly_Node<Type>* fn_GetAdrs(int int_Idx);
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

    void fn_ElemTrace();
    void fn_AdrsTrace();
    void fn_Add(Type typ_Field);
    void fn_Modify(int int_Idx, Type typ_Field);
    void fn_Insert(int int_Idx, Type typ_Field);
    bool fn_Del(int int_Idx);
    Type fn_GetElem(int int_Idx);
    Doubly_Node<Type>* fn_GetAdrs(int int_Idx);
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

    void fn_ElemTrace();
    void fn_AdrsTrace();
    void fn_Add(Type typ_Field);
    void fn_Modify(int int_Idx, Type typ_Field);
    void fn_Insert(int int_Idx, Type typ_Field);
    bool fn_Del(int int_Idx);
    Type fn_GetElem(int int_Idx);
    Doubly_Node<Type>* fn_GetAdrs(int int_Idx);
};

struct Command
{
    std::string str_CmdName;
    std::string str_CmdIntro;
};

void fn_SetLinkedList(int &int_Case);
void fn_SetCmd(Command *cmd_Arr);
void fn_ShowAllCmd(Command *cmd_Arr);
void fn_RunCmd(std::string str_Input, int int_Case);

Singly_Linked_List<int>* sll_ptr = nullptr;
Doubly_Linked_List<int>* dll_ptr = nullptr;
Singly_Circular_Linked_List<int>* scll_ptr = nullptr;
Doubly_Circular_Linked_List<int>* dcll_ptr = nullptr;
Singly_Node<int>* snodptr_Curr = nullptr;
Doubly_Node<int>* dnodptr_Curr = nullptr;

int main()
{
    Command cmd_Arr[int_CmdCount];
    std::string str_Input;
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

    std::cout<< "[system] Now you can use command \"/help\" to check all the commands.\n\n";

    fn_SetCmd(cmd_Arr);

    while(std::cin>> str_Input)
    {
        if(str_Input == "/end") break;
        else if(str_Input == "/help") fn_ShowAllCmd(cmd_Arr);
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

void fn_SetCmd(Command *cmd_Arr)
{
    cmd_Arr[0].str_CmdName  = "/add";
    cmd_Arr[0].str_CmdIntro = "Add a new node into the linked list.";

    cmd_Arr[1].str_CmdName  = "/del";
    cmd_Arr[1].str_CmdIntro = "Delete a node from the linked list.";

    cmd_Arr[2].str_CmdName  = "/modify";
    cmd_Arr[2].str_CmdIntro = "Modify the element of the chosen node.";

    cmd_Arr[3].str_CmdName  = "/insert";
    cmd_Arr[3].str_CmdIntro = "Insert a new node into the linked list at a chosen position.";

    cmd_Arr[4].str_CmdName  = "/get_elem";
    cmd_Arr[4].str_CmdIntro = "Return the element of the chosen node.";

    cmd_Arr[5].str_CmdName  = "/get_adrs";
    cmd_Arr[5].str_CmdIntro = "Return the address of the chosen node.";

    cmd_Arr[6].str_CmdName  = "/elem_trace";
    cmd_Arr[6].str_CmdIntro = "Output all the elements of the nodes in linked list.";

    cmd_Arr[7].str_CmdName  = "/adrs_trace";
    cmd_Arr[7].str_CmdIntro = "Output all the addresses of the nodes in linked list.";

    cmd_Arr[8].str_CmdName  = "/create_ptr";
    cmd_Arr[8].str_CmdIntro = "Create a pointer to point out one node in the linked list.";

    cmd_Arr[9].str_CmdName  = "/get_curr_elem";
    cmd_Arr[9].str_CmdIntro = "Return the element of the pointed node.";

    cmd_Arr[10].str_CmdName  = "/get_curr_adrs";
    cmd_Arr[10].str_CmdIntro = "Return the address of the pointed node.";

    cmd_Arr[11].str_CmdName  = "/ptr_to_next";
    cmd_Arr[11].str_CmdIntro = "Move the pointer to the next node.";

    cmd_Arr[12].str_CmdName  = "/ptr_to_prev";
    cmd_Arr[12].str_CmdIntro = "Move the pointer to the previous node.";

    cmd_Arr[13].str_CmdName  = "/del_ptr";
    cmd_Arr[13].str_CmdIntro = "Delete the pointer.";

    cmd_Arr[14].str_CmdName  = "/end";
    cmd_Arr[14].str_CmdIntro = "End up the program.";
}

void fn_ShowAllCmd(Command *cmd_Arr)
{
    std::cout<< '\n';

    for(int i = 0; i < int_CmdCount; i++)
    {
        std::cout<< "[system] " << cmd_Arr[i].str_CmdName << '\n';
        std::cout<< "[system] " << cmd_Arr[i].str_CmdIntro << "\n\n";
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
            case SINGLY_LINKED_LIST: sll_ptr->fn_Add(int_Num); return;
            case DOUBLY_LINKED_LIST: dll_ptr->fn_Add(int_Num); return;
            case SINGLY_CIRCULAR_LINKED_LIST: scll_ptr->fn_Add(int_Num); return;
            case DOUBLY_CIRCULAR_LINKED_LIST: dcll_ptr->fn_Add(int_Num); return;
        }
    }
    else if(str_Input == "/del")
    {
        int int_Idx;

        std::cout<< "[system] Input an index number.\n";
        std::cin>> int_Idx;

        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: sll_ptr->fn_Del(int_Idx); return;
            case DOUBLY_LINKED_LIST: dll_ptr->fn_Del(int_Idx); return;
            case SINGLY_CIRCULAR_LINKED_LIST: scll_ptr->fn_Del(int_Idx); return;
            case DOUBLY_CIRCULAR_LINKED_LIST: dcll_ptr->fn_Del(int_Idx); return;
        }
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
            case SINGLY_LINKED_LIST: sll_ptr->fn_Modify(int_Idx, int_NewNum); return;
            case DOUBLY_LINKED_LIST: dll_ptr->fn_Modify(int_Idx, int_NewNum); return;
            case SINGLY_CIRCULAR_LINKED_LIST: scll_ptr->fn_Modify(int_Idx, int_NewNum); return;
            case DOUBLY_CIRCULAR_LINKED_LIST: dcll_ptr->fn_Modify(int_Idx, int_NewNum); return;
        }
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
            case SINGLY_LINKED_LIST: sll_ptr->fn_Insert(int_Idx, int_Num); return;
            case DOUBLY_LINKED_LIST: dll_ptr->fn_Insert(int_Idx, int_Num); return;
            case SINGLY_CIRCULAR_LINKED_LIST: scll_ptr->fn_Insert(int_Idx, int_Num); return;
            case DOUBLY_CIRCULAR_LINKED_LIST: dcll_ptr->fn_Insert(int_Idx, int_Num); return;
        }
    }
    else if(str_Input == "/get_elem")
    {
        int int_Idx;

        std::cout<< "[system] Input an index number.\n";
        std::cin>> int_Idx;

        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: std::cout<< "[system] " << sll_ptr->fn_GetElem(int_Idx) << '\n'; return;
            case DOUBLY_LINKED_LIST: std::cout<< "[system] " << dll_ptr->fn_GetElem(int_Idx) << '\n'; return;
            case SINGLY_CIRCULAR_LINKED_LIST: std::cout<< "[system] " << scll_ptr->fn_GetElem(int_Idx) << '\n'; return;
            case DOUBLY_CIRCULAR_LINKED_LIST: std::cout<< "[system] " << dcll_ptr->fn_GetElem(int_Idx) << '\n'; return;
        }
    }
    else if(str_Input == "/get_adrs")
    {
        int int_Idx;

        std::cout<< "[system] Input an index number.\n";
        std::cin>> int_Idx;

        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: std::cout<< "[system] " << sll_ptr->fn_GetAdrs(int_Idx) << '\n'; return;
            case DOUBLY_LINKED_LIST: std::cout<< "[system] " << dll_ptr->fn_GetAdrs(int_Idx) << '\n'; return;
            case SINGLY_CIRCULAR_LINKED_LIST: std::cout<< "[system] " << scll_ptr->fn_GetAdrs(int_Idx) << '\n'; return;
            case DOUBLY_CIRCULAR_LINKED_LIST: std::cout<< "[system] " << dcll_ptr->fn_GetAdrs(int_Idx) << '\n'; return;
        }
    }
    else if(str_Input == "/elem_trace")
    {
        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: sll_ptr->fn_ElemTrace(); return;
            case DOUBLY_LINKED_LIST: dll_ptr->fn_ElemTrace(); return;
            case SINGLY_CIRCULAR_LINKED_LIST: scll_ptr->fn_ElemTrace(); return;
            case DOUBLY_CIRCULAR_LINKED_LIST: dcll_ptr->fn_ElemTrace(); return;
        }
    }
    else if(str_Input == "/adrs_trace")
    {
        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: sll_ptr->fn_AdrsTrace(); return;
            case DOUBLY_LINKED_LIST: dll_ptr->fn_AdrsTrace(); return;
            case SINGLY_CIRCULAR_LINKED_LIST: scll_ptr->fn_AdrsTrace(); return;
            case DOUBLY_CIRCULAR_LINKED_LIST: dcll_ptr->fn_AdrsTrace(); return;
        }
    }
    else if(str_Input == "/create_ptr")
    {
        if((int_Case == 1 || int_Case == 3) && snodptr_Curr != nullptr)
        {
            std::cerr<< "[system] You have already created a pointer.\n";

            return;
        }
        else if((int_Case == 2 || int_Case == 4) && dnodptr_Curr != nullptr)
        {
            std::cerr<< "[system] You have already created a pointer.\n";

            return;
        }

        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: snodptr_Curr = sll_ptr->nodptr_Start; break;
            case DOUBLY_LINKED_LIST: dnodptr_Curr = dll_ptr->nodptr_Start; break;
            case SINGLY_CIRCULAR_LINKED_LIST: snodptr_Curr = scll_ptr->nodptr_Start; break;
            case DOUBLY_CIRCULAR_LINKED_LIST: dnodptr_Curr = dcll_ptr->nodptr_Start; break;
        }

        std::cout<< "[system] Pointer created successfully.\n";

        return;
    }
    else if(str_Input == "/get_curr_elem")
    {
        if((int_Case == 1 || int_Case == 3) && snodptr_Curr == nullptr)
        {
            std::cerr<< "[system] You haven\'t create a pointer.\n";

            return;
        }
        else if((int_Case == 2 || int_Case == 4) && dnodptr_Curr == nullptr)
        {
            std::cerr<< "[system] You haven\'t create a pointer.\n";

            return;
        }

        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: case SINGLY_CIRCULAR_LINKED_LIST: std::cout<< "[system] " << snodptr_Curr->typ_Field << '\n'; return;
            case DOUBLY_LINKED_LIST: case DOUBLY_CIRCULAR_LINKED_LIST: std::cout<< "[system] " << dnodptr_Curr->typ_Field << '\n'; return;
        }
    }
    else if(str_Input == "/get_curr_adrs")
    {
        if((int_Case == 1 || int_Case == 3) && snodptr_Curr == nullptr)
        {
            std::cerr<< "[system] You haven\'t create a pointer.\n";

            return;
        }
        else if((int_Case == 2 || int_Case == 4) && dnodptr_Curr == nullptr)
        {
            std::cerr<< "[system] You haven\'t create a pointer.\n";

            return;
        }

        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: case SINGLY_CIRCULAR_LINKED_LIST: std::cout<< "[system] " << snodptr_Curr << '\n'; return;
            case DOUBLY_LINKED_LIST: case DOUBLY_CIRCULAR_LINKED_LIST: std::cout<< "[system] " << dnodptr_Curr << '\n'; return;
        }
    }
    else if(str_Input == "/ptr_to_next")
    {
        if((int_Case == 1 || int_Case == 3) && snodptr_Curr == nullptr)
        {
            std::cerr<< "[system] You haven\'t create a pointer.\n";

            return;
        }
        else if((int_Case == 2 || int_Case == 4) && dnodptr_Curr == nullptr)
        {
            std::cerr<< "[system] You haven\'t create a pointer.\n";

            return;
        }

        switch(int_Case)
        {
            case SINGLY_LINKED_LIST:
                if(snodptr_Curr->nodptr_Next == nullptr) std::cout<< "[system] This is the last position of the linked list.\n";
                else snodptr_Curr = snodptr_Curr->nodptr_Next; return;

            case DOUBLY_LINKED_LIST:
                if(dnodptr_Curr->nodptr_Next == nullptr) std::cout<< "[system] This is the last position of the linked list.\n";
                else dnodptr_Curr = dnodptr_Curr->nodptr_Next; return;

            case SINGLY_CIRCULAR_LINKED_LIST: snodptr_Curr = snodptr_Curr->nodptr_Next; break;
            case DOUBLY_CIRCULAR_LINKED_LIST: dnodptr_Curr = dnodptr_Curr->nodptr_Next; break;
        }

        std::cout<< "[system] Pointer is moving to the next node.\n";

        return;
    }
    else if(str_Input == "/ptr_to_prev")
    {
        if(int_Case == 1 || int_Case == 3)
        {
            std::cout<< "[system] Pointer of singly node cannot move to previous node.\n";

            return;
        }
        else if((int_Case == 2 || int_Case == 4) && dnodptr_Curr == nullptr)
        {
            std::cout<< "[system] You haven\'t create a pointer.\n";

            return;
        }

        switch(int_Case)
        {
            case DOUBLY_LINKED_LIST:
                if(dnodptr_Curr->nodptr_Prev == nullptr) std::cout<< "[system] This is the First position of the linked list.\n";
                else dnodptr_Curr = dnodptr_Curr->nodptr_Prev; return;

            case DOUBLY_CIRCULAR_LINKED_LIST: dnodptr_Curr = dnodptr_Curr->nodptr_Prev; break;
        }

        std::cout<< "[system] Pointer is moving to the previous node.\n";

        return;
    }
    else if(str_Input == "/del_ptr")
    {
        if((int_Case == 1 || int_Case == 3) && snodptr_Curr == nullptr)
        {
            std::cerr<< "[system] You haven\'t create a pointer.\n";

            return;
        }
        else if((int_Case == 2 || int_Case == 4) && dnodptr_Curr == nullptr)
        {
            std::cerr<< "[system] You haven\'t create a pointer.\n";

            return;
        }

        switch(int_Case)
        {
            case SINGLY_LINKED_LIST: case SINGLY_CIRCULAR_LINKED_LIST: snodptr_Curr = nullptr; break;
            case DOUBLY_LINKED_LIST: case DOUBLY_CIRCULAR_LINKED_LIST: dnodptr_Curr = nullptr; break;
        }

        std::cout<< "[system] Deleted successfully.\n";

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
void Singly_Linked_List<Type>::fn_Add(Type typ_Field)
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
void Singly_Linked_List<Type>::fn_ElemTrace()
{
    if(int_NodCount == 0)
    {
        std::cerr<< "[system] This linked list is empty.\n";

        return;
    }

    std::cout<< "start -> ";

    for(Singly_Node<Type>* nodptr_Temp = nodptr_Start; nodptr_Temp != nullptr; nodptr_Temp = nodptr_Temp->nodptr_Next)
    {
        std::cout<< nodptr_Temp->typ_Field << " -> ";
    }

    std::cout<< " nullptr\n";
}

template <typename Type>
void Singly_Linked_List<Type>::fn_AdrsTrace()
{
    if(int_NodCount == 0)
    {
        std::cerr<< "[system] This linked list is empty.\n";

        return;
    }

    std::cout<< "start -> ";

    for(Singly_Node<Type>* nodptr_Temp = nodptr_Start; nodptr_Temp != nullptr; nodptr_Temp = nodptr_Temp->nodptr_Next)
    {
        std::cout<< nodptr_Temp << " -> ";
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
void Singly_Linked_List<Type>::fn_Modify(int int_Idx, Type typ_Field)
{
    Singly_Node<Type>* nodptr_Temp = nodptr_Start;

    while(int_Idx--)
    {
        nodptr_Temp = nodptr_Temp->nodptr_Next;
    }

    nodptr_Temp->typ_Field = typ_Field;
}

template <typename Type>
bool Singly_Linked_List<Type>::fn_Del(int int_Idx)
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
Type Singly_Linked_List<Type>::fn_GetElem(int int_Idx)
{
    Singly_Node<Type>* nodptr_Temp = nodptr_Start;

    while(int_Idx--)
    {
        nodptr_Temp = nodptr_Temp->nodptr_Next;
    }

    return nodptr_Temp->typ_Field;
}

template <typename Type>
Singly_Node<Type>* Singly_Linked_List<Type>::fn_GetAdrs(int int_Idx)
{
    Singly_Node<Type>* nodptr_Temp = nodptr_Start;

    while(int_Idx--)
    {
        nodptr_Temp = nodptr_Temp->nodptr_Next;
    }

    return nodptr_Temp;
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
void Singly_Circular_Linked_List<Type>::fn_Add(Type typ_Field)
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
void Singly_Circular_Linked_List<Type>::fn_ElemTrace()
{
    if(int_NodCount == 0)
    {
        std::cerr<< "[system] This linked list is empty.\n";

        return;
    }

    std::cout<< "start -> ";

    int i = 0;

    for(Singly_Node<Type>* nodptr_Temp = nodptr_Start; i < int_NodCount; nodptr_Temp = nodptr_Temp->nodptr_Next, i++)
    {
        std::cout<< nodptr_Temp->typ_Field << " -> ";
    }

    std::cout<< " start\n";
}

template <typename Type>
void Singly_Circular_Linked_List<Type>::fn_AdrsTrace()
{
    if(int_NodCount == 0)
    {
        std::cerr<< "[system] This linked list is empty.\n";

        return;
    }

    std::cout<< "start -> ";

    int i = 0;

    for(Singly_Node<Type>* nodptr_Temp = nodptr_Start; i < int_NodCount; nodptr_Temp = nodptr_Temp->nodptr_Next, i++)
    {
        std::cout<< nodptr_Temp << " -> ";
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
void Singly_Circular_Linked_List<Type>::fn_Modify(int int_Idx, Type typ_Field)
{
    Singly_Node<Type>* nodptr_Temp = nodptr_Start;

    while(int_Idx--)
    {
        nodptr_Temp = nodptr_Temp->nodptr_Next;
    }

    nodptr_Temp->typ_Field = typ_Field;
}

template <typename Type>
bool Singly_Circular_Linked_List<Type>::fn_Del(int int_Idx)
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
Type Singly_Circular_Linked_List<Type>::fn_GetElem(int int_Idx)
{
    Singly_Node<Type>* nodptr_Temp = nodptr_Start;

    while(int_Idx--)
    {
        nodptr_Temp = nodptr_Temp->nodptr_Next;
    }

    return nodptr_Temp->typ_Field;
}

template <typename Type>
Singly_Node<Type>* Singly_Circular_Linked_List<Type>::fn_GetAdrs(int int_Idx)
{
    Singly_Node<Type>* nodptr_Temp = nodptr_Start;

    while(int_Idx--)
    {
        nodptr_Temp = nodptr_Temp->nodptr_Next;
    }

    return nodptr_Temp;
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
void Doubly_Linked_List<Type>::fn_ElemTrace()
{
    if(int_NodCount == 0)
    {
        std::cerr<< "[system] This linked list is empty.\n";

        return;
    }

    std::cout<< "(nullptr->)start->";

    for(Doubly_Node<Type>* nodptr_Curr = nodptr_Start; nodptr_Curr != nullptr; nodptr_Curr = nodptr_Curr->nodptr_Next)
    {
        std::cout<< nodptr_Curr->typ_Field << "->";
    }

    std::cout<< "nullptr\n";
}

template <typename Type>
void Doubly_Linked_List<Type>::fn_AdrsTrace()
{
    if(int_NodCount == 0)
    {
        std::cerr<< "[system] This linked list is empty.\n";

        return;
    }

    std::cout<< "(nullptr->)start->";

    for(Doubly_Node<Type>* nodptr_Curr = nodptr_Start; nodptr_Curr != nullptr; nodptr_Curr = nodptr_Curr->nodptr_Next)
    {
        std::cout<< nodptr_Curr << "->";
    }

    std::cout<< "nullptr\n";
}

template <typename Type>
void Doubly_Linked_List<Type>::fn_Add(Type typ_Field)
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
void Doubly_Linked_List<Type>::fn_Modify(int int_Idx, Type typ_Field)
{
    Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

    while(int_Idx--)
    {
        nodptr_Curr = nodptr_Curr->nodptr_Next;
    }

    nodptr_Curr->typ_Field = typ_Field;
}

template <typename Type>
void Doubly_Linked_List<Type>::fn_Insert(int int_Idx, Type typ_Field)
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
bool Doubly_Linked_List<Type>::fn_Del(int int_Idx)
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
Type Doubly_Linked_List<Type>::fn_GetElem(int int_Idx)
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

    return nodptr_Curr->typ_Field;
}

template <typename Type>
Doubly_Node<Type>* Doubly_Linked_List<Type>::fn_GetAdrs(int int_Idx)
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

    return nodptr_Curr;
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
void Doubly_Circular_Linked_List<Type>::fn_ElemTrace()
{
    if(int_NodCount == 0)
    {
        std::cerr<< "[system] This linked list is empty.\n";

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
void Doubly_Circular_Linked_List<Type>::fn_AdrsTrace()
{
    if(int_NodCount == 0)
    {
        std::cerr<< "[system] This linked list is empty.\n";

        return;
    }

    std::cout<< "start -> ";

    for(Doubly_Node<Type>* nodptr_Curr = nodptr_Start; nodptr_Curr != nodptr_End; nodptr_Curr = nodptr_Curr->nodptr_Next)
    {
        std::cout<< nodptr_Curr << " -> ";
    }

    std::cout<< nodptr_End->typ_Field << " -> start\n";
}

template <typename Type>
void Doubly_Circular_Linked_List<Type>::fn_Add(Type typ_Field)
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
void Doubly_Circular_Linked_List<Type>::fn_Modify(int int_Idx, Type typ_Field)
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
void Doubly_Circular_Linked_List<Type>::fn_Insert(int int_Idx, Type typ_Field)
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
bool Doubly_Circular_Linked_List<Type>::fn_Del(int int_Idx)
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
Type Doubly_Circular_Linked_List<Type>::fn_GetElem(int int_Idx)
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

    return nodptr_Curr->typ_Field;
}

template <typename Type>
Doubly_Node<Type>* Doubly_Circular_Linked_List<Type>::fn_GetAdrs(int int_Idx)
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

    return nodptr_Curr;
}
