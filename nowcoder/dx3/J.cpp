// Problem: Jetton
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108300/J
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <algorithm>//next_permutation(s.begin(), s.end());
#include <numeric>//iota()
#include <ranges>//ranges::sort()
#include <bitset>
#include <bit>//std::bit_width()
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
#define ll long long
const int mod=1e9+7;
 
void solve()
{
    int i, j;
    int n, a;
    int x, y; cin >> x >> y;
    int limit = __lg(x + y) + 1;
     
    int cnt = 0, ok = 0;
    while (limit --) {
        if (x == 0 || y == 0) {
            ok = 1;break;
        }
        if (x <= y) {
            y -= x; 
            x <<= 1;
        }else {
            x -= y;
            y <<= 1;
        }
        cnt ++;
    }
     
    if (!ok) cout << "-1\n";
    else cout << cnt << "\n";
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//     init();
    int t=1;
    cin>>t;
    while(t--)  solve();
    return 0;
}