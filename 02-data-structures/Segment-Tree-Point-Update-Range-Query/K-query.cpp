// https://www.spoj.com/problems/KQUERY/?__cf_chl_f_tk=QfK_wLwejv8iMLZqKKVF3J9oOUYPS3HWoUf6kTeXrU0-1782958448-1.0.1.1-dPxeurJI0awdgC.21ky0qc7GZw_jLgPaKBsBhIfnhEU

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 4 * N; 

pair<int, int> a[N];

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
            nodes[id] = a[l].first;
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
    void set(int pos, int value, int id, int l, int r){
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

    void set(int pos, int value){
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

    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++){
        cin >> a[i].first;
        a[i].second = i;
    }

    sort(a, a + n);

    int q;
    cin >> q;

    vector<array<int, 4>> query;
    for (int i = 0; i < q; i++){
        int l, r, k;
        cin >> l >> r >> k;
        l--;

        query.push_back({k, l, r, i});
    }

    sort(query.begin(), query.end());

    SegTree st(n);

    vector<int> res(q, 0);

    int p = 0; 
    for (int i = 0; i < q; i++){
        // cout << "i: " << a[i] << '\n';
        while (p < n && a[p].first <= query[i][0]){
            st.set(a[p].second, 1);
            // cout << i << ": " << p << ' ';
            p++;
        }

        // cout << query[i][1] << "," << query[i][2] << " : " << st.get(query[i][1], query[i][2]) << '\n';
        res[query[i][3]] = (query[i][2] - query[i][1]) - st.get(query[i][1], query[i][2]);
    }

    for (int i = 0; i < q; i++){
        cout << res[i] << '\n';
    }

    return 0;
}