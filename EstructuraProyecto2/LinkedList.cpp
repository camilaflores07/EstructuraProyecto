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
    tail = nullptr; // nuevo
}

void LinkedList::push_front(int pos, int value) {
    Node* newNode = new Node(value, head);
    head = newNode;
    if (tail == nullptr) {
        // si la lista estaba vacía, head y tail apuntan al mismo nodo
        tail = newNode;
    }
}


void LinkedList::push_back(int pos, int value) {
    Node* newNode = new Node(value, nullptr);
    if (head == nullptr) {
        head = tail = newNode; // lista vacía
    } else {
        tail->next = newNode;  // conectar al final
        tail = newNode;        // actualizar tail
    }
}

void LinkedList::insert_value(int pos, int value) {
    if (pos < 0) return;

    if (pos == 0) { push_front(pos, value); return; }

    Node* current = head;
    int index = 0;
    while (current != nullptr && index < pos - 1) {
        current = current->next;
        index++;
    }

    if (current == nullptr) { // posición mayor que tamaño → al final
        push_back(pos, value);
        return;
    }

    Node* newNode = new Node(value, current->next);
    current->next = newNode;
    if (current == tail) tail = newNode; // si insertamos después del último
}

void LinkedList::remove_at(int pos) {
    if (pos < 0 || head == nullptr) return;

    if (pos == 0) {           // borrar cabeza
        pop_front();
        return;
    }

    int idx = 0;
    Node* prev = head;
    while (prev != nullptr && idx < pos - 1) {
        prev = prev->next;
        idx++;
    }
    if (prev == nullptr || prev->next == nullptr) return; // fuera de rango

    Node* target = prev->next;
    prev->next = target->next;
    if (target == tail) tail = prev;  // si borramos el último, mover tail
    delete target;
}


void LinkedList::pop_front() {
    if (head == nullptr) return;
    Node* tmp = head;
    head = head->next;
    if (head == nullptr) tail = nullptr; // quedó vacía
    delete tmp;
}

void LinkedList::pop_back() {
    if (head == nullptr) return;

    if (head->next == nullptr) { // un solo nodo
        delete head;
        head = tail = nullptr;
        return;
    }

    // buscar el penúltimo
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
        if (tmp == tail) tail = current; // si quitamos el último, mover tail
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
    return -1; // no encontrado
}


void LinkedList::print() {
    cout << "[head=" << (head ? to_string(head->data) : string("null")) << ", tail=" << (tail ? to_string(tail->data) : string("null")) << "]  ";

    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "nullptr" << endl;
}
