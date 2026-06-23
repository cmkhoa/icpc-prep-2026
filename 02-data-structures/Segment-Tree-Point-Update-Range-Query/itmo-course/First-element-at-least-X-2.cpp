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
        
        // size = n;
        nodes.assign(2 * size, -1);
        // size = n;
    }

    void build(int id, int l, int r){
        if (r - l == 1){
            if (l < N) nodes[id] = a[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(2 * id + 1, l, mid);
        build(2 * id + 2, mid, r);

        nodes[id] = max(nodes[2 * id + 1], nodes[2 * id + 2]);
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

        nodes[id] = max(nodes[2 * id + 1], nodes[2 * id + 2]);
    }

    void set(int pos, int value){
        set(pos, value, 0, 0, size);
    }
    
    // (l, r)
    long long get(int u, int v, int id, int l, int r){
        if (l >= v || r <= u){
            return -1;
        }
        if (r <= v && l >= u){
            return nodes[id];
        }
        
        int mid = (l + r) >> 1;
        
        return max(get(u, v, 2 * id + 1, l, mid), get(u, v, 2 * id + 2, mid, r));
    }

    long long get(int u, int v){
        return get(u, v, 0, 0, size);
    }

    int findAtLeast(int x, int id, int l, int r){
        if (get(l, r) < x){
            return -1;
        }
        
        if (r - l == 1){
            return l;
        }
        
        int mid = (l + r) >> 1;

        int ans = findAtLeast(x, 2 * id + 1, l, mid);

        if (ans == -1){
            ans = findAtLeast(x, 2 * id + 2, mid, r);
        }

        return ans;
    }

    int findAtLeast(int x, int l){
        return findAtLeast(x, 0, l, size);
    }
};  

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    SegTree st(n);

    // fill(a, a + N, -1);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    st.build();

    while(m--){
        int type;
        cin >> type;

        if (type == 1){
            int pos, v;
            cin >> pos >> v;

            st.set(pos, v);
        }else{
            int x, l;
            cin >> x >> l;

            cout << st.findAtLeast(x, l) << '\n';
        }
    }

    return 0;
}