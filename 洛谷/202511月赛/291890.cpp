// Problem: T699642 [语言月赛 202511] 曼波 No More
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T699642?contestId=291890
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#pragma warning(disable:4996)
// typedef long long ll;
#define int long long
#define register re
#define endl '\n'
#define pii pair<int,int>

inline void solve(){
	int n,m,r,c;cin>>n>>m>>r>>c;
	int x,y,xx,yy;cin>>x>>y>>xx>>yy;
	x++,y++,xx++,yy++;
	int a=0,b=0;
	a+=xx/r-(x-1)/r;
	if(xx%r) a++;
	b+=yy/c-(y-1)/c;
	if(yy%c) b++;
	cout<<a*b<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.tie(nullptr);
	// int t;cin>>t;
	// while(t--)
	solve();
	return 0;
}