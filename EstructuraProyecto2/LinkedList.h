#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:
    LinkedList();
    ~LinkedList();  // destruye cositas

    //
    void push_front(int pos, int value);
    void push_back(int pos, int value);


    //matar
    void pop_front();  //mata primer nodo
    void pop_back(); //mata ultimo nodo

    //eliminar e instertar valores
    void remove_value(int value);
    void insert_value(int pos, int value);

    //buscar
    int find(int value);

    void print();

private:
    Node* head; //nodo 1
    Node* tail; //fin
};

#endif // LINKEDLIST_H
