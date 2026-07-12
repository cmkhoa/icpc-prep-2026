// https://codeforces.com/problemset/problem/920/F

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5, AI = 1e6;
const int M = 4 * N; 

int a[N];
int Div[AI + 5];

struct Node{
    long long sum, max;
};

struct SegTree{
    int size;
    vector<Node> nodes;

    SegTree(int n){
        // size = 1;
        // while(size < n){
        //     size *= 2;
        // }

        // nodes.assign(2 * size, 0);
        size = n;
        nodes.assign(4 * size, {});
    }

    void build(int id, int l, int r){
        if (r - l == 1){
            nodes[id] = {a[l], a[l]};
            return;
        }

        int mid = (l + r) >> 1;
        build(2 * id + 1, l, mid);
        build(2 * id + 2, mid, r);

        nodes[id].sum = nodes[2 * id + 1].sum + nodes[2 * id + 2].sum;
        nodes[id].max = max(nodes[2 * id + 1].max, nodes[2 * id + 2].max);
    }

    void build(){
        build(0, 0, size);
    }

    // [l, r)
    void set(int pos, int value, int id, int l, int r){
        if (pos < l || pos >= r) return;
        if (r - l == 1){
            nodes[id] = {value, value};
            return;
        }

        int mid = (l + r) >> 1;

        set(pos, value, 2 * id + 1, l, mid);
        set(pos, value, 2 * id + 2, mid, r);

        nodes[id].sum = nodes[2 * id + 1].sum + nodes[2 * id + 2].sum;
        nodes[id].max = max(nodes[2 * id + 1].max, nodes[2 * id + 2].max);
    }

    void set(int pos, int value){
        set(pos, value, 0, 0, size);
    }

    Node combine(Node a, Node b){
        return {a.sum + b.sum, max(a.max, b.max)};
    }
    
    // (l, r)
    Node get(int u, int v, int id, int l, int r){
        if (l >= v || r <= u){
            return {};
        }
        if (r <= v && l >= u){
            return nodes[id];
        }
        
        int mid = (l + r) >> 1;
        
        return combine(get(u, v, 2 * id + 1, l, mid), get(u, v, 2 * id + 2, mid, r));
    }

    Node get(int u, int v){
        return get(u, v, 0, 0, size);
    }

    void upd(int u, int v, int id, int l, int r){
        if (l >= v || r <= u){
            return;
        }
        if (nodes[id].max <= 2){
            return;
        }

        if (r - l == 1){
            nodes[id] = {Div[nodes[id].sum], Div[nodes[id].max]};
            return;
        }

        int mid = (l + r) >> 1;

        upd(u, v, 2 * id + 1, l, mid);
        upd(u, v, 2 * id + 2, mid, r);

        nodes[id].sum = nodes[2 * id + 1].sum + nodes[2 * id + 2].sum;
        nodes[id].max = max(nodes[2 * id + 1].max, nodes[2 * id + 2].max);
    }

    void upd(int u, int v){
        upd(u, v, 0, 0, size);
    }
};  

void divSieve(){
    for (int i = 1; i <= sqrtl(AI); i++){
        Div[i * i]--;
        for (int j = i * i; j < AI; j += i){
            Div[j] += 2;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    divSieve();

    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    SegTree st(n);
    st.build();

    for (int i = 0; i < m; i++){
        int type, l, r;
        cin >> type >> l >> r;
        l--;

        if (type == 1){
            st.upd(l, r);
        }else{
            cout << st.get(l, r).sum << '\n';
        }
    
    }

    return 0;
}