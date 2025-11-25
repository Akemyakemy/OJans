#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    vector<int> p(n);
    for (auto &i : p) {
        cin >> i;
        i--;
    }

    const int B = 317;
    const int NB = (n + B - 1) / B;

    vector<long long> a(n);
    vector<long long> lazy(NB);

    vector<vector<int>> cnt(NB, vector<int>(NB));
    for (int t = 0; t < NB; t++) {
        int L = t * B, R = min(n, L + B);
        for (int i = L; i < R; i++) {
            int bj = p[i] / B;
            ++cnt[t][bj];
        }
    }

    vector<vector<int>> pref(NB + 1, vector<int>(NB));
    for (int t = 0; t < NB; t++) {
        for (int b = 0; b < NB; b++) {
            pref[t + 1][b] = pref[t][b] + cnt[t][b];
        }
    }

    vector<vector<pair<int, int>>> occ(n);
    for (int t = 0; t < NB; t++) {
        int L = t * B, R = min(n, L + B);
        vector<int> vals;
        vals.reserve(R - L);
        for (int i = L; i < R; ++i) vals.push_back(p[i]);
        sort(vals.begin(), vals.end());
        for (int l = 0, r; l < vals.size(); l = r) {
            r = l;
            while (r < vals.size() && vals[r] == vals[l]) r++;
            occ[vals[l]].push_back({t, r - l});
        }
    }

    vector<long long> sum_idx(NB, 0);

    auto add_single = [&](int j, long long x) {
        a[j] += x;
        for (auto [t, c] : occ[j]) sum_idx[t] += x * c;
    };

    auto add_range = [&](int L, int R, long long x) {
        int bL = L / B, bR = R / B;
        if (bL == bR) {
            for (int j = L; j <= R; j++) add_single(j, x);
        } else {
            int endL = (bL + 1) * B - 1;
            for (int j = L; j <= endL; j++) add_single(j, x);
            for (int b = bL + 1; b <= bR - 1; b++) lazy[b] += x;
            int startR = bR * B;
            for (int j = startR; j <= R; j++) add_single(j, x);
        }
    };

    auto get_point = [&](int j) -> long long {
        return a[j] + lazy[j / B];
    };

    auto query_range = [&](int L, int R) -> long long {
        long long ans = 0;
        int bL = L / B, bR = R / B;
        if (bL == bR) {
            for (int i = L; i <= R; i++) ans += get_point(p[i]);
        } else {
            int endL = (bL + 1) * B - 1;
            for (int i = L; i <= endL; i++) ans += get_point(p[i]);
            int startR = bR * B;
            for (int i = startR; i <= R; i++) ans += get_point(p[i]);

            int tL = bL + 1, tR = bR - 1;
            if (tL <= tR) {
                for (int t = tL; t <= tR; t++) ans += sum_idx[t];
                for (int b = 0; b < NB; b++) {
                    int k = pref[tR + 1][b] - pref[tL][b];
                    if (k) ans += lazy[b] * 1ll * k;
                }
            }
        }
        return ans;
    };

    long long last = 0;
    for (int _ = 0; _ < q; ++_) {
        int op; cin >> op;
        if (op == 1) {
            long long l, r, x; 
            cin >> l >> r >> x;
            l ^= last; r ^= last; x ^= last;
            l--; r--;
            add_range(l, r, x);
        } else {
            long long l, r; 
            cin >> l >> r;
            l ^= last; r ^= last;
            l--; r--;
            last = query_range(l, r);
            cout << last << '\n';
        }
    }
    return 0;
}
