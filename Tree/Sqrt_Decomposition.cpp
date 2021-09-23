/* 
Sqrt-decomposition is a ds that allows us to perform some operation in O(n^(1/2)).
To build a sqrt-decomposition, we only need to split an array into (n^(1/2)) blocks.
Every block have sum of (n^(1/2)) elements.
 */

#include <bits/stdc++.h>

using namespace std;

class Sqrt{
private:
    vector<int> elements;
    vector<int> blocks;
    int element_size;
    int block_size;
public:
    Sqrt(vector<int> elements){
        this->elements = elements;
        element_size = elements.size();
        block_size = ceil(sqrt(element_size));
        blocks.assign(block_size,0);
        for (int i=0;i<element_size;i++) blocks[i/element_size] += elements[i];
    }
    // slow
    int qry1(int l, int r){
        if (l<r) return 0;
        int sum = 0;
        for (int i=l;i<=r;){
            if (i%block_size==0 && i+block_size-1<=r){
                sum += blocks[i/block_size];
                i += block_size;
            }else{
                sum += elements[i];
                i++;
            }
        }
        return sum;
    }
    // fast
    int qry2(int l, int r){
        if (l>r) return 0;
        int sum = 0;
        int bl = l / block_size, br = r / block_size;
        if (bl==br){
            for (;l<=r;l++) sum += elements[l];
            return sum;
        }else{
            for (int i=l;i<(bl+1)*block_size;i++) sum += elements[i];
            for (int i=bl+1;i<=br-1;i++) sum += blocks[i];
            for (int i=br*block_size;i<=r;i++) sum += elements[i];
        }
        return sum;
    }
    void update(int pos, int val){
        blocks[pos/block_size] += val - elements[pos];
        elements[pos] = val;
    }
};

int main(){
    Sqrt sqrt({1,2,3,4,5,6,7,8});
    cout <<sqrt.qry2(3,6) <<endl;
    sqrt.update(3, 100);
    cout <<sqrt.qry2(2,4) <<endl;
}