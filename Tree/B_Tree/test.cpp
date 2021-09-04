#include <iostream>
#include "BTree.h"

using namespace std;

int main(){
    BTree tree(3);
    int input[]{10,20,5,6,12,30,7,17};
    for (int i: input) tree.insert(i);
    cout <<"After INSERT:\n";
    tree.traverse();
    int sch[]{10,5,12};
    for (int i: sch){
        cout <<"Search value " <<i <<":\n";
        tree.search(i)->traverse();
    }
    int del[]{10,5,12,17,6,7,20,30};
    for (int i: del){
        cout <<"Delete value " <<i <<":\n";
        tree.deleteNode(i);
        tree.traverse();
    }
}