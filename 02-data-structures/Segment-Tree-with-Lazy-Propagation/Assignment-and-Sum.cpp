// https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/A

#include <bits/stdc++.h>
using namespace std;

struct SegTree{
    int size = 0;
    vector<long long> nodes;

    SegTree(int n){
        size = 1;
        while(size < n) size *= 2;

        nodes.assign(2 * size, INT_MIN);
    }

    void propagate(int id, int l, int r){
        if (nodes[id] == INT_MIN) return;

        if (r - l == 1){
            return;
        }
        
        nodes[2 * id + 1] = nodes[id];
        nodes[2 * id + 2] = nodes[id];
        nodes[id] = INT_MIN;
    }

    void modify(int u, int v, int val, int id, int l, int r){
        propagate(id, l, r);
        if (r <= u || l >= v){
            return;
        }

        if (l >= u && r <= v){
            // cout << "[" << l << " " << r << "), ";
            nodes[id] = val;
            return;
        }

        int mid = (l + r) >> 1;

        modify(u, v, val, 2 * id + 1, l, mid);
        modify(u, v, val, 2 * id + 2, mid, r);
    }

    void modify(int u, int v, int val){
        modify(u, v, val, 0, 0, size);
    }

    long long get(int pos, int id, int l, int r){
        propagate(id, l, r);

        // if (pos < l || pos >= r){
        //     return 0;
        // }

        if (r - l == 1){
            return nodes[id];
        }

        int mid = (l + r) >> 1;

        long long res;
        if (pos < mid){
            res = get(pos, 2 * id + 1, l, mid);
        }else{
            res = get(pos, 2 * id + 2, mid, r);
        }
        
        return res;
    }

    long long get(int pos){
        return get(pos, 0, 0, size); 
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    SegTree st(n);
    st.modify(0, st.size, 0);
    // cout << '\n';

    while(m--){
        int type;
        cin >> type;

        if (type == 1){
            int l, r, v;
            cin >> l >> r >> v;

            st.modify(l, r, v);
        }else{
            int pos;
            cin >> pos;

            // cout << '\n';
            cout << st.get(pos) << '\n';
        }
    }

    return 0;
}