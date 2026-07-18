#include <bits/stdc++.h>
using namespace std;

struct SegTree{
    int size = 0;
    vector<long long> nodes;

    SegTree(int n){
        size = 1;
        while(size < n) size >>= 1;

        nodes.assign(size, 0);
    }

    void add(int u, int v, int id, int l, int r){
        if (pos < l || pos >= r){
            return;
        }

        if (r - l == 1){
            nodes[id] = val;
            return;
        }

        int mid = (l + r) >> 1;

        add(pos, val, 2 * id + 1, l, mid);
        add(pos, val, 2 * id + 2, mid, r);

        nodes[id] = nodes[2 * id + 1] + nodes[2 * id + 2];
    }

    void add(int u, int v){
        add(u, v, 0, 0, size);
    }
};

int main(){

}