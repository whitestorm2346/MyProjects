#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

template <typename Type>
class Node
{
public:
    Type data;
    Node<Type>* prev;
    Node<Type>* next;

    Node();
    virtual ~Node();
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

    Node<Type>* getFront();
    Node<Type>* getBack();
};

#endif // LIST_HPP_INCLUDED
