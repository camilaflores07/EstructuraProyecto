#ifndef NODE_H
#define NODE_H

struct Node {
    int data;
    Node* next;

    Node(int d, Node* n = nullptr) {
        data = d;
        next = n;
    }
};

#endif // NODE_H
