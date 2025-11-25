// Problem: Colorful Tree
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/C
// Memory Limit: 1024 MB
// Time Limit: 8000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
 
using i128 = __int128_t;
using u128 = __uint128_t;
 
#ifdef EMOFUNC
#include <debug.h>
#else
#define LOG(...)
#endif
 
const int mod = 998244353;
 
int qpow(int a, int n) {
    int ans = 1;
    for ( ; n; n >>= 1, a = i64(a) * a % mod) {
        if (n & 1) {
            ans = i64(ans) * a % mod;
        }
    }
    return ans;
}
 
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
     
    int T;
    cin >> T;
 
    while (T--) {
        int n, q;
        cin >> n >> q;
 
        vector<int> p(n);
 
        vector e(n, vector<int>());
        for (int i = 1; i < n; i++) {
            cin >> p[i];
            p[i]--;
 
            e[p[i]].push_back(i);
        }
 
        struct Seg {
            int l, r, inv;
        };
 
        vector<Seg> seg(n);
        for (auto & [l, r, inv]: seg) {
            cin >> l;
        }
        for (auto & [l, r, inv]: seg) {
            cin >> r;
            inv = qpow(r - l + 1, mod - 2);
        }
 
        auto pr_same_color = [&](const Seg & s1, const Seg & s2) -> int {
            const auto & [l1, r1, inv1] = s1;
            const auto & [l2, r2, inv2] = s2;
 
            int l = max(l1, l2);
            int r = min(r1, r2);
 
            if (r < l) {
                return 0;
            }
 
            return i64(r - l + 1) * inv1 % mod * inv2 % mod;
        };
 
        auto pr_3_same_color = [&](const Seg & s1, const Seg & s2, const Seg & s3) -> int {
            const auto & [l1, r1, inv1] = s1;
            const auto & [l2, r2, inv2] = s2;
            const auto & [l3, r3, inv3] = s3;
 
            int l = max({l1, l2, l3});
            int r = min({r1, r2, r3});
 
            if (r < l) {
                return 0;
            }
 
            return i64(r - l + 1) * inv1 % mod * inv2 % mod * inv3 % mod;
        };
 
        vector<int> size(n);
 
        vector<int> pr(n); // pr[u] = P(color_u = color_{p[u]})
        vector<int> sum_pr(n); // sum_pr[u] = \sum_{v \in u's subtree} pr[v]
        vector<int> sum_pr2(n); // sum_pr2[u] = \sum_{v \in u's subtree} pr[v]^2
         
        vector<int> prc(n); // prc[u] = \sum_{v1, v2 are u's children} ( P(color_u = color_{v1} = color_{v2}) - P(color_u = color_{v1}) P(color_u = color_{v2}) )
        vector<int> prp(n); // prp[u] = \sum_{v is u's child} ( P(color_u = color_v = color_{p[u]}) - P(color_u = color_v) P(color_u = color_{p[u]}) )
        vector<int> sum_pr3(n); // sum_pr3[u] = prc[u] + \sum_{v \in u's subtree} prp[v] + prc[v]
         
        auto dfs = [&](auto && self, int u) -> void {
             
            size[u] = 1;
            pr[u] = pr_same_color(seg[u], seg[p[u]]);
 
            for (auto v: e[u]) {
                self(self, v);
 
                size[u] += size[v];
 
                sum_pr[u] = (sum_pr[u] + sum_pr[v]) % mod;
                sum_pr[u] = (sum_pr[u] + pr[v]) % mod;
 
                sum_pr2[u] = (sum_pr2[u] + sum_pr2[v]) % mod;
                sum_pr2[u] = (sum_pr2[u] + i64(pr[v]) * pr[v] % mod) % mod;
 
                int prob_diff = (pr_3_same_color(seg[p[u]], seg[u], seg[v]) - i64(pr[u]) * pr[v] % mod + mod) % mod;
                prp[u] = (prp[u] + prob_diff) % mod;
 
                sum_pr3[u] = (sum_pr3[u] + sum_pr3[v]) % mod;
                sum_pr3[u] = (sum_pr3[u] + prp[v]) % mod;
 
                for (auto v2: e[u]) {
                    if (v2 == v) {
                        break;
                    }
 
                    int prob_diff = (pr_3_same_color(seg[u], seg[v], seg[v2]) - i64(pr[v]) * pr[v2] % mod + mod) % mod;
                    prc[u] = (prc[u] + prob_diff) % mod;
                }
            }
 
            sum_pr3[u] = (sum_pr3[u] + prc[u]) % mod;
        };
 
        dfs(dfs, 0);
 
        auto upd = [&](int u, Seg seg_u) {
            int sum_pr_diff = 0;
            int sum_pr2_diff = 0;
            int sum_pr3_diff = 0;
 
            int new_prcu = 0;
 
            for (auto v: e[u]) {
                int new_prv = pr_same_color(seg_u, seg[v]);
                sum_pr_diff = ((sum_pr_diff + new_prv) % mod - pr[v] + mod) % mod;
                sum_pr2_diff = ((sum_pr2_diff + i64(new_prv) * new_prv % mod) % mod - i64(pr[v]) * pr[v] % mod + mod) % mod;
                pr[v] = new_prv;
 
                int new_prpv = 0;
                for (auto c: e[v]) {
                    new_prpv = ((new_prpv + pr_3_same_color(seg_u, seg[v], seg[c])) % mod - i64(pr[v]) * pr[c] % mod + mod) % mod;
                }
                sum_pr3_diff = ((sum_pr3_diff + new_prpv) % mod - prp[v] + mod) % mod;
                prp[v] = new_prpv;
                 
                for (auto v2: e[u]) {
                    if (v2 == v) {
                        break;
                    }
                    int prob_diff = (pr_3_same_color(seg_u, seg[v], seg[v2]) - i64(pr[v]) * pr[v2] % mod + mod) % mod;
                    new_prcu = (new_prcu + prob_diff) % mod;
                }
                 
            }
             
            sum_pr3_diff = ((sum_pr3_diff + new_prcu) % mod - prc[u] + mod) % mod;
 
            sum_pr[u] = (sum_pr[u] + sum_pr_diff) % mod;
            sum_pr2[u] = (sum_pr2[u] + sum_pr2_diff) % mod;
            sum_pr3[u] = (sum_pr3[u] + sum_pr3_diff) % mod;
             
            prc[u] = new_prcu;
 
            if (u != 0) {
                int pu = p[u];
 
                int new_pru = pr_same_color(seg[pu], seg_u);
                sum_pr_diff = ((sum_pr_diff + new_pru) % mod - pr[u] + mod) % mod;
                sum_pr2_diff = ((sum_pr2_diff + i64(new_pru) * new_pru % mod) % mod - i64(pr[u]) * pr[u] % mod + mod) % mod;
 
                int new_prpu = 0;
                for (auto v: e[u]) {
                    new_prpu = ((new_prpu + pr_3_same_color(seg_u, seg[pu], seg[v])) % mod - i64(pr[v]) * new_pru % mod + mod) % mod;
                }
                sum_pr3_diff = ((sum_pr3_diff + new_prpu) % mod - prp[u] + mod) % mod;
 
                int prcpu_diff = 0;
                for (auto s: e[pu]) {
                    if (s == u) {
                        continue;
                    }
 
                    int old_value = (pr_3_same_color(seg[u], seg[s], seg[pu]) - i64(pr[u]) * pr[s] % mod + mod) % mod;
                    int new_value = (pr_3_same_color(seg_u, seg[s], seg[pu]) - i64(new_pru) * pr[s] % mod + mod) % mod;
                    prcpu_diff = ((prcpu_diff + new_value) % mod - old_value + mod) % mod;
                }
                sum_pr3_diff = (sum_pr3_diff + prcpu_diff) % mod;
                 
                sum_pr[pu] = (sum_pr[pu] + sum_pr_diff) % mod;
                sum_pr2[pu] = (sum_pr2[pu] + sum_pr2_diff) % mod;
                sum_pr3[pu] = (sum_pr3[pu] + sum_pr3_diff) % mod;
 
                prc[pu] = (prc[pu] + prcpu_diff) % mod;
 
                if (pu != 0) {
                    int gu = p[pu];
                     
                    int old_value = (pr_3_same_color(seg[u], seg[pu], seg[gu]) - i64(pr[u]) * pr[pu] % mod + mod) % mod;
                    int new_value = (pr_3_same_color(seg_u, seg[pu], seg[gu]) - i64(new_pru) * pr[pu] % mod + mod) % mod;
                    int prppu_diff = (new_value - old_value + mod) % mod;
 
                    sum_pr3_diff = (sum_pr3_diff + prppu_diff) % mod;
                    prp[pu] = (prp[pu] + prppu_diff) % mod;
 
                    for (int x = gu; ; x = p[x]) {
                        sum_pr[x] = (sum_pr[x] + sum_pr_diff) % mod;
                        sum_pr2[x] = (sum_pr2[x] + sum_pr2_diff) % mod;
                        sum_pr3[x] = (sum_pr3[x] + sum_pr3_diff) % mod;
 
                        if (x == 0) {
                            break;
                        }
                    }
                }
 
                pr[u] = new_pru;
                prp[u] = new_prpu;
            }
             
            seg[u] = seg_u;
        };
 
        for (int _i = 0; _i < q; _i++) {
            int op, u;
            cin >> op >> u;
            u--;
 
            if (op == 1) {
                int l, r;
                cin >> l >> r;
                 
                int inv = qpow(r - l + 1, mod - 2);
 
                upd(u, Seg{l, r, inv});
                 
            } else {
                int ex = (size[u] - sum_pr[u] + mod) % mod;
                int ex_2 = (i64(size[u]) * size[u] % mod - (2ll * size[u] - 1) * sum_pr[u] % mod + mod) % mod;
                ex_2 = ((ex_2 + i64(sum_pr[u]) * sum_pr[u] % mod) % mod - sum_pr2[u] + mod) % mod;
                ex_2 = (ex_2 + 2ll * sum_pr3[u] % mod) % mod;
 
                int var = (ex_2 - i64(ex) * ex % mod + mod) % mod;
 
                cout << ex << " " << var << "\n";
            }
        }
         
 
    }
    return 0;
}
 
// E[components] = E[n - \sum_{i} d_i] = n - \sum_{i} E[d_i]
// Var(Components) = E[components^2] - E[components]^2
 
// E[ (n - \sum_{i} d_i )^2 ]
// E[ n^2 + \sum_{i} d_i^2 - 2n \sum_{i} d_i + \sum_{i != j} d_i d_j ]
// n^2 - (2n - 1) \sum_{i} E[d_i] + \sum_{i != j} E[d_i d_j]
// n^2 - (2n - 1) \sum_{i} E[d_i] + \sum_{i} E[d_i] (\sum_j E[d_j] - E[d_i]) + 2 \sum_{i, j adjacent} (E[d_i d_j] 