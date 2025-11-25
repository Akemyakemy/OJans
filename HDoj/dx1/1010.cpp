// Problem: 中位数
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1010
// Memory Limit: 262144 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
int a[2005];
int vis[2005];
int pre[2005],nxt[2005];
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    ll ans=0;
    for(int i=1;i<=n;i++){
        int lim=n;if(lim-i&1)lim--;
        for(int j=i;j<=lim;j++)vis[a[j]]=1;
        int lst=0;
        for(int j=1;j<=n;j++)if(vis[j])
            nxt[lst]=j,pre[j]=lst,lst=j;
        nxt[lst]=n+1,pre[n+1]=lst;
        int mid=0;
        for(int j=1;j<=(lim-i)/2+1;j++)mid=nxt[mid];
        for(int j=lim;j>i;j-=2){
            ans+=1ll*i*j*mid;
            if(a[j]<=mid&&a[j-1]<=mid)mid=nxt[mid];
            else if(a[j]>=mid&&a[j-1]>=mid)mid=pre[mid];
            int x=a[j];
            nxt[pre[x]]=nxt[x];
            pre[nxt[x]]=pre[x];
            x=a[j-1];
            nxt[pre[x]]=nxt[x];
            pre[nxt[x]]=pre[x];
        }
        ans+=1ll*i*i*a[i];
        for(int j=i;j<=lim;j++)vis[a[j]]=0;
    }
    printf("%lld\n",ans);
}
int main(){
    int _;scanf("%d",&_);
    while(_--)solve();
    return 0;
}