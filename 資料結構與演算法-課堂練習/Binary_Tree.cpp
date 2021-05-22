#include <iostream>
#include <queue>

template <typename Type>
class Node
{
public:
    Type typ_Field;
    Node<Type>* nodptr_L;
    Node<Type>* nodptr_R;

    Node();
};

template <typename Type>
class BinaryTree
{
public:
    Node<Type>* nodptr_Root;

    BinaryTree(Type typ_Field);
    ~BinaryTree();

    Node<Type>* fn_CreateNode(Type typ_Field);
    void fn_Insert(Type typ_Field);
    void fn_Trace(Node<Type>* nodptr_Temp, bool bl_Del = false)
    {
        if(nodptr_Temp == nullptr) return;

        fn_TraInOrder(nodptr_Temp->nodptr_L, bl_Mode);
        Node<Type>* nodptr_TempR = nodptr_Temp->nodptr_R;

        if(b_Mode == false) std::cout<< nodptr_Temp->typ_Field << ' ';
        else delete nodptr_Temp;

        fn_Destroy(nodptr_TempR, bl_Mode);
    }
};

int main()
{
    return 0;
}

template <typename Type>
Node<Type>::Node()
{
    nodptr_L = nodptr_R = nullptr;
}

template <typename Type>
BinaryTree<Type>::BinaryTree(Type typ_Field)
{
    nodptr_Root = nullptr;
}

template <typename Type>
BinaryTree<Type>::~BinaryTree(Type typ_Field)
{
    nodptr_Root = nullptr;
}

template <typename Type>
Node<Type>* BinaryTree<Type>::fn_CreateNode(Type typ_Field)
{
    Node<Type>* nodptr_Ele = new Node<Type>();

    try
    {
        if(!nodptr_Ele) throw "Memory allocation error\n";
    }
    catch(const char* chrptr_Msg)
    {
        std::cout<< chrptr_Msg;

        exit(1);
    }

    nodptr_Ele->typ_Field = typ_Field;

    return nodptr_Ele;
}

template <typename Type>
void BinaryTree<Type>::fn_Insert(Type typ_Field)
{
    std::queue<Node<Type>*> que_Nodptr;

    que_Nodptr.push(op_Root);

    while(!que_Nodptr.empty())
    {
        Node<Type>* nodptr_Temp = que_Nodptr.front();

        que_Nodptr.pop();

        if(nodptr_Temp->nodptr_L != nullptr) que_Nodptr.push(nodptr_Temp->nodptr_L);
        else
        {
            nodptr_Temp->nodptr_L = fn_CreateNode(typ_Field);
            return;
        }

        if(nodptr_Temp->nodptr_R != nullptr) que_Nodptr.push(nodptr_Temp->nodptr_R);
        else
        {
            nodptr_Temp->nodptr_R = fn_CreateNode(typ_Field);
            return;
        }
    }
}
