#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

template <typename Type>
class Node
{
public:
    Type data;
    Node<Type>* prev;
    Node<Type>* next;

    Node(Type data);
};

template <typename Type>
class List
{
private:
    Node<Type>* front;
    Node<Type>* back;
    int nodeCount;

public:
    List();
    virtual ~List();

    void insert(Node<Type>* newNode);
    void erase();
    bool empty();
    int  size();

    Node<Type>* getFront();
    Node<Type>* getBack();
};

template <typename Type>
Node<Type>::Node(Type data)
{
    this->data = data;
    prev = nullptr;
    next = nullptr;
}

template <typename Type>
List<Type>::List()
{
    front = nullptr;
    back = nullptr;
    nodeCount = 0;
}

template <typename Type>
List<Type>::~List()
{
    while(!empty())
    {
        erase();
    }
}

template <typename Type>
void List<Type>::insert(Node<Type>* newNode)
{
    if(nodeCount == 0)
    {
        front = back = newNode;
        newNode->next = newNode->prev = newNode;
    }
    else
    {
        front->prev = back->next = newNode;
        newNode->next = front;
        newNode->prev = back;
        back = newNode;
    }

    nodeCount++;
}

template <typename Type>
void List<Type>::erase()
{
    if(nodeCount <= 0) return;

    Node<Type>* temp = back;

    if(nodeCount == 1)
    {
        front = nullptr;
        back = nullptr;
    }
    else
    {
        front->prev = back->prev;
        back->prev->next = front;
        back = back->prev;
    }

    nodeCount--;

    delete temp;
}

template <typename Type>
bool List<Type>::empty()
{
    return (nodeCount == 0);
}

template <typename Type>
int List<Type>::size()
{
    return nodeCount;
}

template <typename Type>
Node<Type>* List<Type>::getFront()
{
    return front;
}

template <typename Type>
Node<Type>* List<Type>::getBack()
{
    return back;
}

#endif // LIST_HPP_INCLUDED
