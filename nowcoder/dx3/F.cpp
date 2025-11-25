// Problem: Flower
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108300/F
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    if(n <= a) {
        cout << "Sayonara" << "\n";
    } else if(n % (a + b) > a) {
        cout << 0 << "\n";
    } else {
        cout << n % (a + b) << "\n";
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}