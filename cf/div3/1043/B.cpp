// Problem: B. The Secret Number
// Contest: Codeforces - Codeforces Round 1043 (Div. 3)
// URL: https://codeforces.com/contest/2132/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define endl '\n'

inline void solve(){
	int n;cin>>n;
	int ans=0;
	int cnt=1;
	vector<int> res;
	for(int i=11;cnt<=18;i=(i-1)*10+1){
		if(i>n) break;
		if(!(n%i)){
			ans=n/i;
			res.push_back(ans);
			// cout<<ans<<" ";
		}
		cnt++;
	}
	cout<<res.size()<<endl;
	for(int i=res.size()-1;i>=0;i--) cout<<res[i]<<" ";
	if(ans) cout<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}