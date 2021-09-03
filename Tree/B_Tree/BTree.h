#ifndef BTREE_H
#define BTREE_H

#include "Node.h"

class BTree{
private:
    Node *root;
    int degree;
public:
    BTree(int degree);
    void insert(int v);
    void deleteNode(int v);
    Node* search(int v);
    void traverse();
};

#endif