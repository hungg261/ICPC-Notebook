/* Hash: 78E8D3A6 */
struct SegTree {
    int n; vector<int> tree;
    SegTree(int n) : n(n), tree(2 * n, 0) {}

    void update(int i, int value) {
        for (tree[i += n] = value; i > 1; i >>= 1) {
            tree[i >> 1] = tree[i] + tree[i ^ 1];
        }
    }

    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += tree[l++];
            if (r & 1) res += tree[--r];
        }
        return res;
    }
};
