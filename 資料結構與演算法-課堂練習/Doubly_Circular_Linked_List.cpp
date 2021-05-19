#include <iostream>

template <typename Type>
class Node
{
public:
    Type typ_Field;
    Node* nodptr_Next;
    Node* nodptr_Prev;

    Node(Type typ_Field);
};

template<typename Type>
class Doubly_Circular_Linked_List
{
private:
    int int_NodCount;

public:
    Node<Type>* nodptr_Start;
    Node<Type>* nodptr_End;

    Doubly_Circular_Linked_List();
    ~Doubly_Circular_Linked_List();

    void fn_Trace();
    void fn_AddNode(Type typ_Field);
    void fn_UpdNode(int int_Idx, Type typ_Field);
    void fn_InsNode(int int_Idx, Type typ_Field);

    bool fn_DelNode(int int_Idx = 0)
    {
        bool bl_IsSuccess = true;

        if(int_Idx > int_NodCount - 1) bl_IsSuccess = false;
        else
        {
            Node<Type>* nodptr_Curr = nodptr_Start;

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
};

int main()
{
    Doubly_Circular_Linked_List<int> dll_List;

    dll_List.fn_AddNode(3);
    dll_List.fn_AddNode(7);
    dll_List.fn_AddNode(6);
    dll_List.fn_AddNode(4);
    dll_List.fn_AddNode(2);
    dll_List.fn_AddNode(8);
    dll_List.fn_AddNode(1);

    dll_List.fn_Trace();

    dll_List.fn_InsNode(2, 100);

    dll_List.fn_Trace();

    dll_List.fn_DelNode(5);
    dll_List.fn_DelNode(1);
    dll_List.fn_DelNode(0);

    dll_List.fn_Trace();

    dll_List.fn_DelNode();

    return 0;
}

template <typename Type>
Node<Type>::Node(Type typ_Field)
{
    this->typ_Field = typ_Field;
    nodptr_Next = nodptr_Prev = nullptr;
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
    for(Node<Type>* nodptr_Curr = nodptr_Start; nodptr_Curr != nodptr_End;)
    {
        Node<Type>* nodptr_Temp = nodptr_Curr->nodptr_Next;

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

    for(Node<Type>* nodptr_Curr = nodptr_Start; nodptr_Curr != nodptr_End; nodptr_Curr = nodptr_Curr->nodptr_Next)
    {
        std::cout<< nodptr_Curr->typ_Field << " -> ";
    }

    std::cout<< nodptr_End->typ_Field << " -> start\n";
}

template <typename Type>
void Doubly_Circular_Linked_List<Type>::fn_AddNode(Type typ_Field)
{
    Node<Type>* nodptr_Elem = new Node<Type>(typ_Field);

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
    Node<Type>* nodptr_Curr = nodptr_Start;

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
    Node<Type>* nodptr_Elem = new Node<Type>(typ_Field);

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
        Node<Type>* nodptr_Curr = nodptr_Start;

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
