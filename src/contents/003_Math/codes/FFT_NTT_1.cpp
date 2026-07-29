/* Hash: 4F119655 */
const double PI = acos(-1);
struct Complex {
    double r, i;
    Complex(double r = 0, double i = 0) : r(r), i(i) {}
    Complex operator+(const Complex& o) const { return {r + o.r, i + o.i}; }
    Complex operator-(const Complex& o) const { return {r - o.r, i - o.i}; }
    Complex operator*(const Complex& o) const { return {r * o.r - i * o.i, r * o.i + i * o.r}; }
};

void fft(vector<Complex>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        Complex wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            Complex w(1);
            for (int j = 0; j < len / 2; j++) {
                Complex u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w = w * wlen;
            }
        }
    }
    if (invert) {
        for (auto& x : a) x.r /= n;
    }
}

vector<long long> multiply_fft(const vector<int>& a, const vector<int>& b) {
    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1; while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i];
    fft(fa, true);
    vector<long long> res(n);
    for (int i = 0; i < n; i++) res[i] = round(fa[i].r);
    return res;
}
