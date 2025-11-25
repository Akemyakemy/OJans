// Problem: A. Be Positive
// Contest: Codeforces - Codeforces Round 1054 (Div. 3)
// URL: https://codeforces.com/contest/2149/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
void solve(){
	int n;cin>>n;
	vector<int> a(n+1);
	int cnt_1=0,cnt0=0,cnt1=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==-1) cnt_1++;
		else if(!a[i]) cnt0++;
		else cnt1++;
	}
	int ans=cnt0;
	if(cnt_1%2) ans+=2;
	cout<<ans<<endl;
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}