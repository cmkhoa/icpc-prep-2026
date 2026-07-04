// https://codeforces.com/problemset/problem/1234/D

#include <bits/stdc++.h>
using namespace std;

// const int N = 1e5 + 5;
// const int M = 4 * N; 

// int a[N];

struct SegTree{
    int size;
    vector<int> nodes;

    SegTree(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        nodes.assign(2 * size, 0);
        // size = n;
        // nodes.assign(4 * size, {});
    }

    // void merge(int id){
    //     int L = 2 * id + 1, R = 2 * id + 2;

    //     nodes[id] = nodes[L];
    //     nodes[id].insert(nodes[R].begin(), nodes[R].end());
    // }

    // unordered_set<int> merge(const auto &lhs, const auto &rhs){
    //     unordered_set<int> ans;

    //     ans.insert(lhs.begin(), lhs.end());
    //     ans.insert(rhs.begin(), rhs.end());
        
    //     return ans;
    // }

    void build(const string &s, int id, int l, int r){
        if (r - l == 1){
            if (l < s.size()){
                nodes[id] = (1 << s[l]);
            }
            return;
        }

        int mid = (l + r) >> 1;
        build(s, 2 * id + 1, l, mid);
        build(s, 2 * id + 2, mid, r);

        nodes[id] = nodes[2 * id + 1] | nodes[2 * id + 2];
    }

    void build(const string &s){
        build(s, 0, 0, size);
    }

    // [l, r)
    void set(int pos, char value, string &s, int id, int l, int r){
        if (pos < l || pos >= r) return;
        if (r - l == 1){
            nodes[id] = (1 << value);
            return;
        }

        int mid = (l + r) >> 1;

        set(pos, value, s, 2 * id + 1, l, mid);
        set(pos, value, s, 2 * id + 2, mid, r);

        nodes[id] = nodes[2 * id + 1] | nodes[2 * id + 2];
    }

    void set(int pos, char value, string &s){
        set(pos, value, s, 0, 0, size);
    }
    
    // (l, r)
    int get(int u, int v, int id, int l, int r){
        if (l >= v || r <= u){
            return 0;
        }
        if (r <= v && l >= u){
            return nodes[id];
        }
        
        int mid = (l + r) >> 1;
        
        return get(u, v, 2 * id + 1, l, mid) | get(u, v, 2 * id + 2, mid, r);
    }

    int get(int u, int v){
        return __builtin_popcount(get(u, v, 0, 0, size));
    }
};  

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    
    int n = s.size();
    for (int i = 0; i < n; i++)
        s[i] -= 'a';
    
    SegTree st(n);
    st.build(s);
    
    int q;
    cin >> q;

    for (int i = 0; i < q; i++){
        int type;
        cin >> type;
    
        if (type == 1){
            int pos; char c;
            cin >> pos >> c;
            pos--;

            c -= 'a';

            st.set(pos, c, s);
        }else{
            int l, r;
            cin >> l >> r;
            l--;

            cout << st.get(l, r) << '\n';
        }
    }

    return 0;
}