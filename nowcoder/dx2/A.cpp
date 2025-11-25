// Problem: Another Day of Sun
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/A
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int, int> pii;
#define vecin(name, len) vector<int> name(len); for (auto &_ : name) cin >> _;
#define vecout(v) for (auto _ : v) cout << _ << " "; cout << endl;
#define x first
#define y second
#define rep(i, a, b) for(int i = a; i < b; i ++)
#define debug(x) cout<<#x<<" = "<<x<<endl
#define all(a) a.begin(), a.end()
constexpr int inf = 1E18;
const int mod = 998244353;
void solve()
{
    int n;int c0 = 0, c1 = 0, c2 = 0;
    cin >> n;
    vector<int> v(n + 1, 0);
    for(int i = 1; i <= n; i ++) {
        cin >> v[i];
        if(v[i] == 1 && v[i - 1] == 0) {
            c0 ++;
        }
        if(v[i] == -1 && v[i - 1] == 0) {
            c1 ++;
        }
        if(v[i] == 1 && v[i - 1] == -1) {
            c1 ++;
        }
        if(v[i] == -1 && v[i - 1] == -1) {
            c2 ++;
        }
    }
     
     
     
    int inv2 = (mod + 1) / 2, inv4 = inv2 * inv2 % mod;
    int ans = c0;
    ans = (ans + c1 * inv2 % mod) % mod;
    ans = (ans + c2 * inv4 % mod) % mod;
     
    for(int i = 0; i <= n; i ++) {
        if(v[i] == -1) {
			ans=ans*2%mod;
        }
    }
    cout << ans << "\n";
     
}
 
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t = 1;
    cin >> t;
    while(t --) 
    {
        solve();
    }
    return 0;
}