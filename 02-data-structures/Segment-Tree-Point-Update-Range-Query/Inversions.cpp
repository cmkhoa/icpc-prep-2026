#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 4 * N; 

int a[N];

struct SegTree{
    int size;
    vector<int> nodes;

    SegTree(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }
        
        // size = n;
        nodes.assign(2 * size, 0);
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

        nodes[id] = nodes[2 * id + 1] + nodes[2 * id + 2];
    }

    void build(){
        build(0, 0, size);
    }

    // [l, r)
    void set(int pos, int value, int id, int l, int r){
        if (pos < l || pos >= r) return;
        if (r - l == 1){
            // cout << "set: " << id << " " << pos << " " << value << '\n';
            nodes[id] = value;
            return;
        }

        int mid = (l + r) >> 1;

        set(pos, value, 2 * id + 1, l, mid);
        set(pos, value, 2 * id + 2, mid, r);

        nodes[id] = nodes[2 * id + 1] + nodes[2 * id + 2];
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
            // cout << id << ": " << u << " " << v << ", " << nodes[id] << '\n';
            return nodes[id];
        }
        
        int mid = (l + r) >> 1;
        
        return get(u, v, 2 * id + 1, l, mid) + get(u, v, 2 * id + 2, mid, r);
    }

    long long get(int u, int v){
        if (v - u < 1) return 0;
        else return get(u, v, 0, 0, size);
    }
};  

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    SegTree st(n + 1);

    // fill(a, a + N, -1);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++){
        ans[i] = st.get(a[i] + 1, n + 1);
        st.set(a[i], 1);
    }

    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";

    return 0;
}