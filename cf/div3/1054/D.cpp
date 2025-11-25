// Problem: D. A and B
// Contest: Codeforces - Codeforces Round 1054 (Div. 3)
// URL: https://codeforces.com/contest/2149/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

string s;
ll cal(char c){
	vector<int> p;
	int cnt=0;
	for(int i=0;i<s.size();i++){
		if(s[i]==c){
			p.push_back(i+1-cnt);
			cnt++;
		}
	}
	if(p.empty()) return 0ll;
	
	int sz=p.size();
	int d=p[sz/2];
	
	ll ans=0;
	for(int i=0;i<sz;i++) ans+=abs(p[i]-d);
	return ans;
	
}

void solve(){
	int n;cin>>n>>s;
	
	cout<<min(cal('a'),cal('b'))<<endl;
	
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}