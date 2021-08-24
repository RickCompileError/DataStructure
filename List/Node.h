#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node{
public:
    int value;
    Node *next;
    Node *prev;
    Node(int value){
        this->value = value;
        next = NULL;
        prev = NULL;
    }
};

#endif