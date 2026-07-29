/* Hash: EE0E96A8 */
const int BLOCK = 2150;

struct Query {
    int l, r, t, id;
    bool operator<(const Query& o) const {
        int bl1 = l / BLOCK, bl2 = o.l / BLOCK;
        if (bl1 != bl2) return bl1 < bl2;
        int br1 = r / BLOCK, br2 = o.r / BLOCK;
        if (br1 != br2) return br1 < br2;
        return t < o.t;
    }
};

struct Update {
    int pos, old_val, new_val;
};

long long current_answer = 0;
vector<int> cnt;

void add(int idx, const vector<int>& a) {}
void remove(int idx, const vector<int>& a) {}

void apply_update(int t, int cur_l, int cur_r, vector<int>& a, const vector<Update>& updates) {
    int pos = updates[t].pos;
    if (pos >= cur_l && pos <= cur_r) {
        remove(pos, a);
        a[pos] = updates[t].new_val;
        add(pos, a);
    } else {
        a[pos] = updates[t].new_val;
    }
}

void rollback_update(int t, int cur_l, int cur_r, vector<int>& a, const vector<Update>& updates) {
    int pos = updates[t].pos;
    if (pos >= cur_l && pos <= cur_r) {
        remove(pos, a);
        a[pos] = updates[t].old_val;
        add(pos, a);
    } else {
        a[pos] = updates[t].old_val;
    }
}

vector<long long> solve_mo_update(vector<Query>& queries, vector<Update>& updates, vector<int>& a) {
    sort(queries.begin(), queries.end());
    cnt.assign(1000005, 0); current_answer = 0;
    vector<long long> answers(queries.size());
    
    int cur_l = 0, cur_r = -1, cur_t = 0;
    for (const auto& q : queries) {
        while (cur_t < q.t) apply_update(cur_t++, cur_l, cur_r, a, updates);
        while (cur_t > q.t) rollback_update(--cur_t, cur_l, cur_r, a, updates);
        while (cur_l > q.l) add(--cur_l, a);
        while (cur_r < q.r) add(++cur_r, a);
        while (cur_l < q.l) remove(cur_l++, a);
        while (cur_r > q.r) remove(cur_r--, a);
        answers[q.id] = current_answer;
    }
    return answers;
}
