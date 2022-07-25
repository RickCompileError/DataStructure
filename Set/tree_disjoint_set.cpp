/*
 * merge, find, equal, cardinality, singleton: O(nlogn)
 * if all n persons merge once: O(a(n)), a(n) is Ackermann function f(n,n)
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
    return (x==arr[x]?x:arr[x]=find(arr[x]));
}

bool equal(int x, int y){
    return find(x)==find(y);
}

void merge(int x, int y){
    x = find(x);
    y = find(y);
    if (x==y) return;
    groups--;
    // Which group should merge into the other can customize
    if (number[x]<number[y]) swap(x,y);
    number[x] += number[y];
    number[y] = 0;
    arr[y] = x;
}

// The return value is the size of the group i joined
int cardinality(int x){
    return number[find(x)];
}

bool singleton(int x){
    return number[find(x)]==1;
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