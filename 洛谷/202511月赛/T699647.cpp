// Problem: T699647 [语言月赛 202511] 基米起床
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T699647?contestId=291890
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#pragma warning(disable:4996)
// typedef long long ll;
// #define int long long
#define register re
#define endl '\n'
#define pii pair<int,int>

inline void solve(){
	int n,m;cin>>n>>m;
	vector<vector<char>> g(n+1,vector<char>(m+1));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(j&1) g[i][j]='x';
			else g[i][j]='.';
		}
	}
	for(int j=4;j<=m;j+=4) g[1][j]='x';
	for(int j=2;j<=m;j+=4) g[n][j]='x';
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cout<<g[i][j];
		cout<<endl;
	}
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.tie(nullptr);
	// int t;cin>>t;
	// while(t--)
	solve();
	return 0;
}