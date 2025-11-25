// Problem: P12391 「RiOI-6」帝国少女
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12391
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
//typedef long long ll;
#define int long long
#define endl '\n'
#define pii pair<int,int>
const int N=2e5+1;

int n,m,a[N],sum[N],ans;
vector<pii> vec;

inline void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	if(m==2){
		for(int i=1;i<=n;i++){
			if(a[i]==2) a[i]=-1;
			if(i&1) a[i]=-a[i];
		}
		
		sum[0]=0;
		for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
		sort(sum,sum+n+1);
		
		for(int len=1;len<=n;len++) ans+=len*(n-len+1);
		for(int i=1;i<=n;i++) ans-=(sum[i]*i-sum[i-1]*(n-i+1));
		ans>>=1;
	}else{
		int lst=1;
		for(int i=2;i<=n+1;i++){
			if(i==n+1 || a[i]!=a[i-1]){
				vec.emplace_back(lst,i-1);
				lst=i;
			}
		}
		
		for(auto [l,r]:vec){
			int ll=r-l+1;
			int cnt=ll/2;

			for(int len=1;len<=ll;len++){
				int k=len/2;
				ans+=k*(ll-len+1);
				ans+=k*(l-1);
				ans+=k*(n-r);
			}
			ans+=(l-1)*(n-r)*cnt;
		}
	}
	
	cout<<ans<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	// int t;cin>>t;
	// while(t--)
	solve();
	return 0;
}
