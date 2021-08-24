#include <bits/stdc++.h>

#define sz(x) (int)x.size()

using namespace std;

// the space worst case is 4n, but in competitive question, it can just define size to the maximum size
const int mxN=1e2;
int segment[mxN];

void print(int a[], int l, int r){
    for (;l<r;) cout <<a[l++] <<' ';
    cout <<endl;
}

void modify(int node, int boundleft, int boundright, int pos, int value){
    if (boundleft==boundright){
        segment[node]=value;
    }else{
        int boundmid=(boundleft+boundright)/2;
        if (pos<=boundmid) modify(node*2, boundleft, boundmid, pos, value);
        else modify(node*2+1, boundmid+1, boundright, pos, value);
        segment[node]=segment[node*2]+segment[node*2+1];
    }
}

int sum(int node, int boundleft, int boundright, int left, int right){
    if (left>right) return 0;
    if (boundleft==left && boundright==right) return segment[node];
    int boundmid=(boundleft+boundright)/2;
    return sum(node*2, boundleft, boundmid, left, min(boundmid, right))+
            sum(node*2+1, boundmid+1, boundright, max(boundmid+1, left), right);
}

void build(int data[], int node, int boundleft, int boundright){
    if (boundleft==boundright) segment[node]=data[boundleft];
    else{
        int boundmid=(boundleft+boundright)/2;
        build(data, node*2, boundleft, boundmid);
        build(data, node*2+1, boundmid+1, boundright);
        segment[node]=segment[node*2]+segment[node*2+1];
    }
}

void run(int sz=2){
    // generate data  
    srand(time(NULL)); 
    int data[sz]{};
    for (int i=0;i<sz;i++) data[i]=rand()%10;
    cout <<"Initial data: "; print(data, 0, sz);
    
    build(data, 1, 0, sz-1);
    cout <<"Segment tree: "; print(segment, 1, 4*sz);
    
    int l=rand()%sz;
    int r=rand()%sz;
    cout <<"Sum of range " <<l <<" to " <<r <<": ";
    cout <<sum(1, 0, sz-1, l, r) <<endl;

    int pos=rand()%sz;
    int val=rand()%10;
    cout <<"Modify position: " <<pos <<", value " <<data[pos] <<" -> " <<val <<endl;
    modify(1, 0, sz-1, pos, val);
    cout <<"Segment tree after modification: "; print(segment, 1, 4*sz);
}

int main(){
    run(2);
    cout <<"---------------------seperate---------------------\n";
    run(5);
    cout <<"---------------------seperate---------------------\n";
    run(8);
    cout <<"---------------------seperate---------------------\n";
}