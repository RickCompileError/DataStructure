/* 
    In this circular doubly list, any function which have parameter named index 
    will use circular way to find the position.
 */

#include <iostream>
#include "Node.h"

using namespace std;

class CircularDoublyList{
private:
    Node *head;
public:
    CircularDoublyList();
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
    void rprint();
    bool isEmpty();
};

CircularDoublyList::CircularDoublyList(){
    head = NULL; 
}

void CircularDoublyList::insertBegin(int value){
    Node *tmp = new Node(value);
    if (head == NULL){
        tmp->next = tmp;
        tmp->prev = tmp;
        head = tmp;
    }else{
        tmp->next = head;
        tmp->prev = head->prev;
        head->prev->next = tmp;
        head->prev = tmp;
    }
}

void CircularDoublyList::insertEnd(int value){
    Node *tmp = new Node(value);
    if (head == NULL){
        tmp->next = tmp;
        tmp->prev = tmp;
        head = tmp;
    }else{
        Node *last = head;
        for (;last->next!=head;) last = last->next;
        tmp->prev = last;
        tmp->next = last->next;
        last->next->prev = tmp;
        last->next = tmp;
    }
}

void CircularDoublyList::insert(int index, int value){
    Node *tmp = new Node(value);
    if (head==NULL){
        tmp->next = tmp;
        tmp->prev = tmp;
        head = tmp;
        return;
    }
    index = index%size();
    Node *cur = head;
    for (int i=0;i<index;i++) cur = cur->next;
    tmp->next = cur->next;
    tmp->prev = cur;
    cur->next->prev = tmp;
    cur->next = tmp;
}

void CircularDoublyList::deleteBegin(){
    if (head == NULL){
        cout <<"List is empty." <<endl;
        return;
    }
    Node *tmp = head;
    if (tmp->next==tmp) head = NULL;
    else{
        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
        head = tmp->next;
    }
    free(tmp);
}

void CircularDoublyList::deleteEnd(){
    if (head == NULL){
        cout <<"List is empty." <<endl;
        return;
    }
    Node *tmp = head;
    for (;tmp->next!=head;) tmp = tmp->next;
    if (tmp->next==tmp) head = NULL;
    else{
        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
    }
    free(tmp);
}

void CircularDoublyList::deleteNode(int index){
    if (head == NULL){
        cout <<"List is empty." <<endl;
        return;
    }
    index = index%size();
    Node *tmp = head;
    for (int i=0;i<index;i++) tmp = tmp->next;
    if (tmp->next==tmp) head = NULL;
    else{
        if (tmp==head) head = head->next;
        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
    }
    free(tmp);
}

int CircularDoublyList::searchByIndex(int index){
    if (head == NULL){
        cout <<"List is empty." <<endl;
        return INT_MIN;
    }
    Node *tmp = head;
    index = index%size();
    for (int i=0;i<index;i++) tmp = tmp->next;
    return tmp->value;
}

int CircularDoublyList::searchByValue(int value){
    if (head == NULL){
        printf("List is empty.\n");
        return -1;
    }
    int index = 0;
    Node *tmp = head;
    do{
        if (tmp->value==value) return index;
        tmp = tmp->next;
        index++;
    }while (tmp!=head);
    printf("Value not found.\n");
    return -1;
}

int CircularDoublyList::size(){
    if (head == NULL) return 0;
    int sz = 1;
    Node *tmp = head;
    while (tmp->next!=head){
        tmp = tmp->next;
        sz++;
    }
    return sz;
}

void CircularDoublyList::print(){
    Node *tmp = head;
    if (tmp == NULL)
        cout <<"List is empty.";
    else
        do{
            cout <<tmp->value <<' ';
            tmp = tmp->next;
        }while (tmp!=head);
    cout <<endl;
}

void CircularDoublyList::rprint(){
    Node *tmp = head;
    if (tmp == NULL)
        cout <<"List is empty.";
    else
        do{
            tmp = tmp->prev;
            cout <<tmp->value <<' ';
        }while (tmp!=head);
    cout <<endl;
}

bool CircularDoublyList::isEmpty(){
    return head == NULL;
}