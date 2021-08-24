#include <bits/stdc++.h>

using namespace std;

void print(int arr[], int size){
    for (int i=0;i<size;i++) cout <<arr[i] <<' ';
    cout <<endl;
}

void siftdown(int arr[], int size, int ind){
    int parent=ind,child;
    bool stop=false;
    while (parent*2<size && !stop){
        if (parent*2+2<size && arr[parent*2+1]<arr[parent*2+2]) child=parent*2+2;
        else child=parent*2+1;
        if (arr[parent]<arr[child]){
            swap(arr[parent],arr[child]);
            parent=child;
        }
        else stop=true;
    }
}

void removeKey(int arr[], int size){
    for (int i=size-1;i>=0;i--){
        swap(arr[0],arr[i]);
        siftdown(arr,i-1,0);
        // cout <<size-i <<". "; print(arr,size);
    }
}

void makeHeap(int arr[], int size){
    for (int i=size/2;i>=0;i--){
        siftdown(arr,size,i);
    }
}

void sort(int arr[], int size){
    cout <<"Origin   : ", print(arr,size);
    makeHeap(arr,size);
    cout <<"Heap Down: ", print(arr,size);
    removeKey(arr,size);
    cout <<"Sort Done: ", print(arr,size);
}

int main()
{
    srand(time(NULL));
    int sz=10;
    int arr[sz];
    for (int i=0;i<sz;i++) arr[i]=rand()%20;
    sort(arr,sz);
}