#include <iostream>
#include "BTree.h"

using namespace std;

int main(){
    BTree tree(3);
    int input[]{10,20,5,6,12,30,7,17};
    for (int i: input) tree.insert(i);
    tree.traverse();
    tree.deleteNode(10);
    tree.traverse();
}