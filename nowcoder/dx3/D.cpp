// Problem: Distant Control
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108300/D
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
    cin >> n >> a;
    string s; cin >> s;
     
    if (a == 1) {
        cout << n << "\n";
        return;
    }
     
    int b[2] = {0}, cnt = 1;
    bool ok = 0;
    b[s[0] - '0'] ++;
     
    for (i = 1; i < n; i ++) {
        b[s[i] - '0'] ++;
        if (s[i] == s[i - 1]) {
            cnt ++;
            if (s[i] == '0' && cnt >= a + 1 ||
                s[i] == '1' && cnt >= a) ok = 1;
        }else {
            cnt = 1;
        }
    }
     
    if (ok) cout << n << "\n";
    else cout << b[1] << "\n";
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