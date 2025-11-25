// Problem: G. Beautiful Tree
// Contest: Codeforces - Codeforces Round 1059 (Div. 3)
// URL: https://codeforces.com/contest/2162/problem/G
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
void solve(){
	int n;cin>>n;
	if(n==2){
		cout<<-1<<endl;
	}else if(n==3) cout<<"1 3\n2 3\n";
	else if(n==4) cout<<"1 2\n3 1\n4 1\n";
	else{
		cout<<"1 2\n2 3\n3 4\n1 "<<n<<"\n";
		for(int i=5;i<n;i++) cout<<"2 "<<i<<endl;
	}
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}