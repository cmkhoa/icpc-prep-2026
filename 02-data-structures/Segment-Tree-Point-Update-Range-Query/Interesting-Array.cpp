// https://codeforces.com/contest/482/problem/B

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int ps[N][30];  

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

    void build(const vector<int> &a, int id, int l, int r){
        if (r - l == 1){
            nodes[id] = a[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(a, 2 * id + 1, l, mid);
        build(a, 2 * id + 2, mid, r);

        nodes[id] = nodes[2 * id + 1] & nodes[2 * id + 2];
    }

    void build(const vector<int> &a){
        build(a, 0, 0, size);
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

        nodes[id] = nodes[2 * id + 1] & nodes[2 * id + 2]; // change this depending on problems
    }

    void set(int pos, int value){
        set(pos, value, 0, 0, size);
    }
    
    // (l, r)
    long long get(int u, int v, int id, int l, int r){
        if (l >= v || r <= u){
            return (1 << 30) - 1;
        }
        if (r <= v && l >= u){
            return nodes[id];
        }
        
        int mid = (l + r) >> 1;
        
        return get(u, v, 2 * id + 1, l, mid) & get(u, v, 2 * id + 2, mid, r);
    }

    long long get(int u, int v){
        return get(u, v, 0, 0, size);
    }
};  

struct Query{
    int l, r, v;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<Query> query;
    for (int i = 0; i < m; i++){
        int l, r, v;
        cin >> l >> r >> v;
        l--;

        for (int mask = v, i = 0; mask != 0; mask >>= 1, i++){
            if (mask & 1){
                ps[l][i] += 1;
                ps[r][i] -= 1;
            }
        }

        query.push_back({l, r, v});
    }

    for (int i = 1; i < n; i++){
        for (int j = 0; j < 30; j++){
            ps[i][j] += ps[i - 1][j];
        }
    }

    vector<int> res(n, 0);
    for (int i = 0; i < n; i++){
        int mask = 0;
        for (int bit = 0; bit < 30; bit++){
            if (ps[i][bit] > 0){
                mask += (1 << bit);
            }
        }

        res[i] = mask;
    }

    SegTree st(n);
    st.build(res);

    for (int i = 0; i < m; i++){
        if (st.get(query[i].l, query[i].r) != query[i].v){
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";
    for (int i = 0; i < n; i++){
        cout << res[i] << " ";
    }

    return 0;
}
