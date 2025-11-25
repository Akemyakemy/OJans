// Problem: G. Cry Me a River
// Contest: Codeforces - Codeforces Round 1047 (Div. 3)
// URL: https://codeforces.com/contest/2137/problem/G
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
	int n,m,q;cin>>n>>m>>q;
	vector<vector<int>> d(n),b(n);
	
	for(int i=0;i<m;i++){
		int x,y;cin>>x>>y;
		x--,y--;
		d[x].push_back(y);
		b[y].push_back(x);
	}
	
	// f[i][j]:node i, player j(0,c,1,r),if c will win
	vector f(n,vector(2,true));
	// false-v child count
	vector c(n,vector(2,0));
	
	auto backtrace=[&](this auto && self, int x, int w)->void{
		if(!f[x][w]) return ;
		f[x][w]=false;
		for(int y:b[x]){
			c[y][1-w]++;
			if(!(1-w)){
				if(c[y][1-w]==d[y].size()) self(y,1-w);
			}else self(y,1-w);
		}
	};
	
	while(q--){
		int tp,u;
		cin>>tp>>u;
		u--;
		if(tp==1){
			//color u red,r win
			backtrace(u,0);
			backtrace(u,1);
		}else{
			cout<<(f[u][0]?"YES":"NO")<<endl;
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