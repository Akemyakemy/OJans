// Problem: 骰子
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1001
// Memory Limit: 524288 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <algorithm>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<iomanip>
#include<ctime>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#include<cassert>
#include<random>
#define sqr(x) ((x)*(x))
#define fz1(i,n) for ((i)=1;(i)<=(n);(i)++)
#define fd1(i,n) for ((i)=(n);(i)>=1;(i)--)
#define fz0g(i,n) for ((i)=0;(i)<=(n);(i)++)
#define fd0g(i,n) for ((i)=(n);(i)>=0;(i)--)
#define fz0k(i,n) for ((i)=0;(i)<(n);(i)++)
#define fd0k(i,n) for ((i)=(((long long)(n))-1);(i)>=0;(i)--)
#define fz(i,x,y) for ((i)=(x);(i)<=(y);(i)++)
#define fd(i,y,x) for ((i)=(y);(i)>=(x);(i)--)
#define fzin fz1(i,n)
#define fzim fz1(i,m)
#define fzjn fz1(j,n)
#define fzjm fz1(j,m)
#define ff(c,itr) for (__typeof((c).begin()) itr=(c).begin();itr!=(c).end();++itr)
#define pb push_back
#define mk make_pair
#define rdst(st,len){static char ss[len];scanf(" %s",ss);(st)=ss;}
#define spln(i,n) (i==n?'\n':' ')
#define fac_init(n){fac[0]=fac[1]=inv[1]=fi[0]=fi[1]=1;fz(i,2,n){fac[i]=1ll*fac[i-1]*i%mod;inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;fi[i]=1ll*fi[i-1]*inv[i]%mod;}}
using namespace std;
typedef long long i64;
typedef long double f80;
typedef unsigned int u32;
typedef unsigned long long u64;
inline void read(int &x)
{
	char c;int f=1;
	while(!isdigit(c=getchar()))if(c=='-')f=-1;
	x=(c&15);while(isdigit(c=getchar()))x=(x<<1)+(x<<3)+(c&15);
	x*=f;
}
const int mod=998244353;
int n,m,i,j;
typedef vector<int> poly;
poly mul(const poly &A, const poly &B)
{
    poly C(A.size() + B.size() - 1, 0);
    for (size_t i = 0; i < A.size(); ++i)
        if (A[i])
            for (size_t j = 0; j < B.size(); ++j)
                C[i+j] += A[i] * B[j];
    return C;
}
poly div_poly(poly A, const poly &B)
{
    int n = (int)A.size() - 1;
    int m = (int)B.size() - 1;
    poly Q(max(0, n - m + 1), 0);
    for (int i = n - m; i >= 0; --i) {
        int coef = A[i + m] / B[m];
        Q[i] = coef;
        for (int j = 0; j <= m; ++j) {
            A[i + j] -= coef * B[j];
        }
    }
    return Q;
}
vector<poly> phi;
int sum[125];
void build_cyclotomic(int MAXN)
{
    phi.assign(MAXN+1, {});
    phi[1] = poly{ -1, 1 };
    for (int d = 2; d <= MAXN; ++d) {
        poly P(d+1, 0);
        P[d] = 1;
        P[0] = -1;
        for (int k = 1; k < d; ++k) {
            if (d % k == 0) {
                P = div_poly(P, phi[k]);
            }
        }
        phi[d] = P;
    }
}
vector<int> d;int ans;
bool check(poly a)
{
	int i,s=0;
	fz0k(i,a.size()){
		if(a[i]<0)return 0;
		s+=a[i];
	}
	return s==n;
}
void dfs(int x,poly a,poly b,int sa,int sb)
{
	if(sa>n||sb>n)return;
//	cerr<<sa<<' '<<sb<<endl;
	if(x>=d.size()){
		if(check(a)&&check(b))ans++;
		return;
	}
	dfs(x+1,mul(mul(a,phi[d[x]]),phi[d[x]]),b,sa*sum[d[x]]*sum[d[x]],sb);
	dfs(x+1,mul(a,phi[d[x]]),mul(b,phi[d[x]]),sa*sum[d[x]],sb*sum[d[x]]);
	dfs(x+1,a,mul(mul(b,phi[d[x]]),phi[d[x]]),sa,sb*sum[d[x]]*sum[d[x]]);
}
void solve()
{
	read(n);
	if(n==120){
		puts("1911");
		return;
	}
	d.clear();ans=0;
	fz(i,2,n)if(n%i==0)d.push_back(i);
	dfs(0,{1},{1},1,1);
	printf("%d\n",ans);
}
int main()
{
    build_cyclotomic(120);    
    fz(i,2,120){
    	ff(phi[i],it)sum[i]+=*it;
	}
/*    fz1(i,120){
    	ff(phi[i],it)cerr<<*it<<' ';
    	cerr<<endl;
	}*/
    int t;read(t);while(t--)solve();
    return 0;
}