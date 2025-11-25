// Problem: F. Prefix Maximum Invariance
// Contest: Codeforces - Codeforces Round 1047 (Div. 3)
// URL: https://codeforces.com/contest/2137/problem/F
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define endl '\n'

inline void solve(){
	int n;cin>>n;
	vector<int> a(n+1),b(n+1);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	//稀疏表
	int max_j=log2(n);
	vector st(n+1,vector<int>(max_j+1));
	for(int i=1;i<=n;i++) st[i][0]=a[i];
	for(int j=1;j<=max_j;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	//O（1） 查询
	auto query=[&](int l,int r){
		assert(r>=l);
		// cout<<l<<" "<<r<<endl;
		int k=31-__builtin_clz(r-l+1);
		return max(st[l][k],st[r-(1<<k)+1][k]);
	};
	
	int ans=0;
	for(int i=1;i<=n;i++){
		if(a[i]==b[i]) {ans+=i*(n-i+1);continue;}
		// int l=1,r=i;
		// if(a[i]>b[i]){
			// while(l<r){
				// int mid=(l+r)>>1;
				// if(query(mid,r-1)>=a[i]) l=mid+1;
				// else r=mid;
			// }
		// }else{
			// while(l<r){
				// int mid=(l+r)>>1;
				// if(query(mid,r-1)>=b[i]) l=mid+1;
				// else r=mid;
			// }
		// }
		int l=1,r=i;
		while(l<r){//l<r 保证了l不会等于r，所以不会出现 mid < r 的情况，所以巧合般的草过去了
			int mid=(l+r)>>1;
			// cout<<mid<<" "<<r-1<<endl;
			if(query(mid,i-1/*r-1*/)>=max(a[i],b[i])) l=mid+1;
			else r=mid;
		}
		ans+=(l-1)*(n-i+1);
	}
	cout<<ans<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}