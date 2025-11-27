// Problem: H. Sea, You & copriMe
// Contest: Codeforces - Codeforces Round 1042 (Div. 3)
// URL: https://codeforces.com/contest/2131/problem/H
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
// #pragma warning(disable:4996)
// typedef long long ll;
// #define int long long
#define register re
#define endl '\n'
#define pii pair<int,int>

const int M=1e6+9;
array<int,M> mu,comp;
vector<int> primes;


void init(){
	mu[1]=1;
	
	for(int i=2;i<M;i++){
		if(!comp[i]){
			primes.emplace_back(i);
			mu[i]=-1;
		}
		for(auto p:primes){
			int q=i*p;
			if(q>=M) break;
			comp[q]=true;
			if(i%p==0){
				mu[q]=0;
				break;
			}else{
				mu[q]=-mu[i];
			}
		}
	}
}

inline void solve(){
	int n,m;cin>>n>>m;
	m=0;
	vector<int> a(n);
	
	for(int i=0;i<n;i++){
		cin>>a[i];
		m=max(m,a[i]);
	}
	
	vector<int> mul(m+1,0),deg(n),mp(m+1);
	for(int i=0;i<n;i++) mp[a[i]]++;
	
	for(int j=1;j<=m;j++){
		for(int x=j;x<=m;x+=j) mul[j]+=mp[x];
	}
	
	for(int i=0;i<n;i++){
		for(int j=1;j*j<=a[i];j++){
			if(a[i]%j==0){
				deg[i]+=mu[j]*mul[j];
				if(j*j<a[i]){
					deg[i]+=mu[a[i]/j]*mul[a[i]/j];
				}
			}
		}
		if(a[i]==1) deg[i]--;
	}
	
	array<int,4> ans;
	int u=0,v=0;
	int mind=INT_MAX;
	
	for(int i=1;i<n;i++){
		if(deg[i]>deg[u]) u=i;
	}
	if(!deg[u]){
		cout<<"0\n";
		return ;
	}
	deg[u]=0;
	
	for(int i=0;i<n;i++){
		if(i==u) continue;
		if(gcd(a[i],a[u])==1){
			deg[i]--;
			if(mind>deg[i]){
				mind=deg[i];
				v=i;
			}
		}
	}
	
	ans[0]=u;ans[1]=v;
	deg[v]=0;
	
	for(int i=0;i<n;i++){
		if(i==u || i==v) continue;
		if(gcd(a[i],a[v])==1) deg[i]--;
	}
	
	u=0;
	for(int i=1;i<n;i++){
		if(deg[i]>deg[u]){
			u=i;
		}
	}
	if(!deg[u]){
		cout<<"0\n";
		return ;
	}
	
	v=-1;
	for(int i=0;i<n;i++){
		if(i==u || !deg[i]) continue;
		if(gcd(a[i],a[u])==1){
			v=i;
			break;
		}
	}
	assert(v>=0);
	ans[2]=u;ans[3]=v;
	for(int i=0;i<4;i++){
		cout<<ans[i]+1<<" \n"[i==3];
	}
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.tie(nullptr);
	init();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}