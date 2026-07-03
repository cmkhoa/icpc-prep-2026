// https://atcoder.jp/contests/abc343/tasks/abc343_f

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int a[N];

struct Data{
    int fmax;
    int smax;
    int fcnt, scnt;

    Data(): fmax(0), smax(0), fcnt(0), scnt(0) {};
    Data(int val): fmax(val), smax(0), fcnt(1), scnt(0) {};
    Data(int fmax, int smax, int fcnt, int scnt): fmax(fmax), smax(smax), fcnt(fcnt), scnt(scnt) {}

    Data operator+(const Data &rhs) const {
        // Data res = *this;

        return {fmax, smax, 
            fcnt + rhs.fcnt * (fmax == rhs.fmax) + rhs.scnt * (smax == rhs.fmax),
            scnt + rhs.fcnt * (fmax == rhs.fmax) + rhs.scnt * (smax == rhs.smax)};
    }

    bool operator==(const Data &rhs) const{
        return (fmax == rhs.fmax) && (smax == rhs.smax);
    }

    bool operator<(const Data &rhs) const{
        if (fmax == rhs.fmax){
            return smax < rhs.smax;
        }

        return fmax < rhs.fmax;
    }

    bool operator>(const Data &rhs) const{
        return !(*this < rhs);
    }
};

struct SegTree{
    vector<Data> nodes;
    int len = 0;
    int size = 0;
    
    SegTree(int n){
        size = 1;
        len = n;
        while(size < n) size *= 2;

        nodes.assign(2 * size, Data());        
        // size = n;
        // nodes.assign(4 * n, Data());
    }
    
    Data combine(Data lhs, Data rhs){
        if (lhs < rhs) swap(lhs, rhs);
    
        Data res;
        res.fmax = lhs.fmax;
        res.smax = lhs.smax;
    
        if (res.fmax != rhs.fmax && res.smax < rhs.fmax){
            res.smax = rhs.fmax;
        }else if (res.smax < rhs.smax){
                res.smax = rhs.smax;
                // res.scnt = lhs.scnt;
        }
    
        if (res.fmax == lhs.fmax) res.fcnt += lhs.fcnt;
        if (res.fmax == lhs.smax) res.fcnt += lhs.scnt;
        if (res.fmax == rhs.fmax) res.fcnt += rhs.fcnt;
        if (res.fmax == rhs.smax) res.fcnt += rhs.scnt;

        if (res.smax == lhs.fmax) res.scnt += lhs.fcnt;
        if (res.smax == lhs.smax) res.scnt += lhs.scnt;
        if (res.smax == rhs.fmax) res.scnt += rhs.fcnt;
        if (res.smax == rhs.smax) res.scnt += rhs.scnt;

        return res;
    }

    void build(int id, int l, int r){
        if (r - l == 1){
            if (l < len) nodes[id] = Data(a[l]);
            return;
        }

        int mid = (l + r) >> 1;
        build(2 * id + 1, l, mid);
        build(2 * id + 2, mid, r);

        nodes[id] = combine(nodes[2 * id + 1], nodes[2 * id + 2]);
    }   

    void build(){
        build(0, 0, size);
    }

    void set(int pos, int val, int id, int l, int r){
        if (pos < l || pos >= r){
            return;
        }

        if (r - l == 1){
            nodes[id] = Data(val);
            return;
        }

        int mid = (l + r) >> 1;
        set(pos, val, 2 * id + 1, l, mid);
        set(pos, val, 2 * id + 2, mid, r);

        nodes[id] = combine(nodes[2 * id + 1], nodes[2 * id + 2]);
    }

    void set(int pos, int val){
        return set(pos, val, 0, 0, size);
    }


    Data get(int u, int v, int id, int l, int r){
        if (r <= u || l >= v){
            return Data();
        }
        
        if (r <= v && l >= u){
            // cout << id << ": " << l << " " << r << '\n';
            return nodes[id];
        }

        int mid = (l + r) >> 1;

        Data L = get(u, v, 2 * id + 1, l, mid);
        Data R = get(u, v, 2 * id + 2, mid, r);

        return combine(L, R);
    }    
    Data get(int u, int v){
        return get(u, v, 0, 0, size);
    }    
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    SegTree st(n);
    st.build();
    
    // for (int i = 0; i <= 14; i++){
    //     cout << i << ": " << st.nodes[i].fmax << " " << st.nodes[i].smax << " " << st.nodes[i].fcnt << " " << st.nodes[i].scnt << '\n';
    // }

    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int p, x;
            cin >> p >> x;
            p--;

            st.set(p, x);
        }else{
            int l, r;
            cin >> l >> r;
            l--;

            cout << st.get(l, r).scnt << '\n';
        }
    }

    return 0;
}