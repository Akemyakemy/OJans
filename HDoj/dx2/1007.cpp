// Problem: 计数
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1007
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
const int N=5007,mo=1e9+7;
int n,R,a[N];
ll f[N],C[N][N];
ll jc[N],jinv[N],iv[N];
ll ksm(ll x,int y){ll s=1;for(;y;y>>=1,x=x*x%mo)if(y&1)s=s*x%mo;return s;}
void init(int n)
{
	jc[0]=1;fo(i,1,n) jc[i]=jc[i-1]*i%mo;
	jinv[n]=ksm(jc[n],mo-2);fd(i,n,1) jinv[i-1]=jinv[i]*i%mo;
	fo(i,1,n) iv[i]=jinv[i]*jc[i-1]%mo;
}
void work()
{
	scanf("%d%d",&n,&R);
	fo(i,1,n) scanf("%d",&a[i]);
	fd(i,n-1,1) a[i]=max(a[i],a[i+1]);
	f[0]=1;
	fo(i,1,n) f[i]=0;
	fo(i,1,n)
	{
		int w=R-a[i]+1;
		C[i][0]=1;
		fo(j,1,n) C[i][j]=C[i][j-1]*(w-j+1)%mo*iv[j]%mo;
	}
	fo(i,1,n)
	{
		fo(j,i,n)
		{
			f[j]=(f[j]+(((j-i)&1)?mo-f[i-1]:f[i-1])*C[i][j-i+1])%mo;
		}
	}
	printf("%lld\n",f[n]);
}
int main()
{
	init(N-1);
	int T;scanf("%d",&T);
	while(T--) work();
}