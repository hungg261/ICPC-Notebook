/* Hash: 2F718C99 */
struct Fraction {
    long long p, q;
    bool operator==(const Fraction& o) const { return p * o.q == q * o.p; }
    bool operator<(const Fraction& o) const { return p * o.q < q * o.p; }
};

struct SternBrocot {
    Fraction mediant(Fraction l, Fraction r) {
        return {l.p + r.p, l.q + r.q};
    }

    string find_path(Fraction target, int max_depth = 60) {
        Fraction L = {0, 1}, R = {1, 0};
        string path = "";
        for (int i = 0; i < max_depth; ++i) {
            Fraction M = mediant(L, R);
            if (target == M) break;
            if (target < M) {
                path += 'L';
                R = M;
            } else {
                path += 'R';
                L = M;
            }
        }
        return path;
    }
};
