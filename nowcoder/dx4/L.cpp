// Problem: Ladder Challenge
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/L
// Memory Limit: 2048 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e5+10;
const int mod = 1e9+7;
int a[N],b0[N],c[N];
int d[N];
void solve() {
    int n,q;
    cin >> n >> q;
    for(int i = 1;i <= n; ++i)cin >> a[i];
    int x = 1;
    int l = 1;
    for(int i = 1;i <= n; ++i) {
        d[i] = d[i-1]-b0[i-1]+(b0[i-1]+a[i]+1>>1);
        b0[i] = b0[i-1]+a[i]+1>>1;
        x = x+a[i]+1>> 1;
        if( b0[i] == x ) {
            for(int j = l;j < i; ++j) c[j] = i;
            l = i;
            x++;
        }
    }
    for(int j = l;j <= n; ++j) c[j] = n+1;
    while( q-- ) {
        int y;
        cin >> x >> y;
        int now = upper_bound(a+1,a+n+1,x)-a;
        y = n-y+1;
        int res = 0;
        while( now <= y ) {
            res += (x+a[now]+1)/2-x;
            x = (x+a[now]+1)/2;
            if( x == b0[now]+1 && c[now] <= y )res--;
            if( x <= b0[now]+1 ) res += d[y]-d[now],now = y;
            now++;
        }
        cout << res << endl;
    }
}
signed main() {
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while( T-- ) {
        solve();
    }
    return 0;
}