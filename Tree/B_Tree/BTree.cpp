#include <iostream>
#include <queue>
#include "BTree.h"

#define pr pair<Node*, int>

using namespace std;

BTree::BTree(int degree):root{NULL},degree{degree}{}

void BTree::insert(int v){
    if (!root){
        // if root is null, new a Node object to it
        root = new Node(degree, true);
        root->keys[0] = v;
        root->quantity++;
    }else{
        // if root is not null, check whether
        // root keys already full
        if (root->quantity==2*degree-1){
            Node *tmp = new Node(degree, false);
            tmp->childs[0] = root;
            tmp->split(0, root);
            // choose which child inserted value should go
            int i = 0;
            if (tmp->keys[0]<v) i = 1;
            tmp->childs[i]->insertNonFull(v);
            root = tmp;
        } 
        else root->insertNonFull(v);
    }
}

void BTree::deleteNode(int v){
    if (!root){
        cout <<"Empty Tree." <<endl;
        return;
    }
    root->remove(v);
    if (root->quantity==0){
        Node *tmp = root;
        if (root->isLeaf) root = NULL;
        else root = root->childs[0];
        delete tmp;
    }
    return;
}

Node* BTree::search(int v){
    return NULL;
}

void BTree::traverse(){
    if (root == NULL){
        cout <<"Empty tree." <<endl;
        return;
    }
    queue<pr> q;
    q.push(make_pair(root, 1));
    while (!q.empty()){
        pr tmp = q.front();
        q.pop();
        cout <<"[" <<tmp.second <<"]: ";
        tmp.first->traverse();
        if (!tmp.first->isLeaf)
            for (int i=0;i<=tmp.first->quantity;i++)
                q.push(make_pair(tmp.first->childs[i], tmp.second+1));
    }
}
