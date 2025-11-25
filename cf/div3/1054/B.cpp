// Problem: B. Unconventional Pairs
// Contest: Codeforces - Codeforces Round 1054 (Div. 3)
// URL: https://codeforces.com/contest/2149/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve(){
	int n;cin>>n;
	int mxdiff=0;
	vector<int> a,diff(n+1);
	for(int i=1,tmp;i<=n;i++) {
		cin>>tmp;
		a.push_back(tmp);
	}
	sort(a.begin(),a.end());
	for(int i=1;i<n;i+=2){
		diff[i]=a[i]-a[i-1];
		mxdiff=max(mxdiff,diff[i]);
	}
	cout<<mxdiff<<endl;
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}