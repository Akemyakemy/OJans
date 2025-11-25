// Problem: A. Collatz Conjecture
// Contest: Codeforces - Codeforces Round 1047 (Div. 3)
// URL: https://codeforces.com/contest/2137/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// #define int long long
#define endl '\n'

void solve(){
	int k,x;cin>>k>>x;
	cout<<x*pow(2,k)<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}