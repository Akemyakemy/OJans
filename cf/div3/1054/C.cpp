// Problem: C. MEX rose
// Contest: Codeforces - Codeforces Round 1054 (Div. 3)
// URL: https://codeforces.com/contest/2149/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;

// #define debug
void solve(){
	int n,k;cin>>n>>k;//mex(a)==k  1~k-1 must be included in a
	int tag[k+1]={0};
	vector<int> a(n+1);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]>k) continue;
		tag[a[i]]++;
		#ifdef debug
		if(a[i]==k)
			cout<<i<<" "<<a[i]<<" "<<tag[a[i]]<<endl;
		#endif
	}
	int cnt=0;
	for(int i=0;i<k;i++) if(!tag[i]){
		cnt++;
		if(tag[k]) tag[k]--;
	}
	#ifdef debug
	cout<<"tag[k] "<<k<<":"<<tag[k]<<endl;
	#endif
	if(tag[k]) cnt+=tag[k];
	cout<<cnt<<endl;
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}