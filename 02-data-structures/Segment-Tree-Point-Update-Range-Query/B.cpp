// https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/B

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 4 * N; 

int a[N];

struct SegTree{
    int size;
    vector<long long> nodes;

    SegTree(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        nodes.assign(2 * size, 0);
    }

    void build(int id, int l, int r){
        if (r - l == 1){
            nodes[id] = a[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(2 * id + 1, l, mid);
        build(2 * id + 2, mid, r);

        nodes[id] = min(nodes[2 * id + 1], nodes[2 * id + 2]);
    }

    void build(){
        build(0, 0, size);
    }

    // [l, r)
    void set(int pos, int value, int id, int l, int r){
        if (pos < l || pos >= r) return;
        if (r - l == 1){
            nodes[id] = value;
            return;
        }

        int mid = (l + r) >> 1;

        set(pos, value, 2 * id + 1, l, mid);
        set(pos, value, 2 * id + 2, mid, r);

        nodes[id] = min(nodes[2 * id + 1], nodes[2 * id + 2]); // change this depending on problems
    }

    void set(int pos, int value){
        set(pos, value, 0, 0, size);
    }
    
    // (l, r)
    long long get(int u, int v, int id, int l, int r){
        if (l >= v || r <= u){
            return INT64_MAX;
        }
        if (r <= v && l >= u){
            return nodes[id];
        }
        
        int mid = (l + r) >> 1;
        
        return min(get(u, v, 2 * id + 1, l, mid), get(u, v, 2 * id + 2, mid, r));
    }

    long long get(int u, int v){
        return get(u, v, 0, 0, size);
    }
};  

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    SegTree st(n);

    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    st.build();

    while(m--){
        int type, x, y;
        cin >> type >> x >> y;

        if (type == 1){
            st.set(x, y);
        }else{
            cout << st.get(x, y) << '\n';
        }
    }

    return 0;
}