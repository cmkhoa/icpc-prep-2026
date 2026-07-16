// https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/description/

class Solution {
public:
    static const int MOD = 1e9 + 7;

    struct Node{
        long long prefix, suffix, both, none;

        Node(): prefix(0), suffix(0), both(0), none(0) {} 
        Node(long long a, long long b, long long c, long long d): prefix(a), suffix(b), both(c), none(d) {} 
    };

    struct SegTree{
        int size;
        vector<Node> nodes;

        SegTree(int n){
            // size = 1;
            // while(size < n){
            //     size *= 2;
            // }

            // nodes.assign(2 * size, {});
            size = n;
            nodes.assign(4 * size, {});
        }

        Node combine(Node l, Node r){
            long long prefix = 0, suffix = 0, both = 0, none = 0;
            prefix = max({
                          l.prefix + r.prefix,
                          l.prefix + r.none,
                          l.both + r.none
                        });

            suffix = max({
                          r.suffix + l.suffix,
                          r.suffix + l.none,
                          r.both + l.none
                        });

            both = max({
                        r.both + l.prefix, 
                        l.both + r.suffix,
                        l.prefix + r.suffix
                        });

            none = max({
                        l.suffix + r.none,
                        r.prefix + l.none,
                        l.none + r.none
                        });

            return {prefix, suffix, both, none};
        }

        void build(const vector<int> &nums, int id, int l, int r){
            if (r - l == 1){
                if (l < nums.size()) nodes[id] = {0, 0, nums[l], 0};
                else nodes[id] = {};

                return;
            }

            int mid = (l + r) >> 1;
            build(nums, 2 * id + 1, l, mid);
            build(nums, 2 * id + 2, mid, r);

            nodes[id] = combine(nodes[2 * id + 1], nodes[2 * id + 2]);
        }

        void build(const vector<int> &nums){
            build(nums, 0, 0, size);
        }

        // [l, r)
        void set(int pos, int value, int id, int l, int r){
            if (pos < l || pos >= r) return;
            if (r - l == 1){
                nodes[id] = {0, 0, value, 0};
                return;
            }

            int mid = (l + r) >> 1;

            set(pos, value, 2 * id + 1, l, mid);
            set(pos, value, 2 * id + 2, mid, r);

            nodes[id] = combine(nodes[2 * id + 1], nodes[2 * id + 2]); // change this depending on problems
        }

        void set(int pos, int value){
            set(pos, value, 0, 0, size);
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

        long long get(int u, int v){
            Node ans = get(u, v, 0, 0, size);

            return max({ans.prefix, ans.suffix, ans.both, ans.none});
        }
    };      

    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        SegTree st(nums.size());
        st.build(nums);

        long long res = 0;    
        for (vector<int> e : queries){
            st.set(e[0], e[1]);

            res += st.get(0, nums.size());
            res %= MOD;
        }

        return res;
    }
};
