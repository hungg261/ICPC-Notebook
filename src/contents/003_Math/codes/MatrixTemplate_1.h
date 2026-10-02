/* Hash: DDB4A8A9 */
const int MOD = 1e9 + 7;

struct Matrix {
    int r, c; vector<vector<long long>> mat;
    
    Matrix(int r, int c, bool identity = false) : r(r), c(c), mat(r, vector<long long>(c, 0)) {
        if (identity) for (int i = 0; i < min(r, c); i++) mat[i][i] = 1;
    }
    
    Matrix operator+(const Matrix& o) const {
        Matrix res(r, c);
        for (int i = 0; i < r; i++) for (int j = 0; j < c; j++)
            res.mat[i][j] = (mat[i][j] + o.mat[i][j]) % MOD;
        return res;
    }

    Matrix operator-(const Matrix& o) const {
        Matrix res(r, c);
        for (int i = 0; i < r; i++) for (int j = 0; j < c; j++)
            res.mat[i][j] = (mat[i][j] - o.mat[i][j] + MOD) % MOD;
        return res;
    }

    Matrix operator*(const Matrix& o) const {
        Matrix res(r, o.c);
        for (int i = 0; i < r; i++) for (int k = 0; k < c; k++) for (int j = 0; j < o.c; j++)
            res.mat[i][j] = (res.mat[i][j] + mat[i][k] * o.mat[k][j]) % MOD;
        return res;
    }

    Matrix power(long long p) const {
        Matrix res(r, r, true), base = *this;
        while (p > 0) {
            if (p & 1) res = res * base;
            base = base * base; p >>= 1;
        }
        return res;
    }
};