#ifndef NODE_H
#define NODE_H

class BTree;

class Node{
private:
    int degree;
    int quantity;
    int *keys;
    Node **childs;
    bool isLeaf;
public:
    Node(int degree, bool isLeaf);
    /* insert need functions */
    void insertNonFull(int v);
    void split(int interval, Node* node);
    /* --------------------- */
    /* delete need functions */
    int findKey(int v);
    void remove(int v);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    /* --------------------- */
    Node* search(int v);
    void traverse();
    friend class BTree;
};

#endif