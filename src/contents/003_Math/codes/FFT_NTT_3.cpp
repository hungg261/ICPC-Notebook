/* Hash: 8CBF2CBC */
// Multiply (1 + 2x) * (2 + 3x) -> 2 + 7x + 6x^2
vector<int> a = {1, 2};
vector<int> b = {2, 3};
vector<long long> c = multiply_fft(a, b);
// c contains: {2, 7, 6, 0, ...}
