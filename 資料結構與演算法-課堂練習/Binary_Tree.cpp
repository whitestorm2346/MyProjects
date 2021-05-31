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
    Node<Type>* fn_Search(Node<Type>* nodptr_Curr, Type typ_Field, bool bl_Last = false)
    {
        if(!bl_Last && nodptr_Curr->typ_Field == typ_Field) return nodptr_Curr;

        if(nodptr_Curr->nodptr_L != nullptr) return fn_Search(nodptr_Curr->nodptr_L, typ_Field, bl_Last);

        if(nodptr_Curr->nodptr_R != nullptr) return fn_Search(nodptr_Curr->nodptr_R, typ_Field, bl_Last);

        return nodptr_Curr;
    }
    void fn_Insert(Type typ_Field);
    void fn_Delete(Type typ_Field);
    void fn_Trace(Node<Type>* nodptr_Temp, bool bl_Del = false)
    {
        if(nodptr_Temp == nullptr) return;

        fn_Trace(nodptr_Temp->nodptr_L, bl_Del);
        Node<Type>* nodptr_TempR = nodptr_Temp->nodptr_R;

        if(bl_Del == false) std::cout<< nodptr_Temp->typ_Field << ' ';
        else delete nodptr_Temp;

        fn_Trace(nodptr_TempR, bl_Del);
    }
};

int main()
{
    BinaryTree<int> bt_Main(100);

    bt_Main.fn_Trace(bt_Main.nodptr_Root);

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
    nodptr_Root = fn_CreateNode(typ_Field);
}

template <typename Type>
BinaryTree<Type>::~BinaryTree()
{
    fn_Trace(nodptr_Root, true);
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
void BinaryTree<Type>::fn_Delete(Type typ_Field)
{

}

template <typename Type>
void BinaryTree<Type>::fn_Insert(Type typ_Field)
{
    std::queue<Node<Type>*> que_Nodptr;

    que_Nodptr.push(nodptr_Root);

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
