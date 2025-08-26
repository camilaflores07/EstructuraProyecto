#ifndef NODE_H
#define NODE_H

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int d, Node* n = nullptr, Node* p = nullptr) {
        data = d;
        next = n;
        prev = p;
    }
};

#endif // NODE_H
