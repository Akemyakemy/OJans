// Problem: Geometry Friend
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/G
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
#define fi first
#define se second
double x, y;
typedef pair<ll, ll> pii;
vector<pii> arr(500005);
 
ll dist(pii a, pii b) {
    ll dex = a.fi - b.fi, dey = a.se - b.se;
    return dex * dex + dey * dey;
}
 
ll cha(pii a, pii b, pii c) {
    ll x1 = a.fi - c.fi, x2 = b.fi - c.fi, y1 = a.se - c.se, y2 = b.se - c.se;
    return x1 * y2 - x2 * y1;
}
 
void solve() {
    cin >> n >> x >> y;
    arr[0].fi = x, arr[0].se = y;
    ll ff = 0, ko, op, fla = 1;
    for (ll i = 1; i <= n; i++)
        cin >> arr[i].fi >> arr[i].se;
    arr[n + 1].fi = arr[1].fi, arr[n + 1].se = arr[1].se;
    for (ll i = 1; i <= n; i++) {
        if (cha(arr[i], arr[i + 1], arr[0]) < 0) {
            fla = 0;
            break;
        }
        if (cha(arr[i], arr[i + 1], arr[0]) == 0) {
            ff = 1;
        }
    }
    if (!fla) {
        printf("%.11lf\n", 2 * M_PI);
        return;
    } else {
        vector<double>so;
        ll madi = 0;
        for (ll i = 1; i <= n; i++)
            madi = max(madi, dist(arr[0], arr[i]));
        for (ll i = 1; i <= n; i++) {
            if (dist(arr[i], arr[0]) == madi) {
                double ang = atan2(arr[i].fi - arr[0].fi, arr[i].se - arr[0].se);
                if (ang < 0)
                    ang = 2 * M_PI + ang;
                so.push_back(ang);
            }
        }
        sort(so.begin(), so.end());
        so.push_back(so[0] + 2 * M_PI);
        double ma = 0.0;
        for (ll i = 0; i < so.size() - 1; i++) {
            ma = max(ma, fabs(so[i + 1] - so[i]));
        }
        printf("%.11lf\n", ma);
    }
}
 
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll t;
    t = 1;
    cin >> t;
 
    while (t--) {
        solve();
    }
    return 0;
}