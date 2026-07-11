// https://codeforces.com/contest/597/problem/C

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 4 * N, K = 10 + 5; 

int a[N];

struct SegTree{
    int size;
    vector<long long> nodes;

    SegTree(int n){
        // size = 1;
        // while(size < n){
        //     size *= 2;
        // }

        // nodes.assign(2 * size, 0);
        size = n;
        nodes.assign(4 * size, 0);
    }

    void build(int id, int l, int r){
        if (r - l == 1){
            nodes[id] = a[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(2 * id + 1, l, mid);
        build(2 * id + 2, mid, r);

        nodes[id] = nodes[2 * id + 1] + nodes[2 * id + 2];
    }

    void build(){
        build(0, 0, size);
    }

    // [l, r)
    void set(int pos, long long value, int id, int l, int r){
        if (pos < l || pos >= r) return;
        if (r - l == 1){
            nodes[id] = value;
            return;
        }

        int mid = (l + r) >> 1;

        set(pos, value, 2 * id + 1, l, mid);
        set(pos, value, 2 * id + 2, mid, r);

        nodes[id] = nodes[2 * id + 1] + nodes[2 * id + 2]; // change this depending on problems
    }

    void set(int pos, long long value){
        set(pos, value, 0, 0, size);
    }
    
    // (l, r)
    long long get(int u, int v, int id, int l, int r){
        if (l >= v || r <= u){
            return 0;
        }
        if (r <= v && l >= u){
            return nodes[id];
        }
        
        int mid = (l + r) >> 1;
        
        return get(u, v, 2 * id + 1, l, mid) + get(u, v, 2 * id + 2, mid, r);
    }
    
    long long get(int u, int v){
        return get(u, v, 0, 0, size);
    }
};  

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    SegTree pre(n + 1), cur(n + 1), upd(n + 1);
    for (int i = 0; i < n; i++){
        pre.set(a[i], 1);
    }

    for (int i = 2; i <= k + 1; i++){
        for (int j = 0; j < i - 1; j++){
            upd.set(a[j], pre.get(a[j], a[j] + 1));
            // cout << "k = " << i << " : index = " << j << "; sum [0, " << a[j] << "): " << upd.get(0, a[j]) << '\n';
        }
        for (int j = i - 1; j < n; j++){
            // cout << "k = " << i << " : index = " << j << "; sum [0, " << a[j] << "): " << upd.get(0, a[j]) << '\n';
            cur.set(a[j], upd.get(0, a[j]));
            upd.set(a[j], pre.get(a[j], a[j] + 1));
        }

        // cout << '\n';
        swap(pre.nodes, cur.nodes);
        fill(cur.nodes.begin(), cur.nodes.end(), 0);
        fill(upd.nodes.begin(), upd.nodes.end(), 0);
    }

    cout << pre.get(0, n + 2);

    return 0;
}