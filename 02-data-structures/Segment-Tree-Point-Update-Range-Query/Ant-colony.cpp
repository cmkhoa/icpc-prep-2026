// https://codeforces.com/contest/474/problem/F

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 4 * N; 

int a[N];

struct Node{
    int gcd, min, cnt;

    Node() : gcd(-1), min(-1), cnt(-1) {};
    Node(int a, int b, int c) : gcd(a), min(b), cnt(c) {};

    bool operator==(const Node &rhs) const{
        return gcd == rhs.gcd && min == rhs.min && cnt == rhs.cnt;
    }
};

struct SegTree{
    int size;
    vector<Node> nodes;

    SegTree(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        nodes.assign(2 * size, {});
    }

    void build(int id, int l, int r){
        if (r - l == 1){
            nodes[id] = Node{a[l], a[l], 1};
            return;
        }

        int mid = (l + r) >> 1;
        build(2 * id + 1, l, mid);
        build(2 * id + 2, mid, r);

        nodes[id].min = min(nodes[2 * id + 1].min, nodes[2 * id + 2].min);
        nodes[id].gcd = __gcd(nodes[2 * id + 1].gcd, nodes[2 * id + 2].gcd);
        nodes[id].cnt = nodes[2 * id + 1].cnt * (nodes[id].min == nodes[2 * id + 1].min)
                      + nodes[2 * id + 2].cnt * (nodes[id].min == nodes[2 * id + 2].min);
    }

    void build(){
        build(0, 0, size);
    }

    // [l, r)
    void set(int pos, int value, int id, int l, int r){
        if (pos < l || pos >= r) return;
        if (r - l == 1){
            nodes[id] = Node{value, value, 1};
            return;
        }

        int mid = (l + r) >> 1;

        set(pos, value, 2 * id + 1, l, mid);
        set(pos, value, 2 * id + 2, mid, r);

        nodes[id].min = min(nodes[2 * id + 1].min, nodes[2 * id + 2].min);
        nodes[id].gcd = __gcd(nodes[2 * id + 1].gcd, nodes[2 * id + 2].gcd);
        nodes[id].cnt = nodes[2 * id + 1].cnt * (nodes[id].min == nodes[2 * id + 1].min)
                      + nodes[2 * id + 2].cnt * (nodes[id].min == nodes[2 * id + 2].min);
    }

    void set(int pos, int value){
        set(pos, value, 0, 0, size);
    }

    Node combine(const Node &a, const Node &b){
        if (a == Node()) return b;
        if (b == Node()) return a;
        
        Node ans;
        ans.min = min(a.min, b.min);
        ans.gcd = __gcd(a.gcd, b.gcd);
        ans.cnt = a.cnt * (ans.min == a.min) + b.cnt * (ans.min == b.min);

        return ans;
    }
    
    // (l, r)
    Node get(int u, int v, int id, int l, int r){
        if (l >= v || r <= u){
            return Node();
        }
        if (r <= v && l >= u){
            return nodes[id];
        }
        
        int mid = (l + r) >> 1;
        
        return combine(get(u, v, 2 * id + 1, l, mid), get(u, v, 2 * id + 2, mid, r));
    }

    long long get(int u, int v){
        Node ans = get(u, v, 0, 0, size);

        if (ans.gcd == ans.min){
            return v - u - ans.cnt;
        }else{
            return v - u;
        }
    }
};  


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    
    SegTree st(n);
    st.build();

    int m;
    cin >> m;

    for (int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        l--;

        cout << st.get(l, r) << '\n';
    }
    return 0;
}