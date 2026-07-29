/* Hash: 4C6E8D88 */
#ifdef _WIN32
#define GETCHAR _getchar_nolock
#else
#define GETCHAR getchar_unlocked
#endif

template <typename T = int>
inline bool readNum(T &x) {
    int ch = GETCHAR(); bool neg = false;
    while (ch != EOF && (ch < '0' || ch > '9') && ch != '-') ch = GETCHAR();
    if (ch == EOF) return false;
    if (ch == '-') { neg = true; ch = GETCHAR(); }
    x = 0;
    while (ch >= '0' && ch <= '9') { x = x * 10 + (ch - '0'); ch = GETCHAR(); }
    if (neg) x = -x;
    return true;
}
