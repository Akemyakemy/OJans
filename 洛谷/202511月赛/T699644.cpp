// Problem: T699644 [语言月赛 202511] 基米说
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T699644?contestId=291890
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

const int mod=1e9+7;

// #define debug
inline void solve(){
	vector<int> a(4,0),b(4,0);
	for(int i=1;i<=3;i++) cin>>a[i];
	for(int i=1;i<=3;i++) cin>>b[i];
	int ans=0;
	for(int i=1;i<=3;i++){
		ans=(ans+a[i]*b[i])%mod;
		#ifdef debug
		cout<<ans<<endl;
		#endif
	}
	if(!ans) cout<<"Orthogonal"<<endl;
	else cout<<"Non-Orthogonal"<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.tie(nullptr);
	// int t;cin>>t;
	// while(t--)
	solve();
	return 0;
}