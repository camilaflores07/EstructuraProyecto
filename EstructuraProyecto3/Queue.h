#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

class Queue {
private:
    Node* front;
    Node* rear;
    int size;

public:
    Queue();
    ~Queue();



    void enqueue(int value);
    int dequeue();
    int peek() const;

    bool isEmpty() const;
    int getSize() const;

    void clear();


    Node* getFront() const;
};

#endif // QUEUE_H
