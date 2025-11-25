// Problem: 子串的故事（2）
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1004
// Memory Limit: 524288 MB
// Time Limit: 8000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define fo(i,l,r) for(int i=(l);i<=(r);++i)
#define fd(i,l,r) for(int i=(l);i>=(r);--i)
#define fu(i,l,r) for(int i=(l);i<(r);++i)
#define pi pair<int,int>
#define eb emplace_back
#define vi vector<int>
#define vp vector<tp>
#define fi first
#define se second
#define ll long long
using namespace std;
const int N=1e5+7,mo=1e9+7,M=2e7+7;
int n,m,cnt[N<<1],rk[N<<1],p[N<<1],sa[N<<1],h[N],sum;
ll ans,re;
char s[N];
void SA(int n)
{
	int m='z';
	fo(i,1,n) cnt[rk[i]=s[i]]++;
	fo(i,1,m) cnt[i]+=cnt[i-1];
	fo(i,1,n) sa[cnt[s[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int o=0;
		fo(i,n-k+1,n) p[++o]=i;
		fo(i,1,n) if(sa[i]>k) p[++o]=sa[i]-k;
		fo(i,1,m) cnt[i]=0;
		fo(i,1,n) cnt[rk[i]]++;
		fo(i,1,m) cnt[i]+=cnt[i-1];
		fd(i,n,1) sa[cnt[rk[p[i]]]--]=p[i];
		m=0;
		fo(i,1,n) p[i]=rk[i];
		fo(i,1,n) rk[sa[i]]=i==1||p[sa[i]]!=p[sa[i-1]]||p[sa[i]+k]!=p[sa[i-1]+k]?++m:m;
		if(m==n) break;
	}
	int k=0;
	fo(i,1,n)
	{
		if(rk[i]==1) continue;
		if(k) k--;
		while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
		h[rk[i]-1]=k;
	}
}
struct tp{
	int u,v,x,y;
	int ls,rs;
	tp operator+(const tp &t)const{return (tp){(u+t.u)%mo,(v+t.v)%mo,(x+t.x)%mo,(y+t.y)%mo,ls,rs};}
}b[M];
void ad(int l,int r,int &o,int x,tp s)
{
	if(!o) o=++sum;
	b[o]=b[o]+s;
	if(l==r) return;
	int mid=l+r>>1;
	if(x<=mid) ad(l,mid,b[o].ls,x,s);
	else ad(mid+1,r,b[o].rs,x,s);
}
tp qry(int l,int r,int o,int x,int y)
{
	if(!o||(x<=l&&r<=y)) return b[o];
	int mid=l+r>>1;
	if(y<=mid) return qry(l,mid,b[o].ls,x,y);
	if(x>mid) return qry(mid+1,r,b[o].rs,x,y);
	return qry(l,mid,b[o].ls,x,y)+qry(mid+1,r,b[o].rs,x,y);
}
struct node{
	int mn;
	int rt;
}t[N<<2];
tp gt(pi u)
{
	tp z;
	z.u=1;
	z.v=u.se;
	z.x=(1ll*u.fi*(u.fi+1)*(u.fi+u.fi+1)/6-1ll*u.fi*(u.fi+1)/2*u.se)%mo;
	z.y=(1ll*u.fi*u.se-1ll*u.fi*(u.fi+1)/2)%mo;
	z.ls=z.rs=0;
	return z;
}
void bt(int l,int r,int o)
{
	if(l==r){t[o].mn=n;return;}
	int mid=l+r>>1;
	bt(l,mid,o+o);bt(mid+1,r,o+o+1);
	t[o].mn=min(min(t[o+o].mn,t[o+o+1].mn),h[mid]);
}
ll calc2(pi u,pi v)
{
//	if(u.s>v.fi)
//		return ((1ll*v.fi*(v.fi+1)*(v.fi+v.fi+1)/6-1ll*v.fi*(v.fi+1)/2*v.se)%mo*u.u+(1ll*v.fi*v.se-1ll*v.fi*(v.fi+1)/2)%mo*u.v)%mo;
//	return (u.x+u.y*v.se)%mo;
	if(u.fi>v.fi)
	{
		return (1ll*v.fi*(v.fi+1)*(v.fi+v.fi+1)/6-1ll*v.fi*(v.fi+1)/2*v.se+u.se*(1ll*v.fi*v.se-1ll*v.fi*(v.fi+1)/2))%mo;
	}
	return (1ll*u.fi*(u.fi+1)*(u.fi+u.fi+1)/6-1ll*u.fi*(u.fi+1)/2*u.se+(1ll*u.fi*u.se-1ll*u.fi*(u.fi+1)/2)*v.se)%mo;
}
void calc(int o,int x,int y)
{
	tp u=qry(0,n,o,0,x);
	ans=(ans+2*(u.x+1ll*u.y*y))%mo;
	if(x==n) return;
	u=qry(0,n,o,x+1,n);
	ans=(ans+2*((1ll*x*(x+1)*(x+x+1)/6-1ll*x*(x+1)/2*y)%mo*u.u+(1ll*x*y-1ll*x*(x+1)/2)%mo*u.v))%mo;
//	for(tp w:s) ans=(ans+2*calc2(w,{x,y}))%mo;
}
pi upd(int l,int r,int o,int x,int y)
{
	if(l==r)
	{
		calc(t[o].rt,y,y+1);
//		ad(0,n,t[o].R,y,gt({y,y+1}));
//		ad(0,n,t[o].L,y,gt({y,y+1}));
		return {y,y};
	}
	int mid=l+r>>1;
	pi w;
	if(x<=mid)
	{
		w=upd(l,mid,o+o,x,y);
		ad(0,n,t[o+o].rt,w.se,gt({w.se,y+1}));
		w.se=min(w.se,h[mid]);
		calc(t[o+o+1].rt,w.se,y+1);
		w.se=min(w.se,t[o+o+1].mn);
	}
	else
	{
		w=upd(mid+1,r,o+o+1,x,y);
		ad(0,n,t[o+o+1].rt,w.fi,gt({w.fi,y+1}));
		w.fi=min(w.fi,h[mid]);
		calc(t[o+o].rt,w.fi,y+1);
		w.fi=min(w.fi,t[o+o].mn);
	}
//	printf("  %d %d\n",w.fi,w.se);
	return w;
}
void clr(int m)
{
	ans=0;re=0;
	fo(i,0,n<<2) t[i].rt=0,t[i].mn=0;
	fo(i,0,m) cnt[i]=rk[i]=sa[i]=p[i]=h[i]=0;
	fo(o,0,sum) b[o].x=b[o].y=b[o].u=b[o].v=b[o].ls=b[o].rs=0;
	sum=0;
}
void work()
{
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	if(n==1)
	{
		fo(i,1,m) scanf("%*d%*d"),printf("%lld\n",1ll*i*(i-1)/2%mo);
		return;
	}
	SA(n);
//	fo(i,1,n-1) printf("%d ",h[i]);
	bt(1,n,1);
	fo(i,1,m)
	{
		int l,r;scanf("%d%d",&l,&r);r=r-l+1;
		upd(1,n,1,rk[l],r);
		ans=(ans+calc2({r,r+1},{r,r+1}))%mo;
//		printf("  %lld\n",calc2({r,r+1},{r,r+1}))%mo;
		re=(re+1ll*r*(r+1)/2)%mo;
		printf("%lld\n",((ans-re)*(mo+1>>1)%mo+mo)%mo);
	}
	clr(max(n+n,130));
}
int main()
{
	int T;scanf("%d",&T);
	while(T--) work();
}