// https://cses.fi/problemset/task/1748

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5, MOD = 1e9 + 7;
const int M = 4 * N; 

int a[N];
long long dp[N];
vector<int> sortedList;

int compress(int v){
    return lower_bound(sortedList.begin(), sortedList.end(), v) - sortedList.begin();
}

struct SegTree{
    int size;
    vector<long long> nodes;

    SegTree(int n){
        // size = 1;
        // while(size < n){
        //     size *= 2;
        // }

        // nodes.assign(2 * size, 0);
        size = n;
        nodes.assign(4 * size, 0);
    }

    void build(int id, int l, int r){
        if (r - l == 1){
            nodes[id] = a[l] % MOD;
            return;
        }

        int mid = (l + r) >> 1;
        build(2 * id + 1, l, mid);
        build(2 * id + 2, mid, r);

        nodes[id] = (nodes[2 * id + 1] + nodes[2 * id + 2]) % MOD;
    }

    void build(){
        build(0, 0, size);
    }

    // [l, r)
    void add(int pos, int value, int id, int l, int r){
        if (pos < l || pos >= r) return;
        if (r - l == 1){
            nodes[id] += value;
            return;
        }

        int mid = (l + r) >> 1;

        add(pos, value, 2 * id + 1, l, mid);
        add(pos, value, 2 * id + 2, mid, r);

        nodes[id] = (nodes[2 * id + 1] + nodes[2 * id + 2]) % MOD; // change this depending on problems
    }

    void add(int origValue, int value){
        int pos = compress(origValue);
        add(pos, value, 0, 0, size);
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
        
        return (get(u, v, 2 * id + 1, l, mid) + get(u, v, 2 * id + 2, mid, r)) % MOD;
    }

    long long get(int u, int v){
        u = compress(u);
        v = compress(v);
        return get(u, v, 0, 0, size);
    }
};  

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++){
        cin >> a[i];
        sortedList.push_back(a[i]);
    }

    sort(sortedList.begin(), sortedList.end());

    SegTree st(n);

    for (int i = 0; i < n; i++){
        dp[i] = 1 + st.get(0, a[i]);
        st.add(a[i], dp[i]);
    }   

    cout << st.get(0, 1e9);

    return 0;
}