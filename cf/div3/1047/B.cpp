// Problem: B. Fun Permutation
// Contest: Codeforces - Codeforces Round 1047 (Div. 3)
// URL: https://codeforces.com/contest/2137/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// #define int long long
#define endl '\n'

void solve(){
	int n;cin>>n;
	vector<int> p(n+1);
	for(int i=1;i<=n;i++){
		cin>>p[i];
		cout<<n-p[i]+1<<" ";
	}
	cout<<endl;
	
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}