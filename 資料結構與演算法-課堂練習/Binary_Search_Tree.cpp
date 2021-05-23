#include <iostream>

template <class Type>
class Node
{
public:
    Type typ_Field;
    Node<Type>* nodptr_L;
    Node<Type>* nodptr_R;

    Node(Type typ_Field);
};

template<class Type>
class BinarySearchTree
{
public:
    Node<Type>* nodptr_Root;

    BinarySearchTree(Type typ_Field);
    ~BinarySearchTree();

    void fn_InsNode(Type typ_Field);
    void fn_TraInOrder(Node<Type>* nodptr_Curr, bool bl_Del);
};

int main()
{
    BinarySearchTree<int> bst_Main(10);

    bst_Main.fn_InsNode(5);
    bst_Main.fn_InsNode(1);
    bst_Main.fn_InsNode(7);
    bst_Main.fn_InsNode(2);
    bst_Main.fn_InsNode(40);
    bst_Main.fn_InsNode(50);

	std::cout<<"Inorder traversal of the constructed tree: \n";

	bst_Main.fn_TraInOrder(bst_Main.nodptr_Root, false);

	return 0;
}

template <typename Type>
Node<Type>::Node(Type typ_Field)
{
    this->typ_Field = typ_Field;
    nodptr_L = nodptr_R = nullptr;
}

template <typename Type>
BinarySearchTree<Type>::BinarySearchTree(Type typ_Field)
{
    nodptr_Root = new Node<Type>(typ_Field);
}

template <typename Type>
BinarySearchTree<Type>::~BinarySearchTree()
{
    fn_TraInOrder(nodptr_Root, true);
}

template <typename Type>
void BinarySearchTree<Type>::fn_InsNode(Type typ_Field)
{
    Node<Type>* nodptr_Elem = new Node<Type>(typ_Field);

    for(Node<Type>* nodptr_Temp = nodptr_Root;;)
    {
        if(nodptr_Temp->typ_Field > typ_Field)
        {
            if(nodptr_Temp->nodptr_L == nullptr)
            {
                nodptr_Temp->nodptr_L = nodptr_Elem;

                break;
            }
            else nodptr_Temp = nodptr_Temp->nodptr_L;
        }
        else
        {
            if(nodptr_Temp->nodptr_R == nullptr)
            {
                nodptr_Temp->nodptr_R = nodptr_Elem;

                break;
            }
            else nodptr_Temp = nodptr_Temp->nodptr_R;
        }
    }
}

template <typename Type>
void BinarySearchTree<Type>::fn_TraInOrder(Node<Type>* nodptr_Curr, bool bl_Del)
{
    if(nodptr_Curr == nullptr) return;

    fn_TraInOrder(nodptr_Curr->nodptr_L, bl_Del);

    Node<Type>* nodptr_TempR = nodptr_Curr->nodptr_R;

    if(bl_Del) delete nodptr_Curr;
    else std::cout<< nodptr_Curr->typ_Field << ' ';

    fn_TraInOrder(nodptr_TempR, bl_Del);
}
