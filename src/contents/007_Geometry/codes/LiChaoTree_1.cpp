/* Hash: 73B73917 */
struct Line {
    long long k, m;
    long long operator()(long long x) { return k * x + m; }
};

struct LiChaoTree {
    int n; vector<Line> tree;
    LiChaoTree(int n) : n(n), tree(4 * n, {0, -INF}) {}

    void insert(int node, int l, int r, Line newline) {
        int mid = (l + r) >> 1;
        bool bit_l = newline(l) > tree[node](l), bit_m = newline(mid) > tree[node](mid);
        if (bit_m) swap(tree[node], newline);
        if (l == r) return;
        if (bit_l != bit_m) insert(node << 1, l, mid, newline);
        else insert(node << 1 | 1, mid + 1, r, newline);
    }

    long long query(int node, int l, int r, int x) {
        if (l == r) return tree[node](x);
        int mid = (l + r) >> 1; long long res = tree[node](x);
        if (x <= mid) res = max(res, query(node << 1, l, mid, x));
        else res = max(res, query(node << 1 | 1, mid + 1, r, x));
        return res;
    }
};