// All value in set by default is specified to null,
// so it's forbidden to find the set that not yet make.
/*******************************************************************************
Complexity: 
    Naive DSU: find_set O(n)
    Path compression: find_set O(logn)
    Union by size/rank: find_set O(α(n)), if not use compression will be O(logn)
    note: α(n) is the inverse Ackermann function, a very slowly growing function,
            for all n < 10^600 doesn't exceed 4
    Explicitly list: find_set O(1)
*******************************************************************************/

#include <bits/stdc++.h>

using namespace std;

class Naive_DSJ{
protected:
    int sz;
    int *parent;
public:
    Naive_DSJ(int n){
        sz = n;
        parent = new int[n];
    }
    virtual void make_set(int v){
        parent[v] = v;
    }
    virtual int find_set(int v){
        if (parent[v]==v) return v;
        return find_set(parent[v]);
    }
    virtual void union_sets(int a, int b){
        a = find_set(a);
        b = find_set(b);
        if (a!=b) parent[b] = a;
    }
    void print(){
        for (int i=0;i<sz;i++) cout <<parent[i] <<' ';
        cout <<endl;
    }
};

class Compression_DSJ: public Naive_DSJ{
public:
    Compression_DSJ(int n): Naive_DSJ(n){}
    int find_set(int v){
        if (parent[v]==v) return v;
        return parent[v] = find_set(parent[v]);
    }
};

class Size_DSJ: public Compression_DSJ{
private:
    int *size;
public:
    Size_DSJ(int n): Compression_DSJ(n){
        size = new int[n];
    }
    void make_set(int v){
        parent[v] = v;
        size[v] = 1;
    }
    void union_sets(int a, int b){
        a = find_set(a);
        b = find_set(b);
        if (a!=b){
            if (size[a]<size[b]) swap(a,b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

class Depth_DSJ: public Compression_DSJ{
private: 
    int *depth;
public:
    Depth_DSJ(int n): Compression_DSJ(n){
        depth = new int[n];
    }
    void make_set(int v){
        parent[v] = v;
        depth[v] = 0;
    }
    void union_sets(int a, int b){
        a = find_set(a);
        b = find_set(b);
        if (a!=b){
            if (depth[a]<depth[b]) swap(a,b);
            parent[b] = a;
            if (depth[a]==depth[b]) depth[a]++;
        }
    }
};

class List_DSJ: public Naive_DSJ{
private:
    vector<int> *ls;
public:
    List_DSJ(int n): Naive_DSJ(n){
        ls = new vector<int>[n];
    }
    void make_set(int v){
        ls[v] = vector<int>(1,v);
        parent[v] = v;
    }
    void union_sets(int a, int b){
        a = find_set(a);
        b = find_set(b);
        if (a!=b){
            if (ls[a].size()<ls[b].size()) swap(a,b);
            while (!ls[b].empty()){
                int v = ls[b].back();
                ls[b].pop_back();
                parent[v] = a;
                ls[a].push_back(v);
            }
        }
    }
};

void test(Naive_DSJ *s, vector<int> input){
    for (int i=0;i<input.size();i++) s->make_set(input[i]);
    s->union_sets(5,7);
    s->union_sets(4,6);
    s->union_sets(2,5);
    s->union_sets(2,4);
    s->union_sets(1,3);
    s->union_sets(1,2);
    s->union_sets(0,1);
    s->print();
}

int main(){
    vector<int> input{0,1,2,3,4,5,6,7};
    Naive_DSJ *nd;
    nd = new Naive_DSJ(input.size());
    test(nd, input);
    nd = new Compression_DSJ(input.size());
    test(nd, input);
    nd = new Size_DSJ(input.size());
    test(nd, input);
    nd = new Depth_DSJ(input.size());
    test(nd, input);
    nd = new List_DSJ(input.size());
    test(nd, input);
}