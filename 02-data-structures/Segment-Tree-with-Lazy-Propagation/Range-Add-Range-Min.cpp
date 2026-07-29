// https://judge.yosupo.jp/problem/range_add_range_min

#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

int a[N];

struct SegTree{
    int size = 0;
    vector<long long> nodes, addedVal;

    const int NEUTRAL_ELEMENT = 0;

    SegTree(int n){
        // size = 1;
        // while(size < n) size *= 2;

        // nodes.assign(2 * size, NEUTRAL_ELEMENT);
        // addedVal.assign(2 * size, NEUTRAL_ELEMENT);
        size = n;
        nodes.assign(4 * size, NEUTRAL_ELEMENT);
        addedVal.assign(4 * size, NEUTRAL_ELEMENT);
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

    void add(int u, int v, int val, int id, int l, int r){
        if (r <= u || l >= v){
            return;
        }
        
        if (l >= u && r <= v){
            addedVal[id] += val;
            nodes[id] += val;
            return;
        }
        
        int mid = (l + r) >> 1;

        add(u, v, val, 2 * id + 1, l, mid);
        add(u, v, val, 2 * id + 2, mid, r);

        nodes[id] = min(nodes[2 * id + 1], nodes[2 * id + 2]) + addedVal[id];
    }

    void add(int u, int v, int val){
        add(u, v, val, 0, 0, size);
    }

    long long get(int u, int v, int id, int l, int r){
        if (v <= l || u >= r){
            return INT64_MAX;
        }

        if (l >= u && r <= v){
            return nodes[id];
        }

        int mid = (l + r) >> 1;
        
        return min(get(u, v, 2 * id + 1, l, mid), get(u, v, 2 * id + 2, mid, r)) + addedVal[id];
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

    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    SegTree st(n);
    st.build();

    while(m--){
        int type;
        cin >> type;

        if (type){
            int l, r;
            cin >> l >> r;

            cout << st.get(l, r) << '\n';
        }else{
            int l, r, x;
            cin >> l >> r >> x;

            st.add(l, r, x);
        }
    }

    return 0;
}