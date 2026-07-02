// https://cses.fi/problemset/task/1144

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int M = 4 * N; 

int a[N];
vector<array<int, 3>> query;
vector<int> allVals;

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

    void add(int pos, int value, int id, int l, int r){
        if (pos < l || pos >= r) return;
        if (r - l == 1){
            nodes[id] += value;
            return;
        }

        int mid = (l + r) >> 1;

        add(pos, value, 2 * id + 1, l, mid);
        add(pos, value, 2 * id + 2, mid, r);

        nodes[id] = nodes[2 * id + 1] + nodes[2 * id + 2]; // change this depending on problems
    }

    void add(int findValue, int value){
        int pos = lower_bound(allVals.begin(), allVals.end(), findValue) - allVals.begin();
        // cout << pos << '\n';
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
        
        return get(u, v, 2 * id + 1, l, mid) + get(u, v, 2 * id + 2, mid, r);
    }

    long long get(int leftVal, int rightVal){
        int u = lower_bound(allVals.begin(), allVals.end(), leftVal) - allVals.begin();
        int v = upper_bound(allVals.begin(), allVals.end(), rightVal) - allVals.begin();

        return get(u, v, 0, 0, size);
    }
};  

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++){
        cin >> a[i];
        allVals.push_back(a[i]);
    }
    
    
    for (int i = 0; i < m; i++){
        char temp; int a, b;
        cin >> temp >> a >> b;
        
        if (temp == '!'){
            allVals.push_back(b);
            a--;
        }
        
        query.push_back({temp == '?', a, b});
    }
    
    SegTree st(allVals.size());
    
    sort(allVals.begin(), allVals.end());
    allVals.erase(unique(allVals.begin(), allVals.end()), allVals.end());
    
    for (int i = 0; i < n; i++){
        st.add(a[i], 1);
    }

    for (int i = 0; i < m; i++){

        if (query[i][0] == 0){
            st.add(a[query[i][1]], -1);
            a[query[i][1]] = query[i][2];
            st.add(query[i][2], 1);
        }else{
            cout << st.get(query[i][1], query[i][2]) << '\n';
        }
    }

    return 0;
}