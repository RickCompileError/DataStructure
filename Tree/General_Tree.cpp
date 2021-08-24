#include <bits/stdc++.h>

using namespace std;

struct Node{
    int value;
    struct Node* left;
    struct Node* right;
    Node(int value){
        this->value = value;
        left = NULL;
        right = NULL;
    }
};

void addNode(Node* currentNode, Node* node){
    Node* tmpx=currentNode;
    Node* tmpy=NULL;
    while (tmpx!=NULL){
        tmpy=tmpx;
        if (node->value<=tmpx->value) tmpx=tmpx->left;
        else tmpx=tmpx->right;
    }
    if (node->value<=tmpy->value) tmpy->left=node;
    else tmpy->right=node;
}

void preorder(Node* node){
    if (node==NULL) return;
    cout <<node->value <<' ';
    preorder(node->left);
    preorder(node->right);
}

void inorder(Node* node){
    if (node==NULL) return;
    inorder(node->left);
    cout <<node->value <<' ';
    inorder(node->right);
}

void postorder(Node* node){
    if (node==NULL) return;
    postorder(node->left);
    postorder(node->right);
    cout <<node->value <<' ';
}

int main()
{
    Node* rootNode=new Node(5);
    for (int i=1;i<=10;i++) addNode(rootNode, new Node(i));
    preorder(rootNode); cout <<endl;
    inorder(rootNode); cout <<endl;
    postorder(rootNode); cout <<endl;
    cout <<"Done";
}