#include <iostream>
#include "Node.h"

using namespace std;

class LinkedList{
private:
    Node *head;
public:
    LinkedList();
    void insertBegin(int);
    void insertEnd(int);
    void insert(int, int);
    void deleteBegin();
    void deleteEnd();
    void deleteNode(int);
    int searchByIndex(int);
    int searchByValue(int);
    int size();
    void print();
    bool isEmpty();
};

LinkedList::LinkedList(){
    head = NULL; 
}

void LinkedList::insertBegin(int value){
    Node *tmp = new Node(value);
    if (head == NULL) head = tmp;
    else{
        tmp->next = head;
        head = tmp;
    }
}

void LinkedList::insertEnd(int value){
    Node *tmp = new Node(value);
    if (head == NULL) head = tmp;
    else{
        Node *last = head;
        for (;last->next;) last = last->next;
        last->next = tmp;
    }
}

void LinkedList::insert(int index, int value){
    Node *tmp = new Node(value);
    Node *cur = head;
    for (int i=0;i<index && cur;i++) cur = cur->next;
    if (cur){
        tmp->next = cur->next;
        cur->next = tmp;
    }else{
        printf("Index %d is larger than list size.\n", index);
    }
}

void LinkedList::deleteBegin(){
    if (head == NULL){
        cout <<"List is empty." <<endl;
        return;
    }
    Node *tmp = head;
    head = head->next;
    free(tmp);
}

void LinkedList::deleteEnd(){
    if (head == NULL){
        cout <<"List is empty." <<endl;
        return;
    }
    Node *cur = head, *prev = NULL;
    for (;cur->next;){
        prev = cur;
        cur = cur->next;
    }
    if (prev != NULL) prev->next = cur->next;
    else head = head->next;
    free(cur);
}

void LinkedList::deleteNode(int index){
    if (head == NULL){
        cout <<"List is empty." <<endl;
        return;
    }
    Node *cur = head, *prev = NULL;
    for (int i=0;i<index && cur;i++){
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL){
        printf("Index %d is larger than list size.\n", index);
    }else{
        if (prev != NULL) prev->next = cur->next;
        free(cur);
    }
}

int LinkedList::searchByIndex(int index){
    if (head == NULL){
        cout <<"List is empty." <<endl;
        return INT_MIN;
    }
    Node *tmp = head;
    for (int i=0;i<index && tmp;i++) tmp = tmp->next;
    if (tmp == NULL){
        printf("Index %d is larger than list size.\n", index);
        return INT_MIN;
    }
    return tmp->value;
}

int LinkedList::searchByValue(int value){
    int index = 0;
    Node *tmp = head;
    for (;tmp && tmp->value!=value;index++) tmp = tmp->next;
    if (tmp == NULL){
        printf("Value not found.\n");
        return -1;
    }
    return index;
}

int LinkedList::size(){
    int sz = 0;
    Node *tmp = head;
    for (;tmp;sz++) tmp = tmp->next;
    return sz;
}

void LinkedList::print(){
    Node *tmp = head;
    if (tmp == NULL)
        cout <<"List is empty.";
    else
        for (;tmp;tmp=tmp->next) cout <<tmp->value <<' ';
    cout <<endl;
}

bool LinkedList::isEmpty(){
    return head == NULL;
}