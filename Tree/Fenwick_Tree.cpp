/* 
Funwick tree can also called Binary Indexed Tree, or BIT for abbreviation. 
This ds is use to: (F -> reversible function, A -> an array)
    1. calculatesw the value of function F in the given range [l, r] in O(logn)
    2. updates A in O(logn)
    3. need O(n) memory
Description:
    In short, there are two bitwise operation functions {g(i),h(i)},
    which iterate from high to low and low to high respectively, to build a tree.
    As you know, we don't really need to build a tree, just use an array to maintain.
    It's hard to find minimum value between [l,r] because the way of building tree, but
    find [0,r] and sum between [l,r] is ok. (vice versa to find maximum)
fundamental approach:
    g(i) = i & (i+1), h(i) = i | (i+1);
    g(0) = 0, h(0) = 1;
    g(1) = 0, h(1) = 3;
    g(2) = 1, h(2) = 3;
    g(3) = 0, h(3) = 7;
    g(4) = 3, h(4) = 5;
    g(5) = 4, h(5) = 7;
    g(6) = 5, h(6) = 7;
    g(7) = 0, h(7) = 15;
one-based indexing approach: (Due to the function's property, we can't use idx 0)
    g(i) = i - (i & -i), h(i) = i + (i & -1);
    g(1) = 0, h(1) = 2;
    g(2) = 0, h(2) = 4;
    g(3) = 2, h(3) = 4;
    g(4) = 0, h(4) = 8;
    g(5) = 4, h(5) = 6;
    g(6) = 4, h(6) = 8;
    g(7) = 6, h(7) = 8;
    g(8) = 0, h(8) = 16;
*/

#include <bits/stdc++.h>

using namespace std;

// for point update and range query
class Fenwick_Tree1{
private:
    vector<int> vsum;
    vector<int> vmin;
    vector<int> vmax;
    int sz;
    const int INF = 0x3f3f3f3f;
public:
    Fenwick_Tree1(int n){
        sz = n;
        vsum.assign(sz, 0);
        vmin.assign(sz, INF);
        vmax.assign(sz, 0);      
    }
    Fenwick_Tree1(vector<int> v): Fenwick_Tree1(v.size()){
        for (int i=0;i<sz;i++) update(i, v[i]);
    }
    void update(int idx, int val){
        while (idx<sz){
            vsum[idx] += val;
            vmin[idx] = min(vmin[idx], val);
            vmax[idx] = max(vmax[idx], val);
            idx = idx | (idx+1);
        }
    }
    void rangeUpdate(int l, int r, int val){
        update(l, val);
        update(r+1, -val);
    }
    int getSum(int idx){
        int res = 0;
        while (idx>=0){
            res += vsum[idx];
            idx = (idx & (idx+1)) - 1;
        }
        return res;
    }
    int getSum(int l, int r){
        return getSum(r) - getSum(l-1);
    }
    int getMin(int idx){
        int res = this->INF;
        while (idx>=0){
            res = min(res, vmin[idx]);
            idx = (idx & (idx+1)) - 1;
        }
        return res;
    }
    int getMax(int idx){
        int res = 0;
        while (idx>=0){
            res = max(res, vmax[idx]);
            idx = (idx & (idx+1)) - 1;
        }
        return res;
    }
};

// for range update and point query, need to be initialized with zero
class Fenwick_Tree2{
private:
    vector<int> vsum;
    int sz;
public:
    Fenwick_Tree2(int n){
        sz = n+1;
        vsum.assign(sz, 0);   
    }
    void update(int idx, int val){
        idx++;
        while (idx<sz){
            vsum[idx] += val;
            idx += (idx & -idx);
        }
    }
    void rangeUpdate(int l, int r, int val){
        update(l, val);
        update(r+1, -val);
    }
    int query(int idx){
        idx++;
        int sum = 0;
        while (idx>0){
            sum += vsum[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }
};

int main(){
    Fenwick_Tree1 ft1({1,2,3,4,5,6,7,8});
    cout <<ft1.getSum(4, 6) <<endl;
    cout <<ft1.getMin(3) <<endl;
    cout <<ft1.getMax(7) <<endl;
    Fenwick_Tree2 ft2(8);
    ft2.rangeUpdate(1,3,5);
    ft2.rangeUpdate(1,7,10);
    cout <<ft2.query(2) <<endl;
    cout <<ft2.query(6) <<endl;
}