/* Hash: 22A3BA61 */
long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) { x = 1; y = 0; return a; }
    long long x1, y1, d = extgcd(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b); return d;
}