#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#define sll  Singly_Linked_List
#define scll Singly_Circular_Linked_List
#define dll  Doubly_Linked_List
#define dcll Doubly_Circular_Linked_List

namespace nod
{
    template <typename Type>
    class Singly_Node
    {
    public:
        Type typ_Field;
        Singly_Node<Type>* nodptr_Next;

        Singly_Node(Type typ_Field)
        {
            nodptr_Next = nullptr;
            this->typ_Field = typ_Field;
        }
    };

    template <typename Type>
    class Doubly_Node
    {
    public:
        Type typ_Field;
        Doubly_Node<Type>* nodptr_Next;
        Doubly_Node<Type>* nodptr_Prev;

        Doubly_Node(Type typ_Field)
        {
            nodptr_Next = nullptr;
            nodptr_Prev = nullptr;
            this->typ_Field = typ_Field;
        }
    };
}

namespace std
{
    template <typename Type>
    class Singly_Linked_List
    {
    private:
        int int_NodCount;
        nod::Singly_Node<Type>* nodptr_End;
        nod::Singly_Node<Type>* nodptr_Start;

    public:
        Singly_Linked_List()
        {
            nodptr_Start = nullptr;
            nodptr_End = nullptr;
            int_NodCount = 0;
        }
        ~Singly_Linked_List()
        {
            for(nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start; int_NodCount > 0;)
            {
                nod::Singly_Node<Type>* nodptr_Temp = nodptr_Curr;

                nodptr_Curr = nodptr_Curr->nodptr_Next;
                int_NodCount--;

                delete nodptr_Temp;
            }
        }

        void assign(int int_Idx, Type typ_NewElem)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (assign)\n";

                return;
            }

            nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start;

            while(int_Idx--)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Next;
            }

            nodptr_Curr->typ_Field = typ_NewElem;
        }
        void push_front(Type typ_Field)
        {
            nod::Singly_Node<Type>* nodptr_NewNode = new nod::Singly_Node<Type>(typ_Field);

            if(int_NodCount == 0)
            {
                nodptr_Start = nodptr_NewNode;
                nodptr_End = nodptr_NewNode;
                int_NodCount++;
            }
            else
            {
                nodptr_NewNode->nodptr_Next = nodptr_Start;
                nodptr_Start = nodptr_NewNode;
                int_NodCount++;
            }
        }
        void push_back(Type typ_Field)
        {
            nod::Singly_Node<Type>* nodptr_NewNode = new nod::Singly_Node<Type>(typ_Field);

            if(int_NodCount == 0)
            {
                nodptr_Start = nodptr_NewNode;
                nodptr_End = nodptr_NewNode;
                int_NodCount++;
            }
            else
            {
                nodptr_End->nodptr_Next = nodptr_NewNode;
                nodptr_End = nodptr_NewNode;
                int_NodCount++;
            }
        }
        void insert(int int_Idx, Type typ_Field)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (insert)\n";

                return;
            }

            nod::Singly_Node<Type>* nodptr_NewNode = new nod::Singly_Node<Type>(typ_Field);
            nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start;

            if(int_Idx == 0)
            {
                nodptr_NewNode->nodptr_Next = nodptr_Start;
                nodptr_Start = nodptr_NewNode;
                int_NodCount++;
            }
            else
            {
                nod::Singly_Node<Type>* nodptr_Temp;

                while(int_Idx--)
                {
                    nodptr_Temp = nodptr_Curr;
                    nodptr_Curr = nodptr_Curr->nodptr_Next;
                }

                nodptr_Temp->nodptr_Next = nodptr_NewNode;
                nodptr_NewNode->nodptr_Next = nodptr_Curr;
                int_NodCount++;
            }
        }
        void pop_front()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (pop_front)\n";

                return;
            }

            nod::Singly_Node<Type>* nodptr_Temp = nodptr_Start;

            if(int_NodCount == 1)
            {
                nodptr_Start = nullptr;
                nodptr_End = nullptr;
                int_NodCount--;
            }
            else
            {
                nodptr_Start = nodptr_Start->nodptr_Next;
                int_NodCount--;
            }

            delete nodptr_Temp;
        }
        void pop_back()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (pop_back)\n";

                return;
            }

            nod::Singly_Node<Type>* nodptr_Temp = nodptr_Start;

            if(int_NodCount == 1)
            {
                nodptr_Start = nullptr;
                nodptr_End = nullptr;
                int_NodCount--;

                delete nodptr_Temp;
            }
            else
            {
                while(nodptr_Temp->nodptr_Next != nodptr_End)
                {
                    nodptr_Temp = nodptr_Temp->nodptr_Next;
                }

                delete nodptr_End;

                nodptr_End = nodptr_Temp;
            }
        }
        void erase(int int_Idx)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (erase)\n";

                return;
            }

            nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start;

            if(int_Idx == 0)
            {
                nodptr_Start = nodptr_Start->nodptr_Next;
                int_NodCount--;

                delete nodptr_Curr;
            }
            else
            {
                nod::Singly_Node<Type>* nodptr_Temp;

                while(int_Idx--)
                {
                    nodptr_Temp = nodptr_Curr;
                    nodptr_Curr = nodptr_Curr->nodptr_Next;
                }

                nodptr_Temp->nodptr_Next = nodptr_Curr->nodptr_Next;
                int_NodCount--;

                delete nodptr_Curr;
            }
        }
        void clear()
        {
            for(nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start; int_NodCount > 0;)
            {
                nod::Singly_Node<Type>* nodptr_Temp = nodptr_Curr;

                nodptr_Curr = nodptr_Curr->nodptr_Next;
                int_NodCount--;

                delete nodptr_Temp;
            }

            nodptr_Start = nullptr;
            nodptr_End = nullptr;
            int_NodCount = 0;
        }
        void reverse()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (reverse)\n";

                return;
            }

            int int_Count = int_NodCount - 1;

            while(int_Count--)
            {
                Type typ_Temp = nodptr_Start->typ_Field;
                nod::Singly_Node<Type>* nodptr_Temp = nodptr_Start;

                nodptr_Start = nodptr_Start->nodptr_Next;

                delete nodptr_Temp;

                nodptr_Temp = new nod::Singly_Node<Type>(typ_Temp);

                nodptr_End->nodptr_Next = nodptr_Temp;
                nodptr_End = nodptr_Temp;
            }
        }
        int size()
        {
            return int_NodCount;
        }
        bool empty()
        {
            return int_NodCount == 0;
        }
        Type at(int int_Idx)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (at)\n";

                return;
            }

            nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start;

            while(int_Idx--)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Next;
            }

            return nodptr_Curr->typ_Field;
        }
        nod::Singly_Node<Type>* begin()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (begin)\n";

                return nullptr;
            }

            return nodptr_Start;
        }
        nod::Singly_Node<Type>* end()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (end)\n";

                return nullptr;
            }

            return nodptr_End;
        }
        Type front()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (front)\n";

                return 0;
            }

            return nodptr_Start->typ_Field;
        }
        Type back()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (back)\n";

                return 0;
            }

            return nodptr_End->typ_Field;
        }

        Type& operator [] (int int_Idx)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (operator[])\n";

                return nodptr_Start->typ_Field;
            }

            nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start;

            while(int_Idx--)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Next;
            }

            return nodptr_Curr->typ_Field;
        }
    };

//=============================================================================================

    template <typename Type>
    class Singly_Circular_Linked_List
    {
    private:
        int int_NodCount;
        nod::Singly_Node<Type>* nodptr_End;
        nod::Singly_Node<Type>* nodptr_Start;

    public:
        Singly_Circular_Linked_List()
        {
            nodptr_Start = nullptr;
            nodptr_End = nullptr;
            int_NodCount = 0;
        }
        ~Singly_Circular_Linked_List()
        {
            for(nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start; int_NodCount > 0;)
            {
                nod::Singly_Node<Type>* nodptr_Temp = nodptr_Curr;

                nodptr_Curr = nodptr_Curr->nodptr_Next;
                int_NodCount--;

                delete nodptr_Temp;
            }
        }

        void assign(int int_Idx, Type typ_NewElem)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (assign)\n";

                return;
            }

            nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start;

            while(int_Idx--)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Next;
            }

            nodptr_Curr->typ_Field = typ_NewElem;
        }
        void push_front(Type typ_Field)
        {
            nod::Singly_Node<Type>* nodptr_NewNode = new nod::Singly_Node<Type>(typ_Field);

            if(int_NodCount == 0)
            {
                nodptr_Start = nodptr_NewNode;
                nodptr_End = nodptr_NewNode;
                nodptr_End->nodptr_Next = nodptr_Start;
                int_NodCount++;
            }
            else
            {
                nodptr_NewNode->nodptr_Next = nodptr_Start;
                nodptr_Start = nodptr_NewNode;
                nodptr_End->nodptr_Next = nodptr_NewNode;
                int_NodCount++;
            }
        }
        void push_back(Type typ_Field)
        {
            nod::Singly_Node<Type>* nodptr_NewNode = new nod::Singly_Node<Type>(typ_Field);


            if(int_NodCount == 0)
            {
                nodptr_Start = nodptr_NewNode;
                nodptr_End = nodptr_NewNode;
                nodptr_End->nodptr_Next = nodptr_Start;
                int_NodCount++;
            }
            else
            {
                nodptr_End->nodptr_Next = nodptr_NewNode;
                nodptr_End = nodptr_NewNode;
                nodptr_NewNode->nodptr_Next = nodptr_Start;
                int_NodCount++;
            }
        }
        void insert(int int_Idx, Type typ_Field)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (insert)\n";

                return;
            }

            nod::Singly_Node<Type>* nodptr_NewNode = new nod::Singly_Node<Type>(typ_Field);
            nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start;

            if(int_Idx == 0)
            {
                nodptr_NewNode->nodptr_Next = nodptr_Start;
                nodptr_Start = nodptr_NewNode;
                nodptr_End->nodptr_Next = nodptr_NewNode;
                int_NodCount++;
            }
            else
            {
                nod::Singly_Node<Type>* nodptr_Temp;

                while(int_Idx--)
                {
                    nodptr_Temp = nodptr_Curr;
                    nodptr_Curr = nodptr_Curr->nodptr_Next;
                }

                nodptr_Temp->nodptr_Next = nodptr_NewNode;
                nodptr_NewNode->nodptr_Next = nodptr_Curr;
                int_NodCount++;
            }
        }
        void pop_front()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (pop_front)\n";

                return;
            }

            nod::Singly_Node<Type>* nodptr_Temp = nodptr_Start;

            if(int_NodCount == 1)
            {
                nodptr_Start = nullptr;
                nodptr_End = nullptr;
                int_NodCount--;
            }
            else
            {
                nodptr_Start = nodptr_Start->nodptr_Next;
                nodptr_End->nodptr_Next = nodptr_Start;
                int_NodCount--;
            }

            delete nodptr_Temp;
        }
        void pop_back()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (pop_back)\n";

                return;
            }

            nod::Singly_Node<Type>* nodptr_Temp = nodptr_Start;

            if(int_NodCount == 1)
            {
                nodptr_Start = nullptr;
                nodptr_End = nullptr;
                int_NodCount--;

                delete nodptr_Temp;
            }
            else
            {
                while(nodptr_Temp->nodptr_Next != nodptr_End)
                {
                    nodptr_Temp = nodptr_Temp->nodptr_Next;
                }

                delete nodptr_End;

                nodptr_End = nodptr_Temp;
                nodptr_End->nodptr_Next = nodptr_Start;
            }
        }
        void erase(int int_Idx)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (erase)\n";

                return;
            }

            nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start;

            if(int_Idx == 0)
            {
                nodptr_End->nodptr_Next = nodptr_Start->nodptr_Next;
                nodptr_Start = nodptr_Start->nodptr_Next;
                int_NodCount--;

                delete nodptr_Curr;
            }
            else
            {
                nod::Singly_Node<Type>* nodptr_Temp;

                while(int_Idx--)
                {
                    nodptr_Temp = nodptr_Curr;
                    nodptr_Curr = nodptr_Curr->nodptr_Next;
                }

                nodptr_Temp->nodptr_Next = nodptr_Curr->nodptr_Next;
                int_NodCount--;

                delete nodptr_Curr;
            }
        }
        void clear()
        {
            for(nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start; int_NodCount > 0;)
            {
                nod::Singly_Node<Type>* nodptr_Temp = nodptr_Curr;

                nodptr_Curr = nodptr_Curr->nodptr_Next;
                int_NodCount--;

                delete nodptr_Temp;
            }

            nodptr_Start = nullptr;
            nodptr_End = nullptr;
            int_NodCount = 0;
        }
        void reverse()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (reverse)\n";

                return;
            }

            int int_Count = int_NodCount - 1;

            while(int_Count--)
            {
                Type typ_Temp = nodptr_Start->typ_Field;
                nod::Singly_Node<Type>* nodptr_Temp = nodptr_Start;

                nodptr_Start = nodptr_Start->nodptr_Next;
                nodptr_End->nodptr_Next = nodptr_Start;
                int_NodCount--;

                delete nodptr_Temp;

                nodptr_Temp = new nod::Singly_Node<Type>(typ_Temp);

                nodptr_End->nodptr_Next = nodptr_Temp;
                nodptr_Temp->nodptr_Next = nodptr_Start;
                nodptr_End = nodptr_Temp;
            }
        }
        int size()
        {
            return int_NodCount;
        }
        bool empty()
        {
            return int_NodCount == 0;
        }
        Type at(int int_Idx)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (at)\n";

                return;
            }

            nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start;

            while(int_Idx--)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Next;
            }

            return nodptr_Curr->typ_Field;
        }
        nod::Singly_Node<Type>* begin()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (begin)\n";

                return nullptr;
            }

            return nodptr_Start;
        }
        nod::Singly_Node<Type>* end()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (end)\n";

                return nullptr;
            }

            return nodptr_End;
        }
        Type front()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (front)\n";

                return 0;
            }

            return nodptr_Start->typ_Field;
        }
        Type back()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (back)\n";

                return 0;
            }

            return nodptr_End->typ_Field;
        }

        Type& operator [] (int int_Idx)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (operator[])\n";

                return nodptr_Start->typ_Field;
            }

            nod::Singly_Node<Type>* nodptr_Curr = nodptr_Start;

            while(int_Idx--)
            {
                nodptr_Curr = nodptr_Curr->nodptr_Next;
            }

            return nodptr_Curr->typ_Field;
        }
    };

//=============================================================================================

    template <typename Type>
    class Doubly_Linked_List
    {
    private:
        int int_NodCount;
        nod::Doubly_Node<Type>* nodptr_Start;
        nod::Doubly_Node<Type>* nodptr_End;

    public:
        Doubly_Linked_List()
        {
            nodptr_Start = nullptr;
            nodptr_End = nullptr;
            int_NodCount = 0;
        }
        ~Doubly_Linked_List()
        {
            for(nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start; int_NodCount > 0;)
            {
                nod::Doubly_Node<Type>* nodptr_Temp = nodptr_Curr;

                nodptr_Curr = nodptr_Curr->nodptr_Next;
                int_NodCount--;

                delete nodptr_Temp;
            }
        }

        void assign(int int_Idx, Type typ_NewElem)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (assign)\n";

                return;
            }

            nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

            if(int_Idx < int_NodCount / 2)
            {
                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Next;
                }
            }
            else
            {
                nodptr_Curr = nodptr_End;
                int_Idx = int_NodCount - 1 - int_Idx;

                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Prev;
                }
            }

            nodptr_Curr->typ_Field = typ_NewElem;
        }
        void push_front(Type typ_Field)
        {
            nod::Doubly_Node<Type>* nodptr_NewNode = new nod::Doubly_Node<Type>(typ_Field);

            if(int_NodCount == 0)
            {
                nodptr_Start = nodptr_NewNode;
                nodptr_End = nodptr_NewNode;
                int_NodCount++;
            }
            else
            {
                nodptr_Start->nodptr_Prev = nodptr_NewNode;
                nodptr_NewNode->nodptr_Next = nodptr_Start;
                nodptr_Start = nodptr_NewNode;
                int_NodCount++;
            }
        }
        void push_back(Type typ_Field)
        {
            nod::Doubly_Node<Type>* nodptr_NewNode = new nod::Doubly_Node<Type>(typ_Field);

            if(int_NodCount == 0)
            {
                nodptr_Start = nodptr_NewNode;
                nodptr_End = nodptr_NewNode;
                int_NodCount++;
            }
            else
            {
                nodptr_End->nodptr_Next = nodptr_NewNode;
                nodptr_NewNode->nodptr_Prev = nodptr_End;
                nodptr_End = nodptr_NewNode;
                int_NodCount++;
            }
        }
        void insert(int int_Idx, Type typ_Field)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (insert)\n";

                return;
            }

            nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start;
            nod::Doubly_Node<Type>* nodptr_NewNode = new nod::Doubly_Node<Type>(typ_Field);

            if(int_Idx == 0)
            {
                nodptr_Start->nodptr_Prev = nodptr_NewNode;
                nodptr_NewNode->nodptr_Next = nodptr_Start;
                nodptr_Start = nodptr_NewNode;
                int_NodCount++;

                return;
            }

            if(int_Idx < int_NodCount / 2)
            {
                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Next;
                }
            }
            else
            {
                nodptr_Curr = nodptr_End;
                int_Idx = int_NodCount - 1 - int_Idx;

                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Prev;
                }
            }

            nodptr_NewNode->nodptr_Prev = nodptr_Curr->nodptr_Prev;
            nodptr_NewNode->nodptr_Next = nodptr_Curr;
            nodptr_Curr->nodptr_Prev->nodptr_Next = nodptr_NewNode;
            nodptr_Curr->nodptr_Prev = nodptr_NewNode;
            int_NodCount++;
        }
        void pop_front()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (pop_front)\n";

                return;
            }

            nod::Doubly_Node<Type>* nodptr_Temp = nodptr_Start;

            if(int_NodCount == 1)
            {
                nodptr_Start = nullptr;
                nodptr_End = nullptr;
                int_NodCount--;
            }
            else
            {
                nodptr_Start = nodptr_Start->nodptr_Next;
                nodptr_Start->nodptr_Prev = nullptr;
                int_NodCount--;
            }

            delete nodptr_Temp;
        }
        void pop_back()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (pop_back)\n";

                return;
            }

            nod::Doubly_Node<Type>* nodptr_Temp = nodptr_End;

            if(int_NodCount == 1)
            {
                nodptr_Start = nullptr;
                nodptr_End = nullptr;
                int_NodCount--;

                delete nodptr_Temp;

                return;
            }

            nodptr_End = nodptr_End->nodptr_Prev;
            nodptr_End->nodptr_Next = nullptr;
            int_NodCount--;

            delete nodptr_Temp;
        }
        void erase(int int_Idx)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (erase)\n";

                return;
            }

            nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

            if(int_Idx == 0)
            {
                nodptr_Start = nodptr_Start->nodptr_Next;
                int_NodCount--;
            }
            else
            {
                if(int_Idx < int_NodCount / 2)
                {
                    while(int_Idx--)
                    {
                        nodptr_Curr = nodptr_Curr->nodptr_Next;
                    }
                }
                else
                {
                    nodptr_Curr = nodptr_End;
                    int_Idx = int_NodCount - 1 - int_Idx;

                    while(int_Idx--)
                    {
                        nodptr_Curr = nodptr_Curr->nodptr_Prev;
                    }
                }

                nodptr_Curr->nodptr_Prev->nodptr_Next = nodptr_Curr->nodptr_Next;
                nodptr_Curr->nodptr_Next->nodptr_Prev = nodptr_Curr->nodptr_Prev;
                int_NodCount--;
            }

            delete nodptr_Curr;
        }
        void clear()
        {
            for(nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start; int_NodCount > 0;)
            {
                nod::Doubly_Node<Type>* nodptr_Temp = nodptr_Curr;

                nodptr_Curr = nodptr_Curr->nodptr_Next;
                int_NodCount--;

                delete nodptr_Temp;
            }

            nodptr_Start = nullptr;
            nodptr_End = nullptr;
            int_NodCount = 0;
        }
        void reverse()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (reverse)\n";

                return;
            }

            int int_Count = int_NodCount - 1;

            while(int_Count--)
            {
                Type typ_Temp = nodptr_Start->typ_Field;
                nod::Doubly_Node<Type>* nodptr_Temp = nodptr_Start;

                nodptr_Start = nodptr_Start->nodptr_Next;
                nodptr_Start->nodptr_Prev = nullptr;

                delete nodptr_Temp;

                nodptr_Temp = new nod::Doubly_Node<Type>(typ_Temp);

                nodptr_End->nodptr_Next = nodptr_Temp;
                nodptr_Temp->nodptr_Prev = nodptr_End;
                nodptr_End = nodptr_Temp;
            }
        }
        int size()
        {
            return int_NodCount;
        }
        bool empty()
        {
            return int_NodCount == 0;
        }
        Type at(int int_Idx)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (at)\n";

                return;
            }

            nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

            if(int_Idx < int_NodCount / 2)
            {
                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Next;
                }
            }
            else
            {
                nodptr_Curr = nodptr_End;
                int_Idx = int_NodCount - 1 - int_Idx;

                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Prev;
                }
            }

            return nodptr_Curr->typ_Field;
        }
        nod::Doubly_Node<Type>* begin()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (begin)\n";

                return nullptr;
            }

            return nodptr_Start;
        }
        nod::Doubly_Node<Type>* end()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (end)\n";

                return nullptr;
            }

            return nodptr_End;
        }
        Type front()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (front)\n";

                return 0;
            }

            return nodptr_Start->typ_Field;
        }
        Type back()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (back)\n";

                return 0;
            }

            return nodptr_End->typ_Field;
        }

        Type& operator [] (int int_Idx)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (operator[])\n";

                return nodptr_Start->typ_Field;
            }

            nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

            if(int_Idx < int_NodCount / 2)
            {
                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Next;
                }
            }
            else
            {
                nodptr_Curr = nodptr_End;
                int_Idx = int_NodCount - 1 - int_Idx;

                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Prev;
                }
            }

            return nodptr_Curr->typ_Field;
        }
    };

// ===================================================================================================

    template <typename Type>
    class Doubly_Circular_Linked_List
    {
    private:
        int int_NodCount;
        nod::Doubly_Node<Type>* nodptr_Start;
        nod::Doubly_Node<Type>* nodptr_End;

    public:
        Doubly_Circular_Linked_List()
        {
            nodptr_Start = nullptr;
            nodptr_End = nullptr;
            int_NodCount = 0;
        }
        ~Doubly_Circular_Linked_List()
        {
            for(nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start; int_NodCount > 0;)
            {
                nod::Doubly_Node<Type>* nodptr_Temp = nodptr_Curr;

                nodptr_Curr = nodptr_Curr->nodptr_Next;
                int_NodCount--;

                delete nodptr_Temp;
            }
        }

        void assign(int int_Idx, Type typ_NewElem)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (assign)\n";

                return;
            }

            nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

            if(int_Idx < int_NodCount / 2)
            {
                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Next;
                }
            }
            else
            {
                nodptr_Curr = nodptr_End;
                int_Idx = int_NodCount - 1 - int_Idx;

                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Prev;
                }
            }

            nodptr_Curr->typ_Field = typ_NewElem;
        }
        void push_front(Type typ_Field)
        {
            nod::Doubly_Node<Type>* nodptr_NewNode = new nod::Doubly_Node<Type>(typ_Field);

            if(int_NodCount == 0)
            {
                nodptr_Start = nodptr_NewNode;
                nodptr_End = nodptr_NewNode;
                nodptr_Start->nodptr_Prev = nodptr_End;
                nodptr_End->nodptr_Next = nodptr_Start;
                int_NodCount++;
            }
            else
            {
                nodptr_Start->nodptr_Prev = nodptr_NewNode;
                nodptr_End->nodptr_Next = nodptr_NewNode;
                nodptr_NewNode->nodptr_Next = nodptr_Start;
                nodptr_NewNode->nodptr_Prev = nodptr_End;
                nodptr_Start = nodptr_NewNode;
                int_NodCount++;
            }
        }
        void push_back(Type typ_Field)
        {
            nod::Doubly_Node<Type>* nodptr_NewNode = new nod::Doubly_Node<Type>(typ_Field);

            if(int_NodCount == 0)
            {
                nodptr_Start = nodptr_NewNode;
                nodptr_End = nodptr_NewNode;
                nodptr_Start->nodptr_Prev = nodptr_End;
                nodptr_End->nodptr_Next = nodptr_Start;
                int_NodCount++;
            }
            else
            {
                nodptr_End->nodptr_Next = nodptr_NewNode;
                nodptr_Start->nodptr_Prev = nodptr_NewNode;
                nodptr_NewNode->nodptr_Prev = nodptr_End;
                nodptr_NewNode->nodptr_Next = nodptr_Start;
                nodptr_End = nodptr_NewNode;
                int_NodCount++;
            }
        }
        void insert(int int_Idx, Type typ_Field)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (insert)\n";

                return;
            }

            nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start;
            nod::Doubly_Node<Type>* nodptr_NewNode = new nod::Doubly_Node<Type>(typ_Field);

            if(int_Idx == 0)
            {
                nodptr_Start->nodptr_Prev = nodptr_NewNode;
                nodptr_NewNode->nodptr_Next = nodptr_Start;
                nodptr_Start = nodptr_NewNode;
                int_NodCount++;

                return;
            }

            if(int_Idx < int_NodCount / 2)
            {
                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Next;
                }
            }
            else
            {
                nodptr_Curr = nodptr_End;
                int_Idx = int_NodCount - 1 - int_Idx;

                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Prev;
                }
            }

            nodptr_NewNode->nodptr_Prev = nodptr_Curr->nodptr_Prev;
            nodptr_NewNode->nodptr_Next = nodptr_Curr;
            nodptr_Curr->nodptr_Prev->nodptr_Next = nodptr_NewNode;
            nodptr_Curr->nodptr_Prev = nodptr_NewNode;
            int_NodCount++;
        }
        void pop_front()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (pop_front)\n";

                return;
            }

            nod::Doubly_Node<Type>* nodptr_Temp = nodptr_Start;

            if(int_NodCount == 1)
            {
                nodptr_Start = nullptr;
                nodptr_End = nullptr;
                int_NodCount--;

                delete nodptr_Temp;

                return;
            }

            nodptr_Start = nodptr_Start->nodptr_Next;
            nodptr_Start->nodptr_Prev = nullptr;
            int_NodCount--;

            delete nodptr_Temp;
        }
        void pop_back()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (pop_back)\n";

                return;
            }

            nod::Doubly_Node<Type>* nodptr_Temp = nodptr_End;

            if(int_NodCount == 1)
            {
                nodptr_Start = nullptr;
                nodptr_End = nullptr;
                int_NodCount--;

                delete nodptr_Temp;

                return;
            }

            nodptr_End = nodptr_End->nodptr_Prev;
            nodptr_End->nodptr_Next = nullptr;
            int_NodCount--;

            delete nodptr_Temp;
        }
        void erase(int int_Idx)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (erase)\n";

                return;
            }

            nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

            if(int_Idx == 0)
            {
                nodptr_Start = nodptr_Start->nodptr_Next;
                nodptr_End->nodptr_Next = nodptr_Start;
                nodptr_Start->nodptr_Prev = nodptr_End;
                int_NodCount--;
            }
            else
            {
                if(int_Idx < int_NodCount / 2)
                {
                    while(int_Idx--)
                    {
                        nodptr_Curr = nodptr_Curr->nodptr_Next;
                    }
                }
                else
                {
                    nodptr_Curr = nodptr_End;
                    int_Idx = int_NodCount - 1 - int_Idx;

                    while(int_Idx--)
                    {
                        nodptr_Curr = nodptr_Curr->nodptr_Prev;
                    }
                }

                nodptr_Curr->nodptr_Prev->nodptr_Next = nodptr_Curr->nodptr_Next;
                nodptr_Curr->nodptr_Next->nodptr_Prev = nodptr_Curr->nodptr_Prev;
                int_NodCount--;
            }

            delete nodptr_Curr;
        }
        void clear()
        {
            ~Doubly_Circular_Linked_List();
            Doubly_Circular_Linked_List();
        }
        void reverse()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (reverse)\n";

                return;
            }

            int int_Count = int_NodCount - 1;

            while(int_Count--)
            {
                Type typ_Temp = nodptr_Start->typ_Field;
                nod::Doubly_Node<Type>* nodptr_Temp = nodptr_Start;

                nodptr_Start = nodptr_Start->nodptr_Next;
                nodptr_End->nodptr_Next = nodptr_Start;
                nodptr_Start->nodptr_Prev = nodptr_End;

                delete nodptr_Temp;

                nodptr_Temp = new nod::Doubly_Node<Type>(typ_Temp);

                nodptr_End->nodptr_Next = nodptr_Temp;
                nodptr_Temp->nodptr_Prev = nodptr_End;
                nodptr_Temp->nodptr_Next = nodptr_Start;
                nodptr_Start->nodptr_Prev = nodptr_Temp;
                nodptr_End = nodptr_Temp;
            }
        }
        int size()
        {
            return int_NodCount;
        }
        bool empty()
        {
            return int_NodCount == 0;
        }
        Type at(int int_Idx)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (at)\n";

                return;
            }

            nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

            if(int_Idx < int_NodCount / 2)
            {
                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Next;
                }
            }
            else
            {
                nodptr_Curr = nodptr_End;
                int_Idx = int_NodCount - 1 - int_Idx;

                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Prev;
                }
            }

            return nodptr_Curr->typ_Field;
        }
        nod::Doubly_Node<Type>* begin()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (begin)\n";

                return nullptr;
            }

            return nodptr_Start;
        }
        nod::Doubly_Node<Type>* end()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (end)\n";

                return nullptr;
            }

            return nodptr_End;
        }
        Type front()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (front)\n";

                return 0;
            }

            return nodptr_Start->typ_Field;
        }
        Type back()
        {
            if(int_NodCount == 0)
            {
                std::cerr<< "Invalid action (back)\n";

                return 0;
            }

            return nodptr_End->typ_Field;
        }

        Type& operator [] (int int_Idx)
        {
            if(int_Idx >= int_NodCount || int_Idx < 0)
            {
                std::cerr<< "Invalid index (operator[])\n";

                return nodptr_Start->typ_Field;
            }

            nod::Doubly_Node<Type>* nodptr_Curr = nodptr_Start;

            if(int_Idx < int_NodCount / 2)
            {
                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Next;
                }
            }
            else
            {
                nodptr_Curr = nodptr_End;
                int_Idx = int_NodCount - 1 - int_Idx;

                while(int_Idx--)
                {
                    nodptr_Curr = nodptr_Curr->nodptr_Prev;
                }
            }

            return nodptr_Curr->typ_Field;
        }
    };
}

#endif // LINKEDLIST_H_INCLUDED
