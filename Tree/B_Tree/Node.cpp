#include <iostream>
#include "Node.h"

Node::Node(int degree, bool isLeaf){
    this->degree = degree;
    this->isLeaf = isLeaf;
    quantity = 0;
    keys = new int[2*degree-1];
    childs = new Node*[2*degree];
}

void Node::insertNonFull(int v){
    int i = quantity;
    if(isLeaf){
        // current position is leaf, put value in to keys
        while (--i>=0 && keys[i]>v) keys[i+1] = keys[i];
        keys[i+1] = v;
        quantity++;
    }else{
        // find position where value should go
        while (--i>=0 && keys[i]>v);
        // if child is full, child should split
        if (childs[i+1]->quantity==degree*2-1){
            split(i+1, childs[i+1]);
            if (keys[i+1]<v) i++;
        }
        childs[i+1]->insertNonFull(v); 
    }
}

void Node::split(int interval, Node* node){
    // split child diagram
    // |degree amount keys|one key|degree amount keys|
    // (child reserve keys)(parent)(sibling get keys)
    Node *tmp = new Node(node->degree, node->isLeaf);
    tmp->quantity = degree-1;
    // split all keys and childs that after degree to new sibling
    for (int i=0;i<degree-1;i++)
        tmp->keys[i] = node->keys[i+degree];
    if (!node->isLeaf){
        for (int i=0;i<degree;i++)
            tmp->childs[i] = node->childs[i+degree];
    }
    node->quantity = degree-1;
    // vacate childs position in order to put new child
    for (int i=quantity;i>=interval+1;i--) childs[quantity+1] = childs[quantity];
    childs[interval+1] = tmp;
    // vacate keys position in order to put the middle key of the child to parent
    for (int i=quantity-1;i>=interval;i--) keys[i+1] = keys[i];
    keys[interval] = node->keys[degree-1];
    quantity = quantity+1;
}

int Node::findKey(int v){
    // find the smallest index that keys[index] larger or equal to v
    int idx = 0;
    while (idx<quantity && keys[idx]<v) idx++;
    return idx;
}

void Node::remove(int v){
    int idx = findKey(v);
    if (idx<quantity && keys[idx]==v){
        // if find value, then remove it
        if (isLeaf) removeFromLeaf(idx);
        else removeFromNonLeaf(idx);
    }else{
        // the value doesn't exist in current node, but may appear in child node
        if (isLeaf){
            std::cout <<"The key " <<v <<" doesn't exist in the tree.";
            return;
        }
        // a flag records whether index equals quantity
        bool flag = (idx==quantity)?true:false;
        // fill the child if the child where the key is supposed to exist has less than degree keys
        if (childs[idx]->quantity<degree) fill(idx);
        // if flag is true and index>quantity, it means that node's childs have been merge
        if (flag && idx>quantity) childs[idx-1]->remove(v);
        else childs[idx]->remove(v);
    }
    return;
}

void Node::removeFromLeaf(int idx){
    // just move all values forward one index
    for (int i=idx+1;i<quantity;i++) keys[i-1] = keys[i];
    quantity--;
    return;
}

void Node::removeFromNonLeaf(int idx){
    int key = keys[idx];
    // if left child have enough keys, then move left maximum child key to the parent key, 
    // and remove that maximum key
    if (childs[idx]->quantity>=degree){
        int predecessor = getPredecessor(idx);
        keys[idx] = predecessor;
        childs[idx]->remove(predecessor);
    }
    // if right child have enough keys, then move right minimum child key to the parent key,
    // and remove that minimum key
    else if (childs[idx+1]->quantity>=degree){
        int successor = getSuccessor(idx);
        keys[idx] = successor;
        childs[idx+1]->remove(successor);
    }
    // both sides have no enough key, then merge two sides
    else{
        merge(idx);
        childs[idx]->remove(key);
    }
    return;
}

int Node::getPredecessor(int idx){
    // get the largest value in node's predecessor
    Node *tmp = childs[idx];
    while (!tmp->isLeaf) tmp = tmp->childs[quantity];
    return tmp->keys[quantity-1];
}

int Node::getSuccessor(int idx){
    // get the smallest value in node's successor
    Node *tmp = childs[idx+1];
    while (!tmp->isLeaf) tmp = tmp->childs[0];
    return tmp->keys[0];
}

void Node::fill(int idx){
    // if previous child have enough keys providing to current child
    if (idx!=0 && childs[idx-1]->quantity>=degree) borrowFromPrev(idx);
    // if next child have enough keys providing to current child
    else if (idx!=quantity && childs[idx+1]->quantity>=degree) borrowFromNext(idx);
    // both previous and next childs can't provide then merge
    // if idx==quantity, node will call merge(idx-1) merging idx to the idx-1
    else (idx!=quantity)?merge(idx):merge(idx-1);
    return;
}

void Node::borrowFromPrev(int idx){
    Node *child = childs[idx];
    // child will borrow one key from previous sibling
    Node *sibling = childs[idx-1];
    // move all key back so that parent's key can put in
    for (int i=child->quantity-1;i>=0;i--) child->keys[i+1] = child->keys[i];
    child->keys[0] = keys[idx-1];
    // if not leaf, move all childs back so that sibling's child can put in
    if (!child->isLeaf)
        for (int i=child->quantity;i>=0;i--) child->childs[i+1] = child->childs[i];
    if (!child->isLeaf) child->childs[0] = sibling->childs[sibling->quantity];
    // cause keys[idx-1] moved to child->keys[0], it must add one from sibling
    keys[idx-1] = sibling->keys[sibling->quantity-1];
    child->quantity++;
    sibling->quantity--;
    return;
}

void Node::borrowFromNext(int idx){
    Node *child = childs[idx];
    // child will borrow one key from next sibling
    Node *sibling = childs[idx+1];
    // put parent key to child latest key+1, put sibling foremost key to parent key
    child->keys[child->quantity] = keys[idx];
    keys[idx] = sibling->keys[0];
    // move forward all key exclusive idx0
    for (int i=1;i<sibling->quantity;i++) sibling->keys[i-1] = sibling->keys[i];
    // if not leaf, put the foremost sibling's child to the last child's child 
    if (!child->isLeaf) child->childs[child->quantity+1] = sibling->childs[0];
    if (!sibling->isLeaf)
        for (int i=1;i<=sibling->quantity;i++) sibling->childs[i-1] = sibling->childs[i];
    child->quantity++;
    sibling->quantity--;
    return;
}

void Node::merge(int idx){
    Node *child = childs[idx];
    Node *sibling = childs[idx+1];
    // put parent key to child in order to modify the least needed key amount
    child->keys[degree-1] = keys[idx];
    // put all sibling's keys and childs(if not leaf) to the child
    for (int i=0;i<sibling->quantity;i++) child->keys[degree+i] = sibling->keys[i];
    if (!child->isLeaf)
        for (int i=0;i<=sibling->quantity;i++) child->childs[degree+i] = sibling->childs[i];
    // cause have been combined, parent keys and childs must move forward
    for (int i=idx+1;i<quantity;i++) keys[i-1] = keys[i];
    for (int i=idx+2;i<=quantity;i++) childs[i-1] = childs[i];
    child->quantity+=sibling->quantity+1;
    quantity--;
    delete sibling;
    return;
}

Node* Node::search(int v){
    int idx=0;
    while (idx<quantity && keys[idx]<v) idx++;
    if (keys[idx]==v) return this;
    if (isLeaf) return NULL;
    return childs[idx]->search(v);
}

void Node::traverse(){
    for (int i=0;i<quantity;i++) std::cout <<keys[i] <<' ';
    std::cout <<std::endl;
}