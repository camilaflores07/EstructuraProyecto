#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

void LinkedList::push_front(int value) {
    Node* newNode = new Node(value, head);
    head = newNode;
}

void LinkedList::push_back(int value) {
    Node* newNode = new Node(value, nullptr);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void LinkedList::pop_front() {
    if (head == nullptr) return;
    Node* tmp = head;
    head = head->next;
    delete tmp;
}


void LinkedList::print() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "nullptr" << endl;
}
