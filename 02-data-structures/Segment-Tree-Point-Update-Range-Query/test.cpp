#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int a[N];

struct SegTree{
    vector<long long> sums;
    int size;

    SegTree(int n){
        size = 1;
        while(size < n) size *= 2;

        sums.assign(2 * size, 0);
    }
    
    void f(int id){
        sums[id] = sums[2 * id + 1] + sums[2 * id + 2];
    }

    void build(int id, int l, int r){
        if (r - l == 1){
            if (l < N) sums[id] = a[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(2 * id + 1, l, mid);
        build(2 * id + 2, mid, r);

        f(id);
    }

    void build(){
        build(0, 0, size);
    }

    void set(int pos, int v, int id, int l, int r){
        if (pos < l || pos >= r){
            return;
        }
        
        if (r - l == 1){
            sums[id] = v;
            return;
        }

        int mid = (l + r) >> 1;
        set(pos, v, 2 * id + 1, l, mid);
        set(pos, v, 2 * id + 2, mid, r);

        f(id);
    }
    
    void set(int pos, int v){
        set(pos, v, 0, 0, size);
    }

    long long get(int u, int v, int id, int l, int r){
        if (v <= l || u >= r){
            return 0;
        }

        if (l >= u && r <= v){
            return sums[id];
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
            cout << st.get(x, y) << '\n';
        }
    }

    return 0;
}