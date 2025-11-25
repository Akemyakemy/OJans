// Problem: 苹果树
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1009
// Memory Limit: 512000 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ci const int
#define ll long long
using namespace std;
char buf[1<<20],*p1=buf,*p2=buf;
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
int read(){int res(0);char ch(getchar());while(ch<48||ch>57)ch=getchar();while(ch>=48&&ch<=57)res=(res<<1)+(res<<3)+(ch^48),ch=getchar();return res;}
void out(ci x){
	if(x>9)out(x/10);
	putchar(x%10+48);
}
ci N=4e5+5;
int n,q,ad[N],a[N],dfn[N],seg[N],dfstime,siz[N],son[N],f[N],top[N],dep[N];
vector<int>g[N];
void Init(){
	for(int i=1;i<=n;++i){
		ad[i]=a[i]=dfn[i]=seg[i]=siz[i]=son[i]=f[i]=top[i]=dep[i]=0;
		g[i].clear();
	}
	dfstime=0;
}
void dfs(ci x){
	siz[x]=1,dep[x]=dep[f[x]]+1;
	for(int y:g[x])if(y!=f[x])f[y]=x,dfs(y),siz[x]+=siz[y],son[x]=siz[y]>siz[son[x]]?y:son[x];
}
void DFS(ci x){
	seg[dfn[x]=++dfstime]=x;
	if(!top[x])top[x]=x;
	if(son[x])top[son[x]]=top[x],DFS(son[x]);
	for(int y:g[x])if(!top[y])DFS(y);
}
ci M=N<<2;
#define ls k<<1
#define rs k<<1|1
struct Tree{
	int l[M],r[M],mx[M];
	void build(ci k,ci L,ci R){
		l[k]=L,r[k]=R,mx[k]=0;
		if(L==R){
			mx[k]=a[seg[L]];
			return;
		}
		ci mid=L+R>>1;
		build(ls,L,mid),build(rs,mid+1,R),mx[k]=max(mx[ls],mx[rs]);
	}
	void cov(ci k,ci p,ci v){
		if(l[k]==r[k]){
			mx[k]+=v;
			return;
		}
		cov(r[ls]>=p?ls:rs,p,v),mx[k]=max(mx[ls],mx[rs]);
	}
	int qry(ci k,ci L,ci R){
		if(L>r[k]||R<l[k])return 0;
		if(L<=l[k]&&r[k]<=R)return mx[k];
		return max(qry(ls,L,R),qry(rs,L,R));
	}
}T;
int gt(ci x){
	return ad[f[x]]+T.qry(1,dfn[x],dfn[x]);
}
int calc(int x,int y){
	int ans=T.qry(1,dfn[x],dfn[y]);
	if(x==top[x])ans=max(ans,gt(x));
	return ans;
}
void Work(){
	n=read(),q=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1,x,y;i<n;++i)
		x=read(),y=read(),
		g[x].push_back(y),
		g[y].push_back(x);
	dfs(1),DFS(1),T.build(1,1,n);
	while(q--){
		ci op=read();
		if(op==1){
			int x=read(),y=read(),fx=top[x],fy=top[y],ans=0;
			while(fx!=fy){
				if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
				ans=max(ans,calc(fx,x)),x=f[fx],fx=top[x];
			}
			if(dep[x]>dep[y])swap(x,y);
			ans=max(ans,calc(x,y));
			out(ans),putchar(10);
		}
		else{
			ci x=read(),v=read();
			ad[x]+=v;
			if(f[x])T.cov(1,dfn[f[x]],v);
			if(son[x])T.cov(1,dfn[son[x]],v);
		}
	}
}
int main(){
	for(int T=read();T;--T)Work(),Init();
	return 0;
}