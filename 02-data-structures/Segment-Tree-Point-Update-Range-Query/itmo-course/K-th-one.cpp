// https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/B

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
            nodes[id] = (l < N ? a[l] : 0);
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
            a[l] = value;
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

    int find(int k, int id, int l, int r){
        // cout << l << " " << r << '\n';
        if (r - l == 1){
            return l;
        }
        
        int mid = (l + r) >> 1;
        if (k > nodes[2 * id + 1]){
            return find(k - nodes[2 * id + 1], 2 * id + 2, mid, r);
        }else{
            return find(k, 2 * id + 1, l, mid);
        }
    }

    int find(int k){
        return find(k + 1, 0, 0, size);
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
        int type;
        cin >> type;

        if (type == 1){
            int pos;
            cin >> pos; 
            st.set(pos, 1 - a[pos]);
        }else{
            int k;
            cin >> k;
            cout << st.find(k) << '\n';
        }
    }

    return 0;
}