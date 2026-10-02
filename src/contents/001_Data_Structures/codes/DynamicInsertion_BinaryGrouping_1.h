/* Hash: 4860BFA0 */
struct StaticACAM {
    vector<string> strings;
    void insert(const string& s) { strings.push_back(s); }
    int size() const { return strings.size(); }
    void build() {}
    long long query(const string& s) { return 0; }
};

struct DynamicACAM {
    vector<StaticACAM> acams;

    void insert(const string& s) {
        StaticACAM cur; cur.insert(s);
        acams.push_back(move(cur));
        while (acams.size() >= 2 && acams.back().size() == acams[acams.size() - 2].size()) {
            StaticACAM rhs = move(acams.back()); acams.pop_back();
            StaticACAM lhs = move(acams.back()); acams.pop_back();
            for (const auto& str : rhs.strings) lhs.insert(str);
            lhs.build();
            acams.push_back(move(lhs));
        }
    }

    long long query(const string& s) {
        long long ans = 0;
        for (auto& ac : acams) ans += ac.query(s);
        return ans;
    }
};