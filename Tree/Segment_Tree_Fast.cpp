#include <bits/stdc++.h>

using namespace std;

const int mxN=1e5, INF=0x3f3f3f3f;
int n;
struct Node{
    int val;
    int mx;
    int mn;
    int lz;
} st[4*mxN];

void print(int a[], int start, int end){
    for (;start<end;) cout <<a[start++] <<' ';
    cout <<endl;
}

void print(int start, int end){
    cout <<endl <<"\tvalue: ";
    for (int i=start;i<end;i++) cout <<st[i].val <<' ';
    cout <<endl <<"\tmax: ";
    for (int i=start;i<end;i++) cout <<st[i].mx <<' ';
    cout <<endl <<"\tmin: ";
    for (int i=start;i<end;i++) cout <<st[i].mn <<' ';
    cout <<endl <<"\tlazy: ";
    for (int i=start;i<end;i++) cout <<st[i].lz <<' ';
    cout <<endl;
}

void updateNode(int val, int i){
    st[i].val=val;
    st[i].mx=val;
    st[i].mn=val;
}

void updateRange(int i){
    st[i].val=st[i*2].val+st[i*2+1].val;
    st[i].mx=max(st[i*2].mx, st[i*2+1].mx);
    st[i].mn=min(st[i*2].mn, st[i*2+1].mn);
}

void app(int i, int val, int lb, int rb){
    st[i].val+=val*(rb-lb+1);
    st[i].mx+=val;
    st[i].mn+=val;
    st[i].lz=val;
}

void push(int i, int lb, int mb, int rb){
    app(2*i, st[i].lz, lb, mb);
    app(2*i+1, st[i].lz, mb+1, lb);
    st[i].lz=0;
}

void singleUpdate(int ind, int val, int i=1, int lb=0, int rb=n-1){
    if (lb==rb){
        updateNode(val, i);
        return;
    }
    int mb=(lb+rb)/2;
    push(i, lb, mb, rb);
    if (ind<=mb) singleUpdate(ind, val, i*2, lb, mb);
    else singleUpdate(ind, val, i*2+1, mb+1, rb);
    updateRange(i);
}

void multiUpdate(int l, int r, int val, int i=1, int lb=0, int rb=n-1){
    if (l<=lb && r>=rb){
        app(i, val, lb, rb);
        return;
    }
    int mb=(lb+rb)/2;
    push(i, lb, mb, rb);
    if (l<=mb) multiUpdate(l, r, val, i*2, lb, mb);
    if (r>mb) multiUpdate(l, r, val, i*2+1, mb+1, rb);
    updateRange(i);
}

int sum(int l, int r, int i=1, int lb=0, int rb=n-1){
    if (l<=lb && r>=rb) return st[i].val;
    int mb=(lb+rb)/2;
    push(i, lb, mb, rb);
    return l<=mb?sum(l, r, i*2, lb, mb):0+
            r>mb?sum(l, r, i*2+1, mb+1, rb):0;
}

int findMax(int l, int r, int i=1, int lb=0, int rb=n-1){
    if (l<=lb && r>=rb) return st[i].mx;
    int mb=(lb+rb)/2;
    push(i, lb, mb, rb);
    return max(l<=mb?findMax(l, r, i*2, lb, mb):-1,
                r>mb?findMax(l, r, i*2+1, mb+1, rb):-1);
}

int findMin(int l, int r, int i=1, int lb=0, int rb=n-1){
    if (l<=lb && r>=rb) return st[i].mn;
    int mb=(lb+rb)/2;
    push(i, lb, mb, rb);
    return min(l<=mb?findMin(l, r, i*2, lb, mb):INF,
                r>mb?findMin(l, r, i*2+1, mb+1, rb):INF);
}

void run(int quantity){
    n=quantity;
    int number[n];
    srand(time(NULL));
    int num;
    for (int i=0;i<n;i++){
        number[i]=rand()%11;
        singleUpdate(i, number[i]);
    }
    cout <<"Number: ", print(number, 0, n);
    cout <<"Segment: ", print(1, 4*n);
    int l=rand()%n;
    int r=rand()%n;
    if (l>r) swap(l,r);
    int val=rand()%11;
    cout <<"Plus range " <<l <<" ~ " <<r <<" value " <<val <<endl;
    multiUpdate(l, r, val);
    cout <<"Update Segment: ", print(1, 4*n);
    l=rand()%n;
    r=rand()%n;
    if (l>r) swap(l,r);
    cout <<"Sum range " <<l <<" ~ " <<r <<" = " <<sum(l,r) <<endl;
    cout <<"Max range " <<l <<" ~ " <<r <<" = " <<findMax(l,r) <<endl;
    cout <<"Min range " <<l <<" ~ " <<r <<" = " <<findMin(l,r) <<endl;
}

int main(){
    run(4);
}
