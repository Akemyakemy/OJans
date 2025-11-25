// Problem: 夜世界
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1002
// Memory Limit: 262144 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
int n,m,a[201000],b[200100];
#define pb push_back
vector<int>g[200100],G[200100];int typ[201000],X[200100],Y[200100],fa[201000],lst[201000];
#define ll long long
#define fi first
#define se second
ll sa[800100],sb[800100];
pair<ll,int>qz[800100];
#define pi pair<ll,int>
void sc(int p){
    sa[p]=sa[p<<1]+sa[p<<1|1];
    sb[p]=sb[p<<1]+sb[p<<1|1];
    qz[p]=min(qz[p<<1],{qz[p<<1|1].fi+sa[p<<1]-sb[p<<1],qz[p<<1|1].se});
}
void build(int p,int l,int r){
    if(l==r){
        sa[p]=a[l],sb[p]=b[l];
        qz[p]={a[l]-b[l],l};
        return;
    }
    int mid=(l+r)>>1;
    build(p<<1,l,mid),build(p<<1|1,mid+1,r),sc(p);
}
void up(int p,int l,int r,int x){
    if(l==r){
        sa[p]=a[l],sb[p]=b[l];
        qz[p]={a[l]-b[l],l};
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)up(p<<1,l,mid,x);else up(p<<1|1,mid+1,r,x);
    sc(p);
}
array<ll,3> ask(int p,int l,int r,int x,int y){
    if(x<=l&&r<=y)return {qz[p].fi,(ll)qz[p].se,sa[p]-sb[p]};
    int mid=(l+r)>>1;
    if(y<=mid)return ask(p<<1,l,mid,x,y);if(x>mid)return ask(p<<1|1,mid+1,r,x,y);
    array<ll,3>Pl=ask(p<<1,l,mid,x,y),Pr=ask(p<<1|1,mid+1,r,x,y);
    Pr[0]+=Pl[2];ll sum=Pl[2]+Pr[2];Pl[2]=Pr[2]=sum;
    return min(Pl,Pr);
}
ll ask2(int p,int l,int r,int x,int y,int z){
    if(x<=l&&r<=y)return (z?sb[p]:sa[p]);
    int mid=(l+r)>>1;ll zk=0;
    if(x<=mid)zk+=ask2(p<<1,l,mid,x,y,z);
    if(y>mid)zk+=ask2(p<<1|1,mid+1,r,x,y,z);
    return zk;
}
ll ans[200100];
void dfs(int x){
    if(typ[x]<=2){
        int i=X[x],z=Y[x];
        if(typ[x]==1)lst[x]=a[i],a[i]=z;
        else lst[x]=b[i],b[i]=z;
        up(1,1,n,i);
    }
    if(typ[x]==4){
        int sz=g[x].size();ll S=0;
        for(int i=0;i<=sz;i++){
            int L=(i?(g[x][i-1]+1):1),R=((i==sz)?n:(g[x][i]-1));
            if(L<=R){
                array<ll,3>xp=ask(1,1,n,L,R);
                if(xp[0]+S<=0){
                    int P=xp[1];
                    ans[x]+=S+ask2(1,1,n,L,P,0);
                    if(P<R){
                        ll sa=ask2(1,1,n,P+1,R,0),sb=ask2(1,1,n,P+1,R,1);
                        ans[x]+=sb,S=sa-sb;
                    }
                    else S=0;
                }
                else{
                    ll sa=ask2(1,1,n,L,R,0),sb=ask2(1,1,n,L,R,1);
                    S+=sa-sb,ans[x]+=sb;
                }
            }
            if(i<sz){
                S+=a[g[x][i]];
                ans[x]+=(S+1)/2,S/=2;
            }
        }
    }
    for(int v:G[x])dfs(v);
    if(typ[x]<=2){
        int i=X[x];
        if(typ[x]==1)a[i]=lst[x];
        else b[i]=lst[x];
        up(1,1,n,i);
    }
}
void sol(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)scanf("%d",&b[i]);
    for(int i=0;i<=m;i++)g[i].clear(),G[i].clear(),ans[i]=0;
    for(int i=1;i<=m;i++){
        fa[i]=i-1;
        scanf("%d",&typ[i]);
        if(typ[i]<=2)scanf("%d%d",&X[i],&Y[i]);
        else if(typ[i]==3)scanf("%d",&X[i]),fa[i]=X[i];
        else{
            int sz,a;scanf("%d",&sz);while(sz--)scanf("%d",&a),g[i].pb(a);
        }
        G[fa[i]].pb(i);
    }
    build(1,1,n);
    dfs(0);
    for(int i=1;i<=m;i++)if(typ[i]==4)printf("%lld\n",ans[i]);
}
int main(){
    int T;scanf("%d",&T);while(T--)sol();
    return 0;
}