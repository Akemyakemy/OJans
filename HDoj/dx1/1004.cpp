// Problem: 串串
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1004
// Memory Limit: 524288 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define LL long long
#define LLL __int128
#define uint unsigned
#define ldb long double
#define uLL unsigned long long
using namespace std;
const int N=2e6+5,M=55;
int n,m;
char S[N];
int Q[N][M];
vector<pair<int,int>>vec[N];
int sa[N],rk[N],height[N],fd[N];
template<class T>inline void SA(T* s,int n){
	static int cnt[N],t1[N],t2[N];
	int *x=t1,*y=t2,m=*max_element(s+1,s+n+1);
	fill(cnt,cnt+m+1,0);
	for(int i=1;i<=n;++i)++cnt[x[i]=s[i]];
	partial_sum(cnt,cnt+m+1,cnt);
	for(int i=n;i>=1;--i)sa[cnt[x[i]]--]=i;
	for(int k=1;;k*=2){
		fill(cnt,cnt+m+1,0);
		for(int i=1;i<=n;++i)++cnt[x[i]];
		partial_sum(cnt,cnt+m+1,cnt),m=0;
		for(int i=n-k+1;i<=n;++i)y[++m]=i;
		for(int i=1;i<=n;++i)if(sa[i]>k)y[++m]=sa[i]-k;
		for(int i=n;i>=1;--i)sa[cnt[x[y[i]]]--]=y[i];
		m=y[sa[1]]=1;
		for(int i=2;i<=n;++i)
			y[sa[i]]=(m+=!(max(sa[i]+k,sa[i-1]+k)<=n&&x[sa[i]]==x[sa[i-1]]&&x[sa[i]+k]==x[sa[i-1]+k]));
		if(m>=n)break;
		swap(x,y);
	}
	for(int i=1;i<=n;++i)rk[sa[i]]=i;
	for(int i=1,j=0;i<=n;++i){
		j=max(j-1,0);
		if(rk[i]==1)continue;
		int k=sa[rk[i]-1];
		while(i+j<=n&&j+k<=n&&s[i+j]==s[j+k])++j;
		height[rk[i]]=j;
	}
}
inline int find(int x){
	return x==fd[x]?x:fd[x]=find(fd[x]);
}
inline void MAIN(){
	cin>>n,m=0;
	LL ans=0;
	for(int i=0;i<n;++i){
		string s;cin>>s;
		for(int j=0;j<s.length();++j)S[++m]=s[j],fill(Q[m],Q[m]+n,0),Q[m][i]=j+1;
		S[++m]=i+1,fill(Q[m],Q[m]+n,0);
	}
	SA(S,m);
	iota(fd+1,fd+m+1,1);
	for(int i=2;i<=m;++i)vec[height[i]].emplace_back(sa[i-1],sa[i]);
	for(int i=m;i>=1;--i){
		for(auto [u,v]:vec[i]){
			u=find(u),v=find(v);
			int s=0,r=0;
			for(int c=0;c<n;++c)
				Q[u][c]=max(Q[u][c],Q[v][c]),s+=Q[u][c],r+=Q[u][c]>0;
			if(r>1)ans=max(ans,1LL*s*i);
			fd[v]=u;
		}
		vec[i].clear();
	}
	cout<<ans<<'\n';
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int t=1;cin>>t;while(t--)MAIN();
	return 0;
}
/*
*/