// Problem: E. Adjacent XOR
// Contest: Codeforces - Codeforces Round 1042 (Div. 3)
// URL: https://codeforces.com/contest/2131/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
// typedef long long ll;
#define int long long
#define endl '\n'
#define pii pair<int,int>

inline void solve(){
	int n;cin>>n;
	vector<int> a(n+1,0);
	vector<int> b(n+1,0);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	
	if(a[n]^b[n]){
		cout<<"NO"<<endl;
		return ;
	}
	for(int i=1;i<n;i++){
		if(a[i]^b[i] && a[i]^a[i+1]^b[i] && a[i]^b[i+1]^b[i]){
			cout<<"NO"<<endl;
			return ;
		}
	}
	cout<<"YES"<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}