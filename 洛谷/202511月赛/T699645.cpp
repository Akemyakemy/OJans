// Problem: T699645 [语言月赛 202511] 打火基
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T699645?contestId=291890
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

// #define debug
inline void solve(){
	int n,x;cin>>n;
	int f=0;
	int cnt=0;
	for(int i=1;i<=n;i++){
		cin>>x;
		if(i==1){
			f=(x&1);
			continue;
		}
		int tmp=(x&1);
		#ifdef debug
		cout<<tmp<<endl;
		#endif
		if(tmp^f){
			cnt++;
			f=tmp;
		}
	}
	cout<<cnt<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.tie(nullptr);
	// int t;cin>>t;
	// while(t--)
	solve();
	return 0;
}