// https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 4 * N; 

int a[M];

struct SegTree{
    int size;
    vector<long long> nodes;
    vector<vector<long long>> dp;

    void calcAt(int id);

    SegTree(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        nodes.assign(2 * size, 0);
        dp.assign(2 * size, vector<long long>(4, INT64_MIN));
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
        dp[id][0] = dp[id][1] = dp[id][2] = dp[id][3] = INT64_MIN;
        if (r - l == 1){
            nodes[id] = value;
            dp[id][0] = dp[id][1] = dp[id][2] = dp[id][3] = nodes[id];
            return;
        }

        int mid = (l + r) >> 1;

        set(pos, value, 2 * id + 1, l, mid);
        set(pos, value, 2 * id + 2, mid, r);

        nodes[id] = nodes[2 * id + 1] + nodes[2 * id + 2];
        calcAt(id); // change this depending on problems
    }

    void set(int pos, int value){
        set(pos, value, 0, 0, size);
    }
    
    // (l, r)
    // long long get(int u, int v, int id, int l, int r){
    //     if (l >= v || r <= u){
    //         return 0;
    //     }
    //     if (r <= v && l >= u){
    //         return nodes[id];
    //     }
        
    //     int mid = (l + r) >> 1;
        
    //     return get(u, v, 2 * id + 1, l, mid) + get(u, v, 2 * id + 2, mid, r);
    // }

    long long get(){
        return max({0LL, dp[0][0], dp[0][1], dp[0][2], dp[0][3]});
    }

    void calcMaxSum(int id, int l, int r){
        if (r - l == 1){
            dp[id][0] = dp[id][1] = dp[id][2] = dp[id][3] = nodes[id];
            return; 
        }
        
        int mid = (l + r) >> 1;
        calcMaxSum(2 * id + 1, l, mid);
        calcMaxSum(2 * id + 2, mid, r);

        calcAt(id);
    }

    void calcMaxSum(){
        calcMaxSum(0, 0, size);
    }
};  

void SegTree::calcAt(int id){
    dp[id][0] = nodes[id];

    dp[id][1] = max(dp[2 * id + 1][1], 
                    dp[2 * id + 1][0] + dp[2 * id + 2][1]);

    dp[id][2] = max(dp[2 * id + 2][2], 
                    dp[2 * id + 2][0] + dp[2 * id + 1][2]);

    dp[id][3] = max({dp[2 * id + 1][3], dp[2 * id + 2][3],
                    dp[2 * id + 1][2] + dp[2 * id + 2][1]});
}


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
    st.calcMaxSum();

    cout << st.get() << '\n';

    while(m--){
        int x, y;
        cin >> x >> y;
        st.set(x, y);

        cout << st.get() << '\n';
    }

    // cout << '\n';
    // for (int i = 0; i < 2 * st.size; i++){
    //     cout << i << " : " << st.dp[i][0] << "," << st.dp[i][1] << "," << st.dp[i][2] << "," << st.dp[i][3] << '\n';
    // }

    return 0;
}