#include "Queue.h"
#include <iostream>
using std::cout;
using std::endl;


Queue::Queue() {
    front = nullptr;
    rear = nullptr;
    size = 0;
}

Queue::~Queue() {
    clear();
}

void Queue::enqueue(int value) {
    Node* newNode = new Node(value);

    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

int Queue::dequeue() {
    if (isEmpty()) {
        std::cout << "Esta Vacio" << std::endl;
        return -1; // Valor por defecto cuando está vacía
    }

    Node* temp = front;
    int value = temp->data;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    size--;
    return value;
}

int Queue::peek() const {
    if (isEmpty()) {
        std::cout << "Esta Vacio" << std::endl;
        return -1;
    }
    return front->data;
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

int Queue::getSize() const {
    return size;
}

void Queue::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}

Node* Queue::getFront() const {
    return front;
}
