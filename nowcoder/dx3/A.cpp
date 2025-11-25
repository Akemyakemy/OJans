// Problem: Ad-hoc Newbie
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108300/A
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#ifndef DEBUG
#define debug
#endif
#define int long long
 
using namespace std;
void solve(){
  int n; cin >> n;
  vector<int> a(n);
  vector<vector<int>> ans(n, vector<int>(n, 0));
  for(auto &v : a) cin >> v;
  for(int i = 0; i < n; i++) {
    for(int j = 2; j < a[i]; j++) {
        ans[i][j-2] = j;
        ans[j-2][i] = j;
        // debug(ans);
    }
    if(a[i] > 1) ans[i][i] = 1;//因为我们从2开始填， 如果a[i] > 1 的话， 我们需要mex为 a[i], 而1并没有被构造过
  }
  debug(ans);
  for(auto &row : ans ){
    for(auto &v : row) cout << v << ' ';
    cout << "\n";
  }
  return ;
}
 
signed main(){
  cin.tie(0) ->sync_with_stdio(false);
  int t = 1; cin >> t;
  while(t--){
     solve();
  }
    
  return 0;
}