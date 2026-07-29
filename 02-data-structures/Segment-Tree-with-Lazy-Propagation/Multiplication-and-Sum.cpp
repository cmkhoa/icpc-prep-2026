// https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/B

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct SegTree{
    int size = 0;
    vector<long long> nodes, addedVal;

    const int NEUTRAL_ELEMENT = 1;
    
    void build(int id, int l, int r){
        if (r - l == 1){
            return;
        }

        int mid = (l + r) >> 1;

        build(2 * id + 1, l, mid);
        build(2 * id + 2, mid, r);

        nodes[id] = (nodes[2 * id + 1] + nodes[2 * id + 2]) % MOD;
    }
    void build(){
        build(0, 0, size);
    }

    SegTree(int n){
        // size = 1;
        // while(size < n) size *= 2;

        // nodes.assign(2 * size, NEUTRAL_ELEMENT);
        // addedVal.assign(2 * size, NEUTRAL_ELEMENT);
        size = n;
        nodes.assign(4 * size, NEUTRAL_ELEMENT);
        addedVal.assign(4 * size, NEUTRAL_ELEMENT);
        
        build();
    }

    void mul(int u, int v, int val, int id, int l, int r){
        if (r <= u || l >= v){
            return;
        }
        
        if (l >= u && r <= v){
            addedVal[id] *= val;
            nodes[id] *= val;
            
            addedVal[id] %= MOD;
            nodes[id] %= MOD;
            return;
        }
        
        int mid = (l + r) >> 1;

        mul(u, v, val, 2 * id + 1, l, mid);
        mul(u, v, val, 2 * id + 2, mid, r);

        nodes[id] = (nodes[2 * id + 1] + nodes[2 * id + 2]) * addedVal[id] % MOD;
    }

    void mul(int u, int v, int val){
        mul(u, v, val, 0, 0, size);
    }

    long long get(int u, int v, int id, int l, int r){
        if (v <= l || u >= r){
            return 0;
        }

        if (l >= u && r <= v){
            return nodes[id];
        }

        int mid = (l + r) >> 1;
        
        return (get(u, v, 2 * id + 1, l, mid) + get(u, v, 2 * id + 2, mid, r)) * addedVal[id] % MOD;
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

    while(m--){
        int type;
        cin >> type;

        if (type == 1){
            int l, r, v;
            cin >> l >> r >> v;

            st.mul(l, r, v);
        }else{
            int u, v;
            cin >> u >> v;

            // cout << '\n';
            cout << st.get(u, v) << '\n';
        }
    }

    return 0;
}