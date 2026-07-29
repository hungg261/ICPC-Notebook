/* Hash: A7C379B3 */
pair<int, long long> solve_elevator(int n, long long max_weight, const vector<long long>& w) {
    vector<pair<int, long long>> dp(1 << n);
    dp[0] = {1, 0};

    for (int mask = 1; mask < (1 << n); ++mask) {
        dp[mask] = {n + 1, 0};
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                auto prev = dp[mask ^ (1 << i)];
                if (prev.second + w[i] <= max_weight) {
                    prev.second += w[i];
                } else {
                    prev.first++;
                    prev.second = w[i];
                }
                dp[mask] = min(dp[mask], prev);
            }
        }
    }
    return dp[(1 << n) - 1];
}
