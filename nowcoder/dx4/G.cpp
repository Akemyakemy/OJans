// Problem: Ghost in the Parentheses
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/G
// Memory Limit: 2048 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define int long long
 
const int P = 998244353;
 
int quick_power(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) {
            res = res * a % P;
        }
        a = a * a % P;
        b >>= 1;
    }
    return res;
}
 
void solve() {
 
    std::string s;
    std::cin>>s;
 
    const int n = s.size();
    std::vector<int> f(n + 1);
 
    for(int i = 0;i < n;i++) {
        f[i + 1] = f[i] + (s[i] == '('?1 : -1);
    }
 
    //  dp[0] : 没有填 ? 的方案数
    //  dp[1] : 上一次在 ( 填? 的方案数
    //  dp[2] : 上一次在 ) 填? 的方案数
 
    /*
        观察发现，倘若在 第 i 个位置填写 ? 且 上一个填写 ? 的位置为 j， 如果
        s[i] != s[j] && f[i] > 0， 那么一定不合法.
    */
 
    std::array<int, 3> dp = {0, 0, 0};
    dp[1] = 1;
 
    for(int i = 0;i < n;i++) {
        if(f[i] <= 1) {
            dp[1] += dp[0];
            dp[0] = 0;
        }
        auto ndp = dp;
        if(s[i] == '(') {
            ndp[0] += dp[0] + dp[1];
        } else {
            if(f[i + 1] == 0) {
                ndp[2] += dp[0] + dp[1];
            } else {
                ndp[2] += dp[1];
            }
            ndp[2] += dp[2];
        }
        dp = ndp;
        for(auto& x : dp) {
            x %= P;
        }
    }
 
    int ans = (dp[0] + dp[1] + dp[2]) % P * quick_power(quick_power(2, n), P - 2) % P;
    std::cout<<ans<<"\n";
}
 
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int t = 1;
    // std::cin>>t;
    while (t--) {
        solve();
    }
 
    return 0;
}