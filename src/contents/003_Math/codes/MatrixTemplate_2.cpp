/* Hash: 69D60AEF */
Matrix T(2, 2); T.mat = {{1, 1}, {1, 0}};
Matrix F(2, 1); F.mat = {{1}, {0}}; // F[1]=1, F[0]=0

Matrix Ans = T.power(n - 1) * F;
long long fn = Ans.mat[0][0];
