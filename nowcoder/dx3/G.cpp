// Problem: Gellyfish and Priority Queue
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108300/G
// Memory Limit: 2048 MB
// Time Limit: 10000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<iostream>
#include<cstdio>
#define mod 998244353
using namespace std;
int n,m;
int now=1,lst;
int o[505],l[505],r[505];
int f[2][505][505][2],ans,q;
inline void add(int &x,int y){
    if((x+=y)>=mod) x-=mod;
    return;
}
inline int qp(int x,int y=mod-2){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod; y>>=1;
    }
    return res;
}
inline int sum(int l,int r){
    if(l>r) return 0;
    return 1ll*(l+r)*(r-l+1)/2%mod;
}
inline int cnt(int l,int r){
    if(l>r) return 0;
    return r-l+1;
}
void solve(){
    scanf("%d%d",&n,&m); q=1; ans=0;
    for(int j=0;j<=m;j+=1){
        f[now][0][j][j==0]=1; f[now][0][j][j!=0]=0;
    }
    for(int k=1;k<=n;k+=1){
        scanf("%d",&o[k]);
        if(o[k]==1){
            scanf("%d%d",&l[k],&r[k]);
            q=1ll*q*(r[k]-l[k]+1)%mod;
        }
    }
    for(int k=n,s=0;k>=1;k-=1){
        swap(now,lst); s+=o[k]-1;
        if(o[k]==1){
            for(int i=0;i<=s;i+=1){
                for(int j=0;j<=m;j+=1){
                    for(int t=0,res;t<2;t+=1){
                        if(!(res=f[lst][i][j][t])){
                            f[now][i][j][t]=0; continue;
                        }
                        f[now][i][j][t]=1ll*res*sum(max(l[k],j+t),r[k])%mod;
                        if(i){
                            add(f[now][i-1][j][t],1ll*res*cnt(l[k],min(r[k],j-1))%mod);
                            if(l[k]<=j&&j<=r[k]) add(f[now][i-1][j][1],res);
                        }
                    }
                }
            }
        }
        else{
            for(int i=2;i<=s;i+=1){
                for(int j=0;j<=m;j+=1){
                    for(int t=0;t<2;t+=1) f[now][i][j][t]=f[lst][i-1][j][t];
                }
            }
            for(int j=0;j<=m;j+=1){
                if(j) add(f[now][1][j][0],f[now][1][j-1][0]);
                f[now][1][j+1][0]=f[now][1][j][1]=f[lst][0][j][1];
                f[now][0][j][0]=f[now][0][j][1]=0;
            }
        }
    }
    for(int j=0;j<=m;j+=1) add(ans,f[now][0][j][1]);
    ans=1ll*ans*qp(q)%mod;
    printf("%d\n",ans);
    return;
}
int main(){
    int t; scanf("%d",&t);
    while(t--) solve();
    return 0;
}