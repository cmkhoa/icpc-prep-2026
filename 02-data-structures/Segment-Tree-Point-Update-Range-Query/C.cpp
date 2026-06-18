#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 4 * N; 

int a[N];

struct SegTree{
    int size;
    vector<int> nodes, count;

    SegTree(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        nodes.assign(2 * size, 0);
        count.assign(2 * size, 1);
    }

    void build(int id, int l, int r){
        if (r - l == 1){
            nodes[id] = a[l];
            count[id] = 1;
            return;
        }

        int mid = (l + r) >> 1;
        build(2 * id + 1, l, mid);
        build(2 * id + 2, mid, r);
        
        if (nodes[2 * id + 1] == nodes[2 * id + 2]){
            count[id] = count[2 * id + 1] + count[2 * id + 2];
        }else{
            count[id] = (nodes[2 * id + 1] < nodes[2 * id + 2] ? count[2 * id + 1] : count[2 * id + 2]);
        }

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
            count[id] = 1;
            return;
        }

        int mid = (l + r) >> 1;

        set(pos, value, 2 * id + 1, l, mid);
        set(pos, value, 2 * id + 2, mid, r);

        if (nodes[2 * id + 1] == nodes[2 * id + 2]){
            count[id] = count[2 * id + 1] + count[2 * id + 2];
        }else{
            count[id] = (nodes[2 * id + 1] < nodes[2 * id + 2] ? count[2 * id + 1] : count[2 * id + 2]);
        }

        nodes[id] = min(nodes[2 * id + 1], nodes[2 * id + 2]); // change this depending on problems
    }

    void set(int pos, int value){
        set(pos, value, 0, 0, size);
    }
    
    // (l, r)
    pair<int, int> get(int u, int v, int id, int l, int r){
        if (l >= v || r <= u){
            return {INT_MAX, 0};
        }
        if (r <= v && l >= u){
            return make_pair(nodes[id], count[id]);
        }
        
        int mid = (l + r) >> 1;
        pair<int, int> L = get(u, v, 2 * id + 1, l, mid);
        pair<int, int> R = get(u, v, 2 * id + 2, mid, r);

        int mini = min(L.first, R.first);
        int count = 1;

        if (L.first == R.first){
            count = L.second + R.second;
        }else{
            count = (L.first < R.first ? L.second : R.second);
        }
        
        return make_pair(mini, count);
    }

    pair<int, int> get(int u, int v){
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
            auto res = st.get(x, y);
            cout << res.first << " " << res.second << '\n';
        }
    }

    return 0;
}