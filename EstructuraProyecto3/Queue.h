#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <iostream>

class Queue {
private:
    Node* front;  // Primer elemento (para dequeue)
    Node* rear;   // Último elemento (para enqueue)
    int size;

public:
    Queue();
    ~Queue();

    // Operaciones principales
    void enqueue(int value);
    int dequeue();
    int peek() const;

    // Utilidades
    bool isEmpty() const;
    int getSize() const;
    void clear();

    // Para visualización
    Node* getFront() const;
};

#endif // QUEUE_H
