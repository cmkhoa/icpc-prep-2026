// https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/C

#include <bits/stdc++.h>
using namespace std;

struct SegTree{
    int size = 0;
    vector<pair<int ,int>> nodes;

    SegTree(int n){
        size = 1;
        while(size < n) size *= 2;

        nodes.assign(2 * size, {INT_MAX, 0});
    }

    void add(int u, int v, pair<int, int> val, int id, int l, int r){
        if (r <= u || l >= v){
            return;
        }

        if (l >= u && r <= v){
            // cout << "[" << l << " " << r << "), ";
            nodes[id] = val;
            return;
        }

        int mid = (l + r) >> 1;

        add(u, v, val, 2 * id + 1, l, mid);
        add(u, v, val, 2 * id + 2, mid, r);
    }

    void add(int u, int v, pair<int, int> val){
        add(u, v, val, 0, 0, size);
    }

    pair<int, int> get(int pos, int id, int l, int r){
        if (pos < l || pos >= r){
            return {INT_MAX, 0};
        }

        if (r - l == 1){
            return nodes[id];
        }

        int mid = (l + r) >> 1;
        
        return min({get(pos, 2 * id + 1, l, mid), get(pos, 2 * id + 2, mid, r), nodes[id]});
    }

    long long get(int pos){
        return get(pos, 0, 0, size).second; 
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

            st.add(l, r, {m, v});
        }else{
            int pos;
            cin >> pos;

            // cout << '\n';
            cout << st.get(pos) << '\n';
        }
    }

    return 0;
}