/* Hash: F37D049B */
struct Blossom {
    int n, timer;
    vector<vector<int>> g;
    vector<int> match, p, base, q;
    vector<bool> inq, inb, blo;

    Blossom(int n) : n(n), g(n + 1), match(n + 1, 0), p(n + 1), base(n + 1), q(n + 1) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int lca(int a, int b) {
        static vector<int> used(n + 1, 0);
        timer++;
        for (;; swap(a, b)) {
            if (a) {
                a = base[a];
                if (used[a] == timer) return a;
                used[a] = timer;
                a = p[match[a]];
            }
        }
    }

    void mark(int v, int b, int children) {
        for (; base[v] != b; v = p[match[v]]) {
            blo[base[v]] = blo[base[match[v]]] = true;
            p[v] = children;
            children = match[v];
        }
    }

    int bfs(int root) {
        fill(p.begin(), p.end(), 0);
        inq.assign(n + 1, false);
        for (int i = 1; i <= n; i++) base[i] = i;
        int ql = 0, qr = 0;
        q[qr++] = root;
        inq[root] = true;

        while (ql < qr) {
            int u = q[ql++];
            for (int v : g[u]) {
                if (base[u] == base[v] || match[u] == v) continue;
                if (v == root || (match[v] && p[match[v]])) {
                    int b = lca(u, v);
                    blo.assign(n + 1, false);
                    mark(u, b, v);
                    mark(v, b, u);
                    for (int i = 1; i <= n; i++) {
                        if (blo[base[i]]) {
                            base[i] = b;
                            if (!inq[i]) {
                                inq[i] = true;
                                q[qr++] = i;
                            }
                        }
                    }
                } else if (!p[v]) {
                    p[v] = u;
                    if (!match[v]) return v;
                    v = match[v];
                    inq[v] = true;
                    q[qr++] = v;
                }
            }
        }
        return 0;
    }

    int solve() {
        int max_match = 0;
        for (int i = 1; i <= n; i++) {
            if (!match[i]) {
                int v = bfs(i);
                while (v) {
                    int pv = p[v], nv = match[pv];
                    match[v] = pv;
                    match[pv] = v;
                    v = nv;
                }
            }
        }
        for (int i = 1; i <= n; i++) if (match[i]) max_match++;
        return max_match / 2;
    }
};