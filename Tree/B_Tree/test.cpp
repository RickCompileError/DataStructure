#include <iostream>
#include "BTree.h"

using namespace std;

int main(){
    BTree tree(3);
    int input[]{10,20,5,6,12,30,7,17};
    for (int i: input) tree.insert(i);
    tree.traverse();
    int del[]{10,5,12,17,6,7,20,30};
    for (int i: del){
        tree.deleteNode(i);
        tree.traverse();
    }
}