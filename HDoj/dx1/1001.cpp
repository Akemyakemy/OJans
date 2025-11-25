// Problem: 博弈
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1001
// Memory Limit: 524288 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,P[4],jc[1001000],ij[1001000];
int qpow(int a,int b){
    int c=1;
    for(;b;b>>=1){
        if(b&1)c=1ll*a*c%mod;
        a=1ll*a*a%mod;
    }
    return c;
}
int C(int a,int b){
    if(a<b||a<0||b<0)return 0;
    return 1ll*jc[a]*ij[b]%mod*ij[a-b]%mod;
}
void sol(){
    P[0]=P[1]=P[2]=P[3]=0;
    scanf("%d",&n);while(n--){
        int xo=0,cc=0,sz,a;scanf("%d",&sz);
        while(sz--)scanf("%d",&a),xo^=a,cc+=(a>1);
        if(cc)P[xo?1:0]++;else P[xo?3:2]++;
    }
    //0:负 1:胜 2：不变 3：反转
    int P2=1ll*C(P[0]+P[1]+P[2]+P[3],P[2])*jc[P[2]]%mod;
    int ans=0;
    if(!P[0]&&!P[1]){
        if(P[3]&1)printf("%d\n",1ll*P2*jc[P[3]]%mod);
        else puts("0");
        return;
    }
    for(int i=0;i<=P[3];i++){
        if((i&1)&&P[0])(ans+=1ll*C(P[3],i)*jc[i]%mod*P[0]%mod*jc[P[0]+P[1]+P[3]-i-1]%mod)%=mod;
        if(!(i&1)&&P[1])(ans+=1ll*C(P[3],i)*jc[i]%mod*P[1]%mod*jc[P[0]+P[1]+P[3]-i-1]%mod)%=mod;
    }
    printf("%d\n",1ll*ans*P2%mod);
}
int main(){
    jc[0]=1;int N=1e6;
    for(int i=1;i<=N;i++)jc[i]=1ll*i*jc[i-1]%mod;
    ij[N]=qpow(jc[N],mod-2);
    for(int i=N;i;i--)ij[i-1]=1ll*i*ij[i]%mod;
    int T;scanf("%d",&T);while(T--)sol();
    return 0;
}