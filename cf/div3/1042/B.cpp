// Problem: B. Alternating Series
// Contest: Codeforces - Codeforces Round 1042 (Div. 3)
// URL: https://codeforces.com/contest/2131/problem/B
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
	if(n==2) cout<<"-1 2\n";
	else{
		int f[]={-1,3,1};
		for(int i=1;i<=n;i++){
			if(i&1) cout<<f[0];
			else{
				if(i^n) cout<<f[1];
				else cout<<2;
			}
			cout<<" \n"[i==n];
		}
	}
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}