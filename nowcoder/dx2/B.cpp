// Problem: Bitwise Perfect
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/B
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

/*
    网址：https://ac.nowcoder.com/acm/contest/108299/B
    标签：线性统计，对比统计化，数学
    结论：
        1. max(x, y) >= z => 2^x + 2^y > 2^z
        2.
    做题思路：
        根据结论，原要求即求是否存在(x, y)，使得max(x, y) >= x ^ y。
        但是一个个对比的时间复杂度较大，需要一个最多O(nlogn)级别的算法
 
*/
 
#ifdef DBG
#include "bits/dbg/stdc++.h"
#elif XCPC
#include "bits/stdc++.h"
#else
#include <bits/stdc++.h>
#endif
 
#define ln(x) log(x)    // log_e
#define lg(x) log10(x)  // log_10
#define lq(x) (__lg(x)) // log_2
#define lcm(x, y) (x / gcd(x, y) * y)
#define popcnt(x) (__builtin_popcountll(x))
#define highbit(x) (x == 0 ? 0 : (1ll << lq(x)))
#define lowbit(x) (x & -x)
#define inrange(l, n, r) (l <= n && n <= r)
using ll = long long;
using ull = unsigned long long;
constexpr int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };
constexpr int inf = INT_MAX / 2;
constexpr ll linf = LLONG_MAX / 2;
constexpr int mod = 998244353;
using namespace std;
 
void solve() {
    int n;
    cin >> n;
    vector <ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (n > 65) {
        cout << "NO\n";
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            ll x = arr[i] ^ arr[j];
            if (max(arr[i], arr[j]) >= x) {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
}
 
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}