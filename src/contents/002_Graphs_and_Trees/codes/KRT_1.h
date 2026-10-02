/* Hash: DE683657 */
struct KRT {
    int n, node_cnt;
    vector<int> parent, sz, node_weight;
    vector<vector<int>> adj;

    KRT(int n) : n(n), node_cnt(n), parent(2 * n + 1), sz(2 * n + 1, 1), node_weight(2 * n + 1, 0), adj(2 * n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find_set(int v) {
        return v == parent[v] ? v : parent[v] = find_set(parent[v]);
    }

    void build(vector<tuple<int, int, int>>& edges) {
        sort(edges.begin(), edges.end());
        for (auto [w, u, v] : edges) {
            int root_u = find_set(u), root_v = find_set(v);
            if (root_u != root_v) {
                node_cnt++;
                node_weight[node_cnt] = w;
                parent[root_u] = node_cnt; parent[root_v] = node_cnt;
                adj[node_cnt].push_back(root_u); adj[node_cnt].push_back(root_v);
            }
        }
    }
};