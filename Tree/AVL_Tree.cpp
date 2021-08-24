#include <bits/stdc++.h>

using namespace std;

struct Node{
    Node *left;
    Node *right;
    char value;
    int height;
};

Node* getNewNode(char value);
Node* insert(Node *node, char value);
Node* deleteNode(Node *node, char value);
Node* findLeftMax(Node* node);
Node* rrRotate(Node *node); // anticlockwise rotation on node
Node* llRotate(Node *node); // clockwise rotation on node
Node* rlRotate(Node *node); // first clockwise rotation on node->right, then anticlockwise rotation on node
Node* lrRotate(Node *node); // first anticlockwise rotation on node->left, then clockwise rotation on node
void levelOrder(Node *node);
void renewHeight(Node *node);
int getHeight(Node *node);
int getFactor(Node *node);

Node* getNewNode(char value){
    Node *tmp=new Node();
    tmp->left=tmp->right=NULL;
    tmp->value=value;
    tmp->height=1;
    return tmp;
}

Node* insert(Node *node, char value){
    if (node==NULL) node=getNewNode(value);
    else if (value>node->value) node->right=insert(node->right, value);
    else node->left=insert(node->left, value);
    // renew height and decide whether to rotate accroding to current node factor
    // rotation is accroding to AVL data structure rule
    renewHeight(node);
    int factor=getFactor(node);
    if (factor==-2){
        if(getFactor(node->right)==-1) return rrRotate(node);
        else return rlRotate(node);
    }else if (factor==2){
        if (getFactor(node->left)==1) return llRotate(node);
        else return lrRotate(node);
    }
    return node;
}

Node* deleteNode(Node *node, char value){
    if (node==NULL) return node;
    // There are three possible situations in deleting a node
    // 1. delete node have no children
    // 2. delete node have only one children
    // 3. delete node have two childrens, and find the maximum value in left tree
    if (value<node->value) node->left=deleteNode(node->left, value);
    else if (value>node->value) node->right=deleteNode(node->right, value);
    else{
        if (node->left==NULL || node->right==NULL){
            Node *tmp;
            tmp=(node->left)?node->left:node->right;
            if (tmp!=NULL) *node=*tmp;
            else{
                tmp=node;
                node=NULL;
            }
            free(tmp);
        }else{
            Node *tmp;
            tmp=findLeftMax(node->left);
            node->value=tmp->value;
            node->left=deleteNode(node->left, tmp->value);
        }
    }
    if (node==NULL) return node;
    // rebalance AVL tree
    renewHeight(node);
    int factor=getFactor(node);
    if (factor==-2){
        if(getFactor(node->right)==-1) return rrRotate(node);
        else return rlRotate(node);
    }else if (factor==2){
        if (getFactor(node->left)==1) return llRotate(node);
        else return lrRotate(node);
    }
    return node;
}

Node* findLeftMax(Node* node){
    if (node->right) return findLeftMax(node->right);
    return node;
}

Node* rrRotate(Node *node){
    Node *tmp=node->right;
    if (tmp->left) node->right=tmp->left;
    else node->right=NULL;
    tmp->left=node;
    // need renewing height after rotate, node and tmp order is important
    renewHeight(node);
    renewHeight(tmp);
    return tmp;
}

Node* llRotate(Node *node){
    Node *tmp=node->left;
    if (tmp->right) node->left=tmp->right;
    else node->left=NULL;
    tmp->right=node;
    // need renewing height after rotate, node and tmp order is important
    renewHeight(node);
    renewHeight(tmp);
    return tmp;
}

Node* rlRotate(Node *node){
    node->right=llRotate(node->right);
    return rrRotate(node);
}

Node* lrRotate(Node *node){
    node->left=rrRotate(node->left);
    return llRotate(node);
}

void renewHeight(Node *node){
    node->height=1+max(getHeight(node->left), getHeight(node->right));
}

void levelOrder(Node* root){
    if (root==NULL){
        cout <<"Empty Tree.\n";
        return;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()){
        cout <<q.front()->value <<' ';
        if (q.front()->left) q.push(q.front()->left);
        if (q.front()->right) q.push(q.front()->right);
        q.pop();
    }
    cout <<endl;
}

int getHeight(Node *node){
    if (node==NULL) return 0;
    return node->height;
}

int getFactor(Node *node){
    return getHeight(node->left)-getHeight(node->right);
}

int main(){
    Node *root=NULL;
    string input="HIJBAECFDGKL";
    for (char c: input) root=insert(root, c);
    levelOrder(root);
    for (char c: input) root=deleteNode(root, c);
    levelOrder(root);
}
//H, I, J, B, A, E, C, F, D, G, K, L