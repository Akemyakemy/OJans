// Problem: A. Lever
// Contest: Codeforces - Codeforces Round 1042 (Div. 3)
// URL: https://codeforces.com/contest/2131/problem/A
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// #define int long long
#define endl '\n'
#define pii pair<int,int>

inline void solve(){
	int n;cin>>n;
	vector<int> a(n+1),b(n+1),c(n+1);
	for(int i=1;i<=n;i++) cin>>a[i];
	int cnt=1;
	for(int i=1;i<=n;i++){
		cin>>b[i];
		c[i]=a[i]-b[i];
		if(c[i]>0) cnt+=c[i];
	}
	cout<<cnt<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}