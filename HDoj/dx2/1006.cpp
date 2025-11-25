// Problem: 半
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1006
// Memory Limit: 512000 MB
// Time Limit: 2000 ms
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
using namespace std;
const int N=1e6+7;
int n,b[N],c[N],f[N],g[N],ans[N];
void upd(int x,int y){while(x<=n)f[x]+=y,x+=x&-x;}
int qry(int x){int s=0;while(x)s+=f[x],x-=x&-x;return s;}
void work()
{
	scanf("%d",&n);
	fd(i,n,1) scanf("%d",&g[i]);
	fd(i,n,1) scanf("%d",&c[i]),b[c[i]]=i;
	fo(i,1,n) f[i]=0;
	fo(i,1,n)
	{
		upd(b[g[i]],1);
		ans[g[i]]=n-qry(b[g[i]]);
	}
	fo(i,1,n) printf("%d ",ans[i]);
	printf("\n");
}
int main()
{
	int T;scanf("%d",&T);
	while(T--) work();
}