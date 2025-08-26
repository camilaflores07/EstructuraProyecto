#include "DoubleLinkedList.h"
#include <iostream>
using namespace std;

DoubleLinkedList::DoubleLinkedList() {
    head = nullptr;
    tail = nullptr;
}

DoubleLinkedList::~DoubleLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}

void DoubleLinkedList::push_front(int pos, int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        // Lista vacía
        head = tail = newNode;
    } else {
        // Conectar el nuevo nodo al frente
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void DoubleLinkedList::push_back(int pos, int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        // Lista vacía
        head = tail = newNode;
    } else {
        // Conectar el nuevo nodo al final
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void DoubleLinkedList::insert_value(int pos, int value) {
    if (pos < 0) return;

    if (pos == 0) {
        push_front(pos, value);
        return;
    }

    Node* current = head;
    int index = 0;

    // Buscar la posición
    while (current != nullptr && index < pos) {
        current = current->next;
        index++;
    }

    if (current == nullptr) {
        // Insertar al final
        push_back(pos, value);
        return;
    }

    // Insertar en el medio
    Node* newNode = new Node(value);
    Node* prevNode = current->prev;

    // Conectar el nuevo nodo
    newNode->next = current;
    newNode->prev = prevNode;

    // Actualizar conexiones existentes
    if (prevNode != nullptr) {
        prevNode->next = newNode;
    } else {
        head = newNode;
    }
    current->prev = newNode;
}

void DoubleLinkedList::pop_front() {
    if (head == nullptr) return;

    Node* tmp = head;

    if (head->next != nullptr) {
        head = head->next;
        head->prev = nullptr;
    } else {
        // Solo había un elemento
        head = tail = nullptr;
    }

    delete tmp;
}

void DoubleLinkedList::pop_back() {
    if (tail == nullptr) return;

    Node* tmp = tail;

    if (tail->prev != nullptr) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        // Solo había un elemento
        head = tail = nullptr;
    }

    delete tmp;
}

void DoubleLinkedList::remove_at(int pos) {
    if (pos < 0 || head == nullptr) return;

    if (pos == 0) {
        pop_front();
        return;
    }

    Node* current = head;
    int index = 0;

    // Buscar el nodo en la posición
    while (current != nullptr && index < pos) {
        current = current->next;
        index++;
    }

    if (current == nullptr) return;

    // Actualizar conexiones
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    } else {
        tail = current->prev;
    }

    delete current;
}

void DoubleLinkedList::remove_value(int value) {
    if (head == nullptr) return;

    Node* current = head;

    // Buscar el nodo con el valor
    while (current != nullptr && current->data != value) {
        current = current->next;
    }

    if (current == nullptr) return; // No encontrado

    // Actualizar conexiones
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    } else {
        tail = current->prev;
    }

    delete current;
}

int DoubleLinkedList::find(int value) {
    Node* current = head;
    int index = 0;

    while (current != nullptr) {
        if (current->data == value) return index;
        current = current->next;
        index++;
    }

    return -1;
}

void DoubleLinkedList::print() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " <-> ";
        current = current->next;
    }
    cout << "nullptr" << endl;
}

QList<int> DoubleLinkedList::toList() {
    QList<int> values;
    Node* current = head;
    while (current != nullptr) {
        values.append(current->data);
        current = current->next;
    }
    return values;
}
