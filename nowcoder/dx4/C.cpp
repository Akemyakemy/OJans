// Problem: Computational Geometry Problem
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/C
// Memory Limit: 2048 MB
// Time Limit: 10000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
int powdv(int x,int y=mod-2){
    int ans=1;
    while(y){
        if(y&1)ans=1ll*ans*x%mod;
        y>>=1,x=1ll*x*x%mod;
    }
    return ans;
}
int C(int n,int m){
    int di=1,id=1;
    for(int i=1;i<=m;++i)di=1ll*di*(n-i+1)%mod,id=1ll*id*i%mod;
    return 1ll*di*powdv(id)%mod;
}
int main(){
    int n,s;long long k;
    scanf("%d%d%lld",&n,&s,&k);
    long long z=1ll*(n-1)*s-k;
    if(z<0||s-1-z<0){
        puts("0");return 0;
    }
    int ans=C(s,s-1-z),a1=1,a2=1;
    for(int i=1;i<=z;++i){
        a1=1ll*a1*((1ll*(n-1)*s-i+1)%mod)%mod;
        a2=1ll*a2*i%mod;
    }
    for (int i=1;i<=s-1;++i)ans=1ll*ans*i%mod;
    ans=1ll*ans*a1%mod*powdv(a2)%mod;
    printf("%d\n",ans);
    return 0;
}