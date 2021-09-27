#include <bits/stdc++.h>

using namespace std;

void print(int arr[], int size){
    for (int i=1;i<=size;i++) cout <<arr[i] <<' ';
    cout <<endl;
}

void siftdown(int arr[], int size, int ind){
    int parent=ind,child;
    bool stop=false;
    while (parent*2<=size && !stop){
        if (parent*2+1<=size && arr[parent*2]<arr[parent*2+1]) child=parent*2+1;
        else child=parent*2;
        if (arr[parent]<arr[child]){
            swap(arr[parent],arr[child]);
            parent=child;
        }
        else stop=true;
    }
}

void removeKey(int arr[], int size){
    for (int i=size;i>=1;i--){
        swap(arr[1],arr[i]);
        siftdown(arr,i-1,1);
        // cout <<size-i <<". "; print(arr,size);
    }
}

void makeHeap(int arr[], int size){
    for (int i=size/2;i>=1;i--){
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
    int arr[sz+1];
    for (int i=1;i<=sz;i++) arr[i]=rand()%20;
    sort(arr,sz);
}