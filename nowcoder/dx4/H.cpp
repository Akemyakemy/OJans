// Problem: Highs and Lows
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/H
// Memory Limit: 2048 MB
// Time Limit: 8000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define i128 __int128
#define PII array<int,2>
const int maxn=50,decode=1145141919810ll,base=123123123321ll,muke=283352491887623359ll;
int n,mod,c[maxn],rc[maxn],cnm[maxn],g[maxn],m[maxn],a[maxn],evoke[maxn],C[maxn][maxn],A[maxn][maxn];
inline int tmp(int a,int b){
    (a+=b)>=mod&&(a-=mod);return a;
}
inline int mul(int a,int b){
    return 1ll*a*b%mod;
}
inline int ksm(int a,int b,int mud){
    int res=1;
    while(b){
        if(b&1)res=res*a%mud;a=a*a%mud,b>>=1;
    }
    return res;
}
inline int phi(int m){
    int res=m;
    for(int i=2;i*i<=m;i++){
        if(m%i==0){
            while(m%i==0)m/=i;res-=res/i;
        }
    }
    if(m>1)res-=res/m;return res;
}
int check(int mid){
    static PII tak[1<<20];int top=0;
    int ln=n>>1,rn=n+1>>1;
    for(int mask=0;mask<(1<<ln);mask++){
        int has=0;
        for(int i=0,sum,md;i<n;i++){
            md=(i<n-mid)?g[i]:mod,sum=evoke[i]%md;
            for(int j=0;j<ln;j++){
                if(mask>>j&1){
                    sum=(sum+2ll*A[i][j])%md;
                }
            }
            has=((i128)has*base%muke+sum)%muke;
        }
        tak[++top]=PII{has,mask};
    }
    sort(tak+1,tak+1+top);
    for(int mask=0;mask<(1<<rn);mask++){
        int has=0;
        for(int i=0,sum,md;i<n;i++){
            md=(i<n-mid)?g[i]:mod,sum=0;
            for(int j=0;j<rn;j++){
                if(mask>>j&1){
                    sum=(sum+2ll*A[i][j+ln])%md;
                }
            }
            sum=(md-sum)%md,has=((i128)has*base%muke+sum)%muke;
        }
        int p=lower_bound(tak+1,tak+1+top,PII{has,0})-tak;
        if(p<=top and tak[p][0]==has)return (mask<<ln)+tak[p][1];
    }
    return decode;
}
signed main(){
    ios_base::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    cin>>n>>mod;
    for(int i=0;i<n;i++){
        cin>>a[i],a[i]=tmp(a[i],mod-1);
    }
    C[0][0]=1;
    for(int i=1;i<maxn;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++){
            C[i][j]=tmp(C[i-1][j],C[i-1][j-1]);
        }
    }
    int now=mod,pre=1;
    g[0]=m[0]=1;
    for(int i=1;i<=n;i++)g[i]=g[i-1]*__gcd(i,now),m[i]=mul(m[i-1],i),now/=__gcd(i,now);
    for(int i=0;i<n;i++){
        A[i][i]=1;
        evoke[i]=a[i];
        for(int j=0;j<i;j++){
            evoke[i]=tmp(evoke[i],mod-mul(C[i][j],evoke[j])) ;
            for(int k=0;k<=j;k++){
                A[i][k]=tmp(A[i][k],mod-mul(C[i][j],A[j][k]));
            }
        }
    }
    int l=0,r=n-1,ans=decode;
    while(l<=r){
        int mid=(l+r>>1);
        if(check(mid)!=decode){
            ans=mid,l=mid+1;
        }else{
            r=mid-1;
        }
    }
    if(ans==decode)return cout<<"-1",0;
    int mask=check(ans);
    for(int i=0,md;i<n;i++){
        cnm[i]=evoke[i];
        for(int j=0;j<n;j++){
            if(mask>>j&1)cnm[i]=(cnm[i]+2ll*A[i][j])%mod;
        }
        cnm[i]/=g[i],m[i]/=g[i],md=mod/g[i];
        cnm[i]=cnm[i]*ksm(m[i],phi(md)-1,md)%md;
    }
    for(int i=n-1;i>=0;i--){
        rc[0]=cnm[i];
        for(int j=1;j<=n;j++)rc[j]=0;
        for(int j=0;j<n;j++ )rc[j+1]=c[j];
        for(int j=0;j<n;j++ )rc[j]=tmp(rc[j],mod-mul(c[j],i+1));
        for(int j=0;j<=n;j++)c[j]=rc[j];
    }
    cout<<n-1-ans<<endl;
    for(int i=0;i<n-ans;i++)cout<<c[i]<<" ";
    return 0;
}