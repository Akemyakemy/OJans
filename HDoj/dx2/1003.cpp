// Problem: 图上的数
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1003
// Memory Limit: 512000 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define fo(i,l,r) for(int i=(l);i<=(r);++i)
#define fd(i,l,r) for(int i=(l);i>=(r);--i)
#define fu(i,l,r) for(int i=(l);i<(r);++i)
#define pi pair<int,int>
#define eb emplace_back
#define vi vector<int>
#define fi first
#define se second
#define ll long long
#define ld long double
using namespace std;
const int N=400007,B=60,mo=998244353;
int n,m,vis[N];
ll e2[N],s;
ld mx,e[N];
ll ksm(ll x,int y){ll s=1;for(;y;y>>=1,x=x*x%mo)if(y&1)s=s*x%mo;return s;}
int tot,to[N],head[N],nx[N],w[N];
void add(int x,int y,int z){to[++tot]=y;nx[tot]=head[x];head[x]=tot;w[tot]=z;}
void Max(int &x,int y){if(x<y)x=y;}
struct node{
	int s,l,g[B+1];
	node operator+(const int &t)const{
		node z;
		z.s=s+1;
		z.l=t?s+1:(l>0?l+1:-1);
		fo(i,0,B) z.g[i]=0;
		if(t) z.g[0]=t;
		if(l>0)
		{
			fo(i,0,B) if(l+1-i+B>=z.l) Max(z.g[z.l-(l+1-i)],g[i]+t);
		}
		return z;
	}
	node operator+(const node &t)const{
		node z;
		z.s=max(s,t.s);
		z.l=max(l,t.l);
		fo(i,0,B) z.g[i]=0;
		if(l>0)
		{
			fo(i,0,B) if(l-i+B>=z.l) Max(z.g[z.l-(l-i)],g[i]);
		}
		if(t.l>0)
		{
			fo(i,0,B) if(t.l-i+B>=z.l) Max(z.g[z.l-(t.l-i)],t.g[i]);
		}
		return z;
	}
}f[N],ans;
node dfs(int x)
{
	if(vis[x]) return f[x];
	vis[x]=1;
	f[x].s=0;
	f[x].l=-1;
	for(int i=head[x];i;i=nx[i]) f[x]=f[x]+(dfs(to[i])+w[i]);
	return f[x];
}
void work()
{
	scanf("%d%d",&n,&m);
	fo(i,1,n) head[i]=0,vis[i]=0;
	tot=0;
	fo(i,1,m)
	{
		int x,y,z;scanf("%d%d%d",&x,&y,&z);
		add(y,x,z);
	}
	ans.s=0;ans.l=-1;
	fo(i,1,n)
	{
		ans=ans+dfs(i);
	}
//	printf("  %d %d\n",ans.s,ans.l);
//	fo(i,0,B) printf("%d ",ans.g[i]); printf("\n");
	if(ans.l<0){printf("0\n");return;}
	mx=0;s=0;
	fo(i,0,min(B,ans.l-1))
	{
		int w=ans.l-i;
		ld o=e[w]/w*ans.g[i];
		if(o>mx) mx=o,s=e2[w]*ksm(w,mo-2)%mo*ans.g[i]%mo;
	}
//	printf("%lld %lld\n",s,33*ksm(2,mo-2)%mo);
	printf("%lld\n",s*ksm(10000,mo-2)%mo);
}
int main()
{
	fo(i,1,N-1) e[i]=e[i-1]*2+1;
	fo(i,1,N-1) e2[i]=(e2[i-1]*2+1)%mo;
	int T;scanf("%d",&T);
	while(T--) work();
}