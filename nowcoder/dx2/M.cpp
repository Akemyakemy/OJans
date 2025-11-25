// Problem: Miscalculated Triangles
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/M
// Memory Limit: 1024 MB
// Time Limit: 8000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
// #define int long long
using namespace std;
const int N = 1e5 + 10;
const int mod = 998244353;
 
int len, s[N], l[N];
int dp[N][2][2][2][2][4];
int dfs(int pos, int ab, int bc, int cs, int abcl, int abc)
{
    if (!pos)
    {
        if (abc < 1)
            return 0;
        return 1 + (ab && bc);
    }
    if (dp[pos][ab][bc][cs][abcl][abc + 1] != -1)
        return dp[pos][ab][bc][cs][abcl][abc + 1];
    int ans = 0;
    int upc = !cs ? s[pos] : 1;
    for (int i = 0; i <= 1; i++)
    {
        for (int j = 0; j <= 1; j++)
        {
            if (!ab && i > j)
                continue;
            for (int k = 0; k <= upc; k++)
            {
                if (!bc && j > k)
                    continue;
                if (!abcl && (i ^ j ^ k) > l[pos])
                    continue;
                if (abc * 2 + i + j - k < -1)
                    continue;
                ans += dfs(pos - 1, ab || i < j, bc || j < k, cs || k != upc, abcl || ((i ^ j ^ k) < l[pos]), min(2, abc * 2 + i + j - k));
                if (ans >= mod)
                    ans -= mod;
            }
        }
    }
    return dp[pos][ab][bc][cs][abcl][abc + 1] = ans;
}
int get_ans(int len)
{
    for (int i = 0; i <= len; i++)
        dp[i][0][0][0][0][0] = -1, dp[i][0][0][0][0][1] = -1, dp[i][0][0][0][0][2] = -1, dp[i][0][0][0][0][3] = -1, dp[i][0][0][0][1][0] = -1, dp[i][0][0][0][1][1] = -1, dp[i][0][0][0][1][2] = -1, dp[i][0][0][0][1][3] = -1, dp[i][0][0][1][0][0] = -1, dp[i][0][0][1][0][1] = -1, dp[i][0][0][1][0][2] = -1, dp[i][0][0][1][0][3] = -1, dp[i][0][0][1][1][0] = -1, dp[i][0][0][1][1][1] = -1, dp[i][0][0][1][1][2] = -1, dp[i][0][0][1][1][3] = -1, dp[i][0][1][0][0][0] = -1, dp[i][0][1][0][0][1] = -1, dp[i][0][1][0][0][2] = -1, dp[i][0][1][0][0][3] = -1, dp[i][0][1][0][1][0] = -1, dp[i][0][1][0][1][1] = -1, dp[i][0][1][0][1][2] = -1, dp[i][0][1][0][1][3] = -1, dp[i][0][1][1][0][0] = -1, dp[i][0][1][1][0][1] = -1, dp[i][0][1][1][0][2] = -1, dp[i][0][1][1][0][3] = -1, dp[i][0][1][1][1][0] = -1, dp[i][0][1][1][1][1] = -1, dp[i][0][1][1][1][2] = -1, dp[i][0][1][1][1][3] = -1, dp[i][1][0][0][0][0] = -1, dp[i][1][0][0][0][1] = -1, dp[i][1][0][0][0][2] = -1, dp[i][1][0][0][0][3] = -1, dp[i][1][0][0][1][0] = -1, dp[i][1][0][0][1][1] = -1, dp[i][1][0][0][1][2] = -1, dp[i][1][0][0][1][3] = -1, dp[i][1][0][1][0][0] = -1, dp[i][1][0][1][0][1] = -1, dp[i][1][0][1][0][2] = -1, dp[i][1][0][1][0][3] = -1, dp[i][1][0][1][1][0] = -1, dp[i][1][0][1][1][1] = -1, dp[i][1][0][1][1][2] = -1, dp[i][1][0][1][1][3] = -1, dp[i][1][1][0][0][0] = -1, dp[i][1][1][0][0][1] = -1, dp[i][1][1][0][0][2] = -1, dp[i][1][1][0][0][3] = -1, dp[i][1][1][0][1][0] = -1, dp[i][1][1][0][1][1] = -1, dp[i][1][1][0][1][2] = -1, dp[i][1][1][0][1][3] = -1, dp[i][1][1][1][0][0] = -1, dp[i][1][1][1][0][1] = -1, dp[i][1][1][1][0][2] = -1, dp[i][1][1][1][0][3] = -1, dp[i][1][1][1][1][0] = -1, dp[i][1][1][1][1][1] = -1, dp[i][1][1][1][1][2] = -1, dp[i][1][1][1][1][3] = -1;
    return dfs(len, 0, 0, 0, 0, 0);
}
 
void solve()
{
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 1; i <= max(n, m); i++)
        l[i] = s[i] = 0;
    for (int i = 1; i <= n; i++)
        l[i] = a[i - 1] == '1';
    for (int i = 1; i <= m; i++)
        s[i] = b[i - 1] == '1';
    cout << get_ans(max(n, m)) << '\n';
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int tt = 1;
    cin >> tt;
    while (tt--)
        solve();
}