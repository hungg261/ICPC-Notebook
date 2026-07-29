/* Hash: A9711F63 */
const long long INF = 1e18;

struct Hungarian {
    int n;
    vector<vector<long long>> cost;
    vector<long long> u, v, dist;
    vector<int> p, way, match;
    vector<bool> used;

    Hungarian(int _n) : n(_n), cost(_n + 1, vector<long long>(_n + 1, 0)), u(_n + 1, 0), v(_n + 1, 0), p(_n + 1, 0), way(_n + 1, 0), match(_n + 1, 0), dist(_n + 1, 0), used(_n + 1, false) {}

    long long solve() {
        for (int i = 1; i <= n; ++i) {
            p[0] = i;
            int j_cur = 0;
            fill(dist.begin(), dist.end(), INF);
            fill(used.begin(), used.end(), false);
            do {
                used[j_cur] = true;
                int i_cur = p[j_cur], j_next = 0;
                long long delta = INF;
                for (int j = 1; j <= n; ++j) {
                    if (!used[j]) {
                        long long cur = cost[i_cur][j] - u[i_cur] - v[j];
                        if (cur < dist[j]) { dist[j] = cur; way[j] = j_cur; }
                        if (dist[j] < delta) { delta = dist[j]; j_next = j; }
                    }
                }
                for (int j = 0; j <= n; ++j) {
                    if (used[j]) { u[p[j]] += delta; v[j] -= delta; }
                    else dist[j] -= delta;
                }
                j_cur = j_next;
            } while (p[j_cur] != 0);
            do {
                int j_prev = way[j_cur];
                p[j_cur] = p[j_prev];
                j_cur = j_prev;
            } while (j_cur != 0);
        }
        for (int j = 1; j <= n; ++j) match[p[j]] = j;
        return -v[0];
    }
};
