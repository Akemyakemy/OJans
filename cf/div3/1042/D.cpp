// Problem: D. Arboris Contractio
// Contest: Codeforces - Codeforces Round 1042 (Div. 3)
// URL: https://codeforces.com/contest/2131/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;

inline void solve(){
	int n;cin>>n;
	vector g(n+1,vector<int>());
	vector<int> e(n+1,0);
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
		e[u]++;
		e[v]++;
	}
	if(n<=3){
		cout<<0<<endl;
		return;
	}
	
	int c1=0;
	for(int i=1;i<=n;i++){
		if(e[i]==1) c1++;
	}
	int mx=0;
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(auto v:g[i]){
			if(e[v]==1) cnt++;
		}
		mx=max(mx,cnt);
	}
	cout<<c1-mx<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--) solve();
	return 0;
}