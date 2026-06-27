// https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/problem/A

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 4 * N; 

int a[N];


struct SegTree{
    struct Item{
        long long odd = 0;
        long long even = 0;
    
        void set(long long val, int r){
            if (r){
                odd = val;
            }else{
                even = val;
            }
        }
    
        Item operator+(const Item &rhs) const{
            Item res;
    
            res.odd = this->odd + rhs.odd;
            res.even = this->even + rhs.even;
    
            return res;
        }
    };

    int size;
    vector<Item> nodes;

    SegTree(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        nodes.assign(2 * size, Item());
        nodes.assign(2 * size, Item());
    }

    void build(int id, int l, int r){
        if (r - l == 1){
            nodes[id].set(a[l], l % 2);
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
            nodes[id].set(value, l % 2);
            return;
        }

        int mid = (l + r) >> 1;

        set(pos, value, 2 * id + 1, l, mid);
        set(pos, value, 2 * id + 2, mid, r);

        nodes[id] = nodes[2 * id + 1] + nodes[2 * id + 2];
    }

    void set(int pos, int value){
        set(pos - 1, value, 0, 0, size);
    }
    
    // (l, r)
    Item get(int u, int v, int id, int l, int r){
        if (l >= v || r <= u){
            return Item();
        }
        if (r <= v && l >= u){
            return nodes[id];
        }
        
        int mid = (l + r) >> 1;
        
        return get(u, v, 2 * id + 1, l, mid) + get(u, v, 2 * id + 2, mid, r);
    }

    Item get(int u, int v){
        return get(u - 1, v, 0, 0, size);
    }
};  

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    SegTree st(n);

    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    st.build();

    int m;
    cin >> m;

    while(m--){
        int type;
        cin >> type;

        if (type){
            int l, r;
            cin >> l >> r;
            SegTree::Item ans = st.get(l, r);
            int res = 0;

            res = ((l - 1) & 1 ? ans.odd - ans.even : ans.even - ans.odd);
            
            cout << res << '\n';
        }else{
            int i, j;
            cin >> i >> j;

            st.set(i, j);
        }
    }

    return 0;
}