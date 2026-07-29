/* Hash: 459F49A8 */
long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) { x = 1; y = 0; return a; }
    long long x1, y1, d = extgcd(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b); return d;
}

pair<long long, long long> crt_two(long long r1, long long m1, long long r2, long long m2) {
    long long x, y, g = extgcd(m1, m2, x, y);
    if ((r2 - r1) % g != 0) return {-1, -1};
    long long lcm = m1 / g * m2, mod = m2 / g;
    long long x0 = ((x % mod) + mod) % mod;
    long long ans = (r1 + (__int128)((r2 - r1) / g) * x0 % lcm * m1) % lcm;
    return {ans < 0 ? ans + lcm : ans, lcm};
}

pair<long long, long long> crt(const vector<pair<long long, long long>>& eq) {
    if (eq.empty()) return {0, 1};
    long long r_ans = eq[0].first, m_ans = eq[0].second;
    for (size_t i = 1; i < eq.size(); i++) {
        auto [r, m] = crt_two(r_ans, m_ans, eq[i].first, eq[i].second);
        if (m == -1) return {-1, -1};
        r_ans = r; m_ans = m;
    }
    return {r_ans, m_ans};
}
