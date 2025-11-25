// Problem: A. Shizuku Hoshikawa and Farm Legs
// Contest: Codeforces - Codeforces Round 1065 (Div. 3)
// URL: https://codeforces.com/contest/2171/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
// #pragma warning(disable:4996)
// typedef long long ll;
// #define int long long
#define register re
#define endl '\n'
#define pii pair<int,int>

inline void solve(){
	int n;cin>>n;
	if(n&1){
		cout<<0<<endl;
		return ;
	}
	cout<<n/4+1<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.tie(nullptr);
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}