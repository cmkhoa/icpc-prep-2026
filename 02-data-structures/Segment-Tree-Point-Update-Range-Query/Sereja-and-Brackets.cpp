// https://codeforces.com/contest/380/problem/C

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
            nodes[id] = a[l];
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

struct Query{
    int l, r, idx;
};

int main(){
    // ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    int m;
    cin >> m;

    vector<Query> query;
    for (int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        l--;

        query.push_back({l, r, i});
    }

    sort(query.begin(), query.end(), [](const Query &a, const Query &b){
        return a.r < b.r;
    });

    SegTree st(s.size());

    vector<int> res(m);

    stack<int> p;
    int i = 0;
    for (int j = 0; j < m; j++){
        while(i < s.size() && i < query[j].r){
            // cout << j << ", " << query[j].r << ": " << i << '\n';
            // cout << i << " :\n";
            if (s[i] == ')'){
                if (!p.empty()){
                    // cout << p.top() << " " << i << '\n';
                    st.set(p.top(), 1);
                    p.pop();
                }
            }else{
                p.push(i);
            }
            
            i++;
        }   

        res[query[j].idx] = 2 * st.get(query[j].l, query[j].r);
    }

    for (int i = 0; i < m; i++){
        cout << res[i] << "\n";
    }

    return 0;
}