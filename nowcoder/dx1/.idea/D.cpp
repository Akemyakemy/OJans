// Problem: LCM Challenge
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108298/D
// Memory Limit: 1024 MB
// Time Limit: 16000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#pragma GCC optimize ("O2")
#define LL long long
#define id(x)(x<=SQRT?idx1[x]:idx2[n/(x)])
using namespace std;
bool AAAAA;
LL SQRT,vis[200010],ss[200010];
int cnt,idx1[200010],idx2[200010];
__int128 n,mod=1,Barrett=((__int128)1<<80)/mod;
inline LL add(LL x,LL y){return x+y<mod?x+y:x+y-mod;}
inline LL sub(LL x,LL y){return x<y?x-y+mod:x-y;}
inline LL mul(__int128 x,LL y){x=x*y;x-=mod*((Barrett*x)>>80);return x<mod?x:x-mod;}
LL ksm(__int128 B,LL K,__int128 A=1)
{
    for(;K;K>>=1,B=B*B%mod)
    if(K&1)A=A*B%mod;
    return A;
}
LL w[200010],prod[1000010],prodi[1000010],mUl=1,g1[200010],g1i[200010],g2[200010],sums[200010];
void xxs(LL N)
{
    ss[0]=0;prod[0]=1;prodi[0]=1;
    for(LL i=2;i<=N;i++){
        if(!vis[i]){
            ss[++ss[0]]=i;
            prod[ss[0]]=(__int128)prod[ss[0]-1]*i%mod;
            prodi[ss[0]]=ksm(prod[ss[0]],mod-2);
            sums[ss[0]]=ss[0];
        }
        for(int j=1;i*ss[j]<=N;j++){
            vis[i*ss[j]]=1;
            if(i%ss[j]==0)break;
        }
    }
}
bool BBBBB;
int tot=1,rev[270000];
LL MULY[270000],MULX[270000],MULZ[270000],wk[3][270000],wki[3][270000];
LL trans_f[270000],trans_g[270000],fact_f[270000],fact_g[270000],fact[10000010],inv[10000010],MTTX[270000],MTTY[270000],ansX[270000],ansY[270000],ansZ[270000];
const long double Pi=3.1415926535897932384626;
struct Complex
{
    long double x,y;
    Complex operator+(const Complex&n2){return{x+n2.x,y+n2.y};}
    Complex operator-(const Complex&n2){return{x-n2.x,y-n2.y};}
    Complex operator*(const Complex&n2){return{x*n2.x-y*n2.y,x*n2.y+y*n2.x};}
}A[270000],B[270000],C[270000],D[270000],I={0,1};
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void FFT(Complex*c,int inv)
{
    for(int i=0;i<tot;i++)
        if(i<rev[i])swap(c[i],c[rev[i]]);
    for(int mid=1;mid<tot;mid<<=1){
        Complex w1={cos(Pi/mid),inv*sin(Pi/mid)};
        for(int i=0;i<tot;i+=mid*2){
            Complex wk={1,0};
            for(int j=0;j<mid;j++,wk=wk*w1){
                Complex x=c[i+j],y=wk*c[i+j+mid];
                c[i+j]=x+y;
                c[i+j+mid]=x-y;
            }
        }
    }
}
void MTT(LL*a,LL*b)
{
    for(int i=0;i<tot;i++){
        a[i]%=mod;b[i]%=mod;
        A[i].x=a[i]>>15;A[i].y=a[i]&0x7fff;
        C[i].x=b[i]>>15;C[i].y=b[i]&0x7fff;
    }
    FFT(A,1);FFT(C,1);
    B[0]=A[0];B[0].y=-B[0].y;
    D[0]=C[0];D[0].y=-D[0].y;
    for(int i=1;i<tot;i++){
        B[i]=A[tot-i];B[i].y=-B[i].y;
        D[i]=C[tot-i];D[i].y=-D[i].y;
    }
    for(int i=0;i<tot;i++){
        Complex x=A[i],y=B[i];A[i]=x+y;A[i].x/=2;A[i].y/=2;
        B[i]=y-x;B[i].x/=2;B[i].y/=2;B[i]=B[i]*I;
        x=C[i];y=D[i];C[i]=x+y;C[i].x/=2;C[i].y/=2;
        D[i]=y-x;D[i].x/=2;D[i].y/=2;D[i]=D[i]*I;
 
        Complex xx=C[i],yy=D[i];
        x=A[i];y=B[i];
        C[i]=x*xx+I*y*xx;
        D[i]=x*yy+I*y*yy;
    }
    FFT(C,-1);FFT(D,-1);
    for(int i=0;i<tot;i++)
        C[i].x/=tot,C[i].y/=tot,D[i].x/=tot,D[i].y/=tot;
    for(int i=0;i<tot;i++)
        a[i]=((((LL)(C[i].x+0.5)%mod)<<30)%mod+(((LL)(C[i].y+0.5)%mod)<<15)%mod+(((LL)(D[i].x+0.5)%mod)<<15)%mod+(((LL)(D[i].y+0.5)))%mod)%mod;
}
void calc(LL a[],LL b[],int N,LL M)
{
    int bit=0;while((1<<bit)<=N+N)bit++,tot=1<<bit;
    for(int i=1;i<tot;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    for(int i=0;i<tot;i++)trans_f[i]=a[i];
    for(int i=0;i<tot;i++)
    if(N>=i){
        trans_f[i]=mul(mul(trans_f[i],inv[i]),inv[N-i]);
        if((N-i)%2)trans_f[i]=(mod-trans_f[i])%mod;
    }else trans_f[i]=0;
    for(int i=0;i<tot;i++)
        MULX[i]=MULY[i]=trans_g[i]=0;
    MULY[0]=M-N;
    for(int i=1;i<=N*2;i++)
        MULY[i]=mul(MULY[i-1],M-N+i);
    trans_g[N*2]=ksm(MULY[N*2],mod-2);
    for(int i=N*2-1;i>=0;i--){
        trans_g[i]=mul(trans_g[i+1],M-N+i+1);
        MULY[i+1]=mul(MULY[i],trans_g[i+1]);
        trans_g[i+1]=MULY[i+1];
    }
    MULY[0]=trans_g[0];
    for(int i=0;i<=N;i++)MULX[i]=trans_f[i];
    MTT(MULX,MULY);
    LL temp=1;
    for(int j=0;j<=N;j++)
        temp=mul(temp,M-N+j);
    for(int i=0;i<=N;i++){
        b[i]=mul(temp,MULX[N+i]);
        temp=mul(temp,mul(trans_g[i],M+i+1));
    }
}
LL factK=0;
void preparefact()
{
    fact[0]=1;
    for(int i=1;i<=10000000;i++)
        fact[i]=mul(fact[i-1],i);
    inv[10000000]=ksm(fact[10000000],mod-2);
    for(int i=10000000-1;i>=0;i--)
        inv[i]=mul(inv[i+1],(i+1));
    factK=131072;
    memset(fact_f,0,sizeof(LL)*(factK+5));
    fact_f[0]=1;fact_f[1]=factK+1;
    for(int d=2;d<factK;d*=2){
        calc(fact_f,fact_g,d-1,d);
        for(int j=0;j<d;j++)fact_f[j|d]=fact_g[j];
        calc(fact_f,fact_g,d-1,add(d,mul(d,ksm(factK,mod-2))));
        for(int j=0;j<d;j++)fact_f[j|d]=mul(fact_g[j],fact_f[j|d]);
        calc(fact_f,fact_g,d-1,mul(d,ksm(factK,mod-2)));
        for(int j=0;j<d;j++)fact_f[j]=mul(fact_g[j],fact_f[j]);
        for(LL j=0;j<d*2;j++)
            fact_f[j]=mul(((j<<17)|d),fact_f[j]);
    }
}
LL factorial(LL N)
{
    if(N<=10000000)return fact[N];
    LL temp=fact_f[N>>17];
    for(int j=0;j<(N&131071);j++)
        temp=mul(temp,(N-j));
    return temp;
}
LL pw[2][200010],pwi[2][200010],powtot;
signed main()
{
    long long nn,modmod;
    cin>>nn>>modmod;
    n=nn;mod=modmod;
    Barrett=((__int128)1<<80)/mod;
    SQRT=sqrt((long long)n);
    xxs(SQRT);
    for(int i=1;ss[i]*ss[i]<=n&&i<=ss[0];i++){
        __int128 temp=1,temp2=ss[i];
        while(temp2*ss[i]<=n)temp*=ss[i],temp2*=ss[i];
        mUl=(__int128)mUl*(temp%mod)%mod;
    }
    for(LL L=1,R;L<=n;L=R+1){
        R=n/(n/L);w[++cnt]=n/L;
        if(n/L<=SQRT)idx1[n/L]=cnt;
        else idx2[n/(n/L)]=cnt;
    }
    preparefact();
    for(int i=131071;i>0;i--)
        fact_f[i]=mul((LL)i<<17,fact_f[i-1]);
    fact_f[0]=1;
    for(int i=1;i<=131071;i++)
        fact_f[i]=mul(fact_f[i],fact_f[i-1]);
    for(int i=1;i<=cnt;i++){
        g1[i]=factorial(w[i]);
        g1i[i]=ksm(g1[i],mod-2);
        g2[i]=w[i]-1;
    }
    for(int j=1;j<=ss[0]&&ss[j]*ss[j]<=n;j++){
        LL powtot=sqrt(modmod/ss[j]);
        while(powtot*powtot<modmod/ss[j])powtot++;
        pw[0][0]=1;pwi[0][0]=1;
        pw[0][1]=ss[j];pwi[0][1]=ksm(ss[j],mod-2);
        for(int i=2;i<=powtot;i++){
            pw[0][i]=mul(pw[0][i-1],pw[0][1]);
            pwi[0][i]=mul(pwi[0][i-1],pwi[0][1]);
        }
        pw[1][0]=1;pwi[1][0]=1;
        pw[1][1]=pw[0][powtot];pwi[1][1]=pwi[0][powtot];
        for(int i=2;i<powtot;i++){
            pw[1][i]=mul(pw[1][i-1],pw[1][1]);
            pwi[1][i]=mul(pwi[1][i-1],pwi[1][1]);
        }
        for(int i=1;i<=cnt&&w[i]>=ss[j]*ss[j];i++){
            g2[i]-=g2[id(w[i]/ss[j])]-sums[j-1];
            g1[i]=mul(mul(mul(mul(pwi[0][(g2[id(w[i]/ss[j])]-sums[j-1])%powtot],pwi[1][(g2[id(w[i]/ss[j])]-sums[j-1])/powtot]),
                prod[j-1]),g1[i]),
                g1i[id(w[i]/ss[j])]);
            g1i[i]=mul(mul(mul(mul(pw[0][(g2[id(w[i]/ss[j])]-sums[j-1])%powtot],pw[1][(g2[id(w[i]/ss[j])]-sums[j-1])/powtot]),
                prodi[j-1]),g1i[i]),
                g1[id(w[i]/ss[j])]);
        }
    }
    cout<<(long long)((__int128)g1[id(n)]*mUl%mod)<<endl;
}