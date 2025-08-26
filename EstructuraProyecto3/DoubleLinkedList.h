#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <QList>
#include "Node.h"

class DoubleLinkedList {
public:
    DoubleLinkedList();
    ~DoubleLinkedList();

    void push_front(int pos, int value);
    void push_back(int pos, int value);
    void insert_value(int pos, int value);
    void pop_front();
    void pop_back();
    void remove_value(int value);
    void remove_at(int pos);
    int find(int value);
    void print();
    QList<int> toList();  // Para el pincel

private:
    Node* head;
    Node* tail;
};

#endif // DOUBLELINKEDLIST_H
