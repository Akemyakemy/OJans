// Problem: A. Homework
// Contest: Codeforces - Codeforces Round 1043 (Div. 3)
// URL: https://codeforces.com/contest/2132/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// #define int long long
#define endl '\n'

inline void solve(){
	int n;cin>>n;
	string a;cin>>a;
	int m;cin>>m;
	string b;cin>>b;
	string c;cin>>c;
	
	for(int i=0;i<m;i++){
		if(c[i]=='V') a=b[i]+a;
		else a=a+b[i];
	}
	
	cout<<a<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}