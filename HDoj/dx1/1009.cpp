// Problem: 子序列
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1009
// Memory Limit: 262144 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
int read(){
    int x=0;char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+(c^'0'),c=getchar();
    return x;
}
#define ll long long
int n;
int a[2000005],pos[2000005];
int tree[2000005];
void add(int x){for(;x<=n;x+=x&-x)tree[x]++;}
int ask(int x){int res=0;for(;x;x&=x-1)res+=tree[x];return res;}
void solve(){
    n=read();
    for(int i=1;i<=n;i++)pos[a[i]=read()]=i;
    for(int i=1;i<=n;i++)tree[i]=0;
    int l=0x3f3f3f3f,r=0;
    int ans=1;
    for(int i=n;i>=1;i--){
        int x=pos[i];
        l=min(l,x);
        r=max(r,x);
        add(x);
        int val=ask(x);
        if(l<x)ans=max(ans,x-l+1-(val-1)+1);
        if(x<r)ans=max(ans,r-x+1-(n-i)+val);
    }
    printf("%d\n",ans);
}
int main(){
    int _=read();
    while(_--)solve();
    return 0;
}