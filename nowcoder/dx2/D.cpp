// Problem: Donkey Thinks...
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/D
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
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
 
constexpr i64 inf = 1e18;
 
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
     
    int T;
    cin >> T;
 
    while (T--) {
        int n, v;
        cin >> n >> v;
 
        vector<vector<pair<i64, i64>>> hd(v + 1);
        for (int i = 0; i < n; i++) {
            int h, s, d;
            cin >> h >> s >> d;
            if (s > v) {
                continue;
            }
            hd[s].emplace_back(h, d);
        }
 
        vector<i64> dp(v + 1);
 
        i64 ans = 0;
 
        for (int u = 0; u <= v; u++) {
            for (int s = 1; s <= v - u; s++) {
                nth_element(hd[s].begin(), hd[s].begin() + (v - u) / s, hd[s].end(), [&](const auto & hd1, const auto & hd2) {
                    return hd1.first - hd1.second * u > hd2.first - hd2.second * u;
                });
            }
 
            fill(dp.begin(), dp.end(), -inf);
            dp[0] = 0;
 
            for (int s = 1; s <= v - u; s++) {
                for (int i = 0; i < (v - u) / s && i < int(hd[s].size()); i++) {
                    i64 value = hd[s][i].first - hd[s][i].second * u;
                    for (int j = v - u; j >= s; j--) {
                        dp[j] = max(dp[j], dp[j - s] + value);
                    }
                }
            }
 
            ans = max(ans, dp[v - u]);
        }
 
        cout << ans << "\n";
    }
 
    return 0;
}