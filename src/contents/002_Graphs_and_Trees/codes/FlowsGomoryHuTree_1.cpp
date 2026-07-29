/* Hash: C4BF8E4C */
struct GomoryHu {
    struct Edge { int u, v; long long w; };
    int n;
    vector<Edge> tree;

    GomoryHu(int _n) : n(_n) {}

    // Requires a Dinic or PushRelabel solver instance "D" initialized with N nodes
    // and the original graph edges added with their respective capacities.
    void build(const vector<pair<pair<int, int>, long long>>& edges) {
        vector<int> p(n, 0);
        for (int i = 1; i < n; ++i) {
            Dinic D(n, i, p[i]); // Replace with your standard Dinic(N, S, T)
            for (auto& e : edges) {
                D.add_edge(e.first.first, e.first.second, e.second);
                D.add_edge(e.first.second, e.first.first, e.second); // Undirected
            }
            long long flow = D.max_flow();
            tree.push_back({i, p[i], flow});
            for (int j = i + 1; j < n; ++j) {
                if (p[j] == p[i] && D.level[j] != -1) { // j is on i's side of the min-cut
                    p[j] = i;
                }
            }
        }
    }
};
