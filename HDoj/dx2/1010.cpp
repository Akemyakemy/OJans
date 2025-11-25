// Problem: 子序列
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1010
// Memory Limit: 512000 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pr;
typedef vector<LL> vi;
inline LL rd(){
	LL x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
const LL p=998244353,N=1000005;
LL qp(LL x,LL y){LL z=1;for(;y;y>>=1,x=x*x%p)if(y&1)z=z*x%p;return z;}
LL n,m,T,k,c[N],sm[N],nw[N];pr a[N];vector<pr>vc;vi ve[N];
struct nd{
	LL x;
	bool operator<(const nd&b)const{
		if(x==b.x)return 0;
		if((nw[x]+1)*(nw[b.x]+1-a[b.x].S)!=(nw[b.x]+1)*(nw[x]+1-a[x].S))
		return (nw[x]+1)*(nw[b.x]+1-a[b.x].S)<(nw[b.x]+1)*(nw[x]+1-a[x].S);
		if(x<b.x)return a[x+1].F<a[x].F;return a[b.x+1].F>a[b.x].F;
	}
};
priority_queue<nd>q;
int main(){
	for(T=rd();T--;){
		m=rd();k=rd();n=0;
		for(LL i=1;i<=m;++i)sm[i]=0,ve[i].clear();
		for(LL i=1,o;i<=k;++i){
			o=rd();++sm[o];
			if(!n||a[n].F!=o)a[++n]={o,1};
			else ++a[n].S;
		}
		for(LL i=1;i<=m;++i)c[i]=rd();LL fl=1;
		for(LL i=1;i<=m;++i)if(c[i]<sm[i])fl=0;
		if(!fl){
			vc.clear();
			for(LL i=1;i<=m;++i)if(c[i])vc.push_back({i,c[i]});
			printf("%lld\n",vc.size());
			for(auto i:vc)printf("%lld %lld\n",i.S,i.F);
			continue;
		}
		for(LL i=1;i<=n;++i)nw[i]=a[i].S,ve[a[i].F].push_back(i);
		for(LL i=1;i<=m;++i)if(sm[i]){
			while(q.size())q.pop();
			for(auto j:ve[i])q.push({j});
			for(LL j=sm[i];j<c[i];++j){nd x=q.top();q.pop();++nw[x.x];q.push(x);}
		}
		vc.clear();
		for(LL i=1;i<=m;++i)if(c[i]&&!sm[i])vc.push_back({i,c[i]});LL po=0;
		printf("%lld\n",n+vc.size());
		for(LL i=1;i<=n;++i){
			while(po<vc.size()&&vc[po].F<a[i].F)printf("%lld %lld\n",vc[po].S,vc[po].F),++po;
			printf("%lld %lld\n",nw[i],a[i].F);
		}
		while(po<vc.size())printf("%lld %lld\n",vc[po].S,vc[po].F),++po;
	}
	return 0;
}