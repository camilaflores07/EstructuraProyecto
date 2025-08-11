#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

void LinkedList::push_front(int pos, int value) {
    Node* newNode = new Node(value, head);
    head = newNode;
    if (tail == nullptr) {
        tail = newNode;
    }
}

void LinkedList::push_back(int pos, int value) {
    Node* newNode = new Node(value, nullptr);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void LinkedList::insert_value(int pos, int value) {
    if (pos < 0) return;

    if (pos == 0) {
        push_front(pos, value);
        return;
    }

    Node* current = head;
    int index = 0;
    while (current != nullptr && index < pos - 1) {
        current = current->next;
        index++;
    }

    if (current == nullptr) {
        push_back(pos, value);
        return;
    }

    Node* newNode = new Node(value, current->next);
    current->next = newNode;
    if (current == tail) tail = newNode;
}

void LinkedList::remove_at(int pos) {
    if (pos < 0 || head == nullptr) return;

    if (pos == 0) {
        pop_front();
        return;
    }

    int idx = 0;

    Node* prev = head;
    while (prev != nullptr && idx < pos - 1) {
        prev = prev->next;
        idx++;
    }
    if (prev == nullptr || prev->next == nullptr) return;

    Node* target = prev->next;
    prev->next = target->next;
    if (target == tail) tail = prev;
    delete target;
}

void LinkedList::pop_front() {
    if (head == nullptr) return;
    Node* tmp = head;
    head = head->next;
    if (head == nullptr) tail = nullptr;
    delete tmp;
}

void LinkedList::pop_back() {
    if (head == nullptr) return;

    if (head->next == nullptr) {
        delete head;
        head = tail = nullptr;
        return;
    }


    Node* current = head;
    while (current->next != tail) {
        current = current->next;
    }
    delete tail;
    tail = current;
    tail->next = nullptr;
}

void LinkedList::remove_value(int value) {
    if (head == nullptr) return;

    if (head->data == value) {
        pop_front();
        return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Node* tmp = current->next;
        current->next = tmp->next;
        if (tmp == tail) tail = current;
        delete tmp;
    }
}

int LinkedList::find(int value) {
    Node* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->data == value) return index;
        current = current->next;
        index++;
    }
    return -1;
}

void LinkedList::print() {

    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "nullptr" << endl;
}

QList<int> LinkedList::toList() {
    QList<int> values;
    Node* current = head;
    while (current != nullptr) {
        values.append(current->data);
        current = current->next;
    }
    return values;
}

