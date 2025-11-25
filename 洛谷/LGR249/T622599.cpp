// Problem: T622599 批话哥
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T622599?contestId=242706
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#pragma warning(disable:4996)
// typedef long long ll;
#define int long long
#define register re
#define endl '\n'
#define pii pair<int,int>

inline void solve(){
	int n,m,k,l,r;cin>>n>>m>>k>>l>>r;
	vector a(n+1,vector<int>(m+1,0));
	for(int i=1,x,y,v;i<=k;i++){
		cin>>x>>y>>v;
		if(v<=l) v=100;
		else if(v>=r) v=0;
		a[x][y]=v;
	}
	
	for(int i=1;i<=n;i++){
		int ans=0;
		for(int j=1;j<=m;j++){
			ans+=a[i][j];
		}
		cout<<ans<<' ';
	}
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.tie(nullptr);
	// int t;cin>>t;
	// while(t--)
	solve();
	return 0;
}