#include<bits/stdc++.h>
using namespace std;
const int N=3010;
void solve(){
	int n,m;cin>>n>>m;
	vector<int> l(m+1),r(m+1),f(n+1,0),st(n+1),en(n+1);
	for(int i=1;i<=m;i++){
		cin>>l[i]>>r[i];
		st[l[i]]=1;
		en[r[i]]=1;
		for(int j=l[i];j<=r[i];j++) f[j]++;
	}
	
	vector<int> ans(n+1,-1);
	auto fill=[&](){
		vector<bool> used(n+1,0);
		for(int i=1;i<=n;i++) if(ans[i]!=-1) used[ans[i]]=1;
		
		int p=0;
		for(int i=1;i<=n;i++){
			if(ans[i]==-1){
				while(used[p]) p++;
				ans[i]=p;
				used[p]=1;
			}
		}
		
		for(int i=1;i<=n;i++) cout<<ans[i]<<" \n"[i==n];
	};
	
	for(int i=1;i<=n;i++){
		if(f[i]==m){
			int ptr=1;
			ans[i]=0;
			
			fill();
			return ;
		}
	}
	
	for(int i=1;i<n;i++){
		if(en[i]==0){
			ans[i]=0;
			ans[i+1]=1;
			
			fill();
			return ;
		}
		if(st[i+1]==0){
			ans[i]=1;
			ans[i+1]=0;
			
			fill();
			return ;
		}
	}
	
	assert(n>=3);
	ans[1]=0;
	ans[2]=2;
	ans[3]=1;
	
	fill();
	
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--) solve();
	return 0;
}