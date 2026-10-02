/* Hash: 492ADDB4 */
long long cost(int i, int j) { return 0; }

void solve_dp() {
    dp.assign(n + 1, vector<long long>(n + 1, 0)); opt.assign(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) opt[i][i] = i;

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1; dp[i][j] = 1e18;
            for (int k = opt[i][j - 1]; k <= min(j - 1, opt[i + 1][j]); k++) {
                long long cur = dp[i][k] + dp[k + 1][j] + cost(i, j);
                if (cur < dp[i][j]) { dp[i][j] = cur; opt[i][j] = k; }
            }
        }
    }
}