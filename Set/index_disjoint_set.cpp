/*
 * merge: O(n)
 * find, equal, cardinality, singleton: O(1)
 * if all n persons merge once: O(n^2)
 */

#include <bits/stdc++.h>

using namespace std;

const int sz = 10;
int arr[sz]{};
int number[sz]{};
int groups = sz;

void initialize(){
    for (int i=0;i<sz;i++) arr[i] = i, number[i] = 1;
    groups = sz;
}

int find(int x){
    return arr[x];
}

bool equal(int x, int y){
    return arr[x]==arr[y];
}

void merge(int x, int y){
    x = arr[x];
    y = arr[y];
    if (x==y) return;
    groups--;
    // Which group should merge into the other can customize
    if (number[x]<number[y]) swap(x,y);
    for (int i=0;i<sz;i++){
        if (arr[i]==y) arr[i] = x;
    }
    number[x] += number[y];
    number[y] = 0;
}

int cardinality(int x){
    return number[arr[x]];
}

bool singleton(int x){
    return number[arr[x]]==1;
}

void print(){
    cout <<"Index:\t"; for (int i=0;i<sz;i++) cout <<i <<' '; cout <<endl;
    cout <<"Group:\t"; for (int i=0;i<sz;i++) cout <<find(i) <<' '; cout <<endl;
    cout <<"Size:\t"; for (int i=0;i<sz;i++) cout <<cardinality(i) <<' '; cout <<endl;
    cout <<"Groups:\t"; cout <<groups <<endl;
}

int main(){
    initialize();
    print();
    cout <<"\nMerge 1 9" <<endl;
    merge(1,9);
    print(); 
    cout <<"\nMerge 2 8" <<endl;
    merge(2,8);
    print();
    cout <<"\nMerge 2 7" <<endl;
    merge(2,7);
    print();
    cout <<"\nMerge 1 7" <<endl;
    merge(1,7);
    print();
    cout <<"\nIs 0 singleton?" <<endl;
    cout <<singleton(0) <<endl;
    cout <<"\nIs 8 singleton?" <<endl;
    cout <<singleton(8) <<endl;

}