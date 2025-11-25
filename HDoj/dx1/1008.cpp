// Problem: mod 2
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1008
// Memory Limit: 524288 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
int n,a[300100],qc[300100],cn;
mt19937 rnd(time(0));
#define ll long long
const ll XP=(1ll<<60)-1;
int ls[6001000],rs[6001000],N,T[300100];
ll vp[6001000],fk[301000];
void up(int &p,int lst,int l,int r,int x){
    p=++N,ls[p]=ls[lst],rs[p]=rs[lst],vp[p]=vp[lst]^fk[x];
    if(l==r)return;int mid=(l+r)>>1;
    if(x<=mid)up(ls[p],ls[lst],l,mid,x);
    else up(rs[p],rs[lst],mid+1,r,x);
}
int ask(int p1,int p2,int l,int r,int x){
    if(vp[p1]==vp[p2])return n+1;
    if(l==r)return l;
    int mid=(l+r)>>1;
    if(x>mid)return ask(rs[p1],rs[p2],mid+1,r,x);
    int z=ask(ls[p1],ls[p2],l,mid,x);if(z!=n+1)return z;
    return ask(rs[p1],rs[p2],mid+1,r,mid+1);
}

int S2[70][70],co[70][70];
int Query(int l,int r,ll K,ll V){
    int B=0;
    for(int i=0;i<60;i++)if((K>>i)&1)B++;
    int C=0,lp=1,mx=0;
    while(lp<=cn&&C<=B){
        int nxt=ask(T[l-1],T[r],1,cn,lp);
        if(nxt<=cn)mx=max(mx,qc[nxt]),C++;
        lp=nxt+1;
    }
    if(mx>V||C>B)return 0;
    if(K&1){
        if(!((V-C)&1))return 0;
        B--;
        int ans=0;
        for(int i=0;i<=B;i++)ans^=(co[B][i]&S2[B-i][C]);
        return ans;
    }
    return S2[B][C];
}
void sol(){
    for(int i=1;i<=N;i++)ls[i]=rs[i]=0,vp[i]=0;
    N=cn=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),qc[++cn]=a[i],fk[i]=((1ll*rnd()*rnd()+rnd())&XP);
    sort(qc+1,qc+cn+1);cn=unique(qc+1,qc+cn+1)-qc-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(qc+1,qc+cn+1,a[i])-qc,
    up(T[i],T[i-1],1,cn,a[i]);
    int q;scanf("%d",&q);
    ll preans=0;
    for(int i=1;i<=q;i++){
        ll K,V,l,r;
        scanf("%lld%lld%lld%lld",&l,&r,&K,&V);
        l^=preans,r^=preans,K^=preans,V^=preans;
        int zz=Query(l,r,K,V);
        printf("%d\n",zz),preans+=zz;
    }
}
int main(){
    co[0][0]=1,S2[0][0]=1;
    for(int i=1;i<=60;i++){
        co[i][0]=1;
        for(int j=1;j<=i;j++){
            co[i][j]=co[i-1][j-1]^co[i-1][j];
            S2[i][j]=S2[i-1][j-1];
            if(j&1)S2[i][j]^=S2[i-1][j];
        }
    }
    int T;scanf("%d",&T);while(T--)sol();
    return 0;
}