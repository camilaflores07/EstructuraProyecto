#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:
    LinkedList();
    ~LinkedList();  // destruye cositas

    //insertar
    void push_front(int value); // insertar al principio
    void push_back(int value); // insertar al final

    //eliminar
    void pop_front();  //mata primer nodo

    void print();

private:
    Node* head; //nodo 1
};

#endif // LINKEDLIST_H
