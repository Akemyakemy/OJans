// Problem: T600132 Lamborghini (Remix)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T600132?contestId=242706
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
	int n;cin>>n;
	vector<int> a(n+1),prea(n+1,0),diff(n+1,0);
	int mx=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]++;
		mx=max(mx,a[i]);
		prea[i]=prea[i-1]+a[i];
	}
	int ans=1;
	for(int i=1;i<=n;i++){
		if(mx>=prea[i]) {
			ans=max(ans,i);
			continue;
		}else{
			int pos=lower_bound(prea.begin()+1,prea.end(),prea[i]-mx)-prea.begin();
			if(prea[i]-prea[pos]==mx) ans=max(ans,i-pos);
			else ans=max(ans,i-pos+1);
		}
	}
	cout<<ans<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.tie(nullptr);
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}