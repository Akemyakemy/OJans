// Problem: C. Maximum Even Sum
// Contest: Codeforces - Codeforces Round 1047 (Div. 3)
// URL: https://codeforces.com/contest/2137/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define endl '\n'

void solve(){
	vector<int> k;
	int a,b;cin>>a>>b;
	int ans=-1;
	if(!((a+b)&1)) ans=a+b;
	if((a&1) && (b&1)) ans=max(ans,a*b+1);
	else if(!(a&1) && b%2==0) ans=max(ans,2+(a*b)/2);
	else if((a&1) && (b%4==0)) ans=max(ans,2+(a*b)/2);
	cout<<ans<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}