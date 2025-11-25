// Problem: 树上LCM
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1007
// Memory Limit: 524288 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
int n,p[20],c[20],m;
vector<int>g[100100];
#define pb push_back
int S,fh,st[101000];
bool jd[100100];
#define ll long long
ll ans;
int sz[101000];
ll Cb(ll x){return x*(x+1)/2;}
void dfs(int x,int f){
    for(int v:g[x])if(v!=f)dfs(v,x);
    if(jd[x]||(st[x]&S)){
        sz[x]=0;
        for(int v:g[x])if(v!=f)ans+=Cb(sz[v])*fh;
    }
    else{
        sz[x]=1;
        for(int v:g[x])if(v!=f)sz[x]+=sz[v];
    }
}
void sol(){
    m=0;
    int X,XX;
    scanf("%d%d",&n,&X);XX=X;
    for(int i=1;i<=n;i++)g[i].clear(),jd[i]=0,st[i]=0;
    for(int i=2;i*i<=X;i++)if(!(X%i)){
        m++,c[m]=0,p[m]=i;
        while(!(X%i))X/=i,c[m]++;
    }
    if(X>1)m++,c[m]=1,p[m]=X;
    for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),g[u].pb(v),g[v].pb(u);
    for(int i=1,a;i<=n;i++){
        scanf("%d",&a);
        if(XX%a){jd[i]=1;continue;}
        for(int j=1;j<=m;j++){
            int ca=0;
            while(!(a%p[j]))a/=p[j],ca++;
            if(ca==c[j])st[i]|=(1<<(j-1));
        }
    }
    ans=0;
    for(S=0;S<(1<<m);S++){
        fh=1;
        for(int i=0;i<m;i++)if((S>>i)&1)fh=-fh;
        dfs(1,0),ans+=Cb(sz[1])*fh;
    }
    printf("%lld\n",ans);
}
int main(){
    int T;scanf("%d",&T);while(T--)sol();
    return 0;
}