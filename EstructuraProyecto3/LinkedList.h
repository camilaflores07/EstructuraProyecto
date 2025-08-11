#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <QList>
#include "Node.h"

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    // Insercion
    void push_front(int pos, int value);
    void push_back(int pos, int value);
    void insert_value(int pos, int value);

    // Eliminacion
    void pop_front();
    void pop_back();
    void remove_value(int value);
    void remove_at(int pos);

    // Busqueda
    int find(int value);

    // Pintar
    void print();
    QList<int> toList();

private:
    Node* head; // primero
    Node* tail; // ultimo
};

#endif // LINKEDLIST_H
