/* Hash: 4727B10A */
// checker.cpp
int32_t main() {
    ifstream f_user("user.out"), f_brute("brute.out");
    string s_user, s_brute;
    while (f_user >> s_user) {
        if (!(f_brute >> s_brute) || s_user != s_brute) return 1;
    }
    if (f_brute >> s_brute) return 1;
    return 0;
}