// Problem: T619940 坤班
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T619940?contestId=242706
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#pragma warning(disable:4996)
//typedef long long ll;
#define int long long
#define register re
#define pii pair<int,int>
#define endl '\n'
#define x first
#define y second

// #define debug
inline void solve(){
	int n,m;cin>>n>>m;
	
	vector<pii> st(m+1,{0,0});
	int ans=0,cntc=0;
	for(int i=1,a,b,c;i<=n;i++){
		cin>>a>>b>>c;
		if(c){
			cntc++;
			st[a].y++;
		}
		st[a].x+=b;
	}
	sort(st.begin()+1,st.end());
	
	int l=0,r=min(cntc,st[1].x)+1;
	while(l<r){
		int mid=(l+r)>>1;
		int tot=0;
		for(int i=m;i>0;i--){
			int c=min(st[i].y,st[i].x-mid);
			tot+=c;
			if(tot>=mid) break;
		}
		if(tot>=mid){
			ans=mid;
			l=mid+1;
		}else r=mid;
	}
	
	cout<<ans<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.tie(nullptr);
	// int t;cin>>t;
	// while(t--)
	solve();
	return 0;
}