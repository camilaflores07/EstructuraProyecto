#include "Stack.h"
#include <iostream>

Stack::Stack() : top(nullptr), size(0) {
}

Stack::~Stack() {
    clear();
}

void Stack::push(int data) {
    Node* newNode = new Node(data, top);
    top = newNode;
    size++;
}

int Stack::pop() {
    if (isEmpty()) {
        return -1; // Valor por defecto cuando stack está vacío
    }

    Node* nodeToDelete = top;
    int data = top->data;
    top = top->next;
    delete nodeToDelete;
    size--;

    return data;
}

int Stack::peek() const {
    if (isEmpty()) {
        return -1; // Valor por defecto cuando stack está vacío
    }

    return top->data;
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

int Stack::getSize() const {
    return size;
}

void Stack::clear() {
    while (!isEmpty()) {
        pop();
    }
}

Node* Stack::getTop() const {
    return top;
}

void Stack::printStack() const {
    std::cout << "Stack (top -> bottom): ";
    Node* current = top;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
