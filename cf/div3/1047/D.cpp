// Problem: D. Replace with Occurrences
// Contest: Codeforces - Codeforces Round 1047 (Div. 3)
// URL: https://codeforces.com/contest/2137/problem/D
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
	vector<int> b(n+1),a(n+1);
	for(int i=1;i<=n;i++) cin>>b[i];
	
	vector idx(n+1,vector<int>());
	for(int i=1;i<=n;i++) idx[b[i]].push_back(i);
	
	int cnt=1;
	for(int i=1;i<=n;i++){
		if(idx[i].size()%i){
			cout<<-1<<endl;
			return ;
		}
		int c=0;
		while(c<idx[i].size()){
			for(int j=1;j<=i;j++){
				a[idx[i][c]]=cnt;
				c++;
			}
			cnt++;
		}
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	cout<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}