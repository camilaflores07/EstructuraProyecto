#ifndef STACK_H
#define STACK_H

#include "Node.h"

class Stack {
private:
    Node* top;
    int size;

public:

    Stack();

    ~Stack();

    void push(int data);
    int pop();
    int peek() const;


    bool isEmpty() const;
    int getSize() const;
    void clear();


    Node* getTop() const;
    void printStack() const; // Debug
};

#endif //STACK_H

