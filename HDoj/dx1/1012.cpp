// Problem: 请输入文本
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1012
// Memory Limit: 65536 MB
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
int n,k;
void solve(){
    scanf("%d%d",&n,&k);
    int p=1;while(p*(p+1)/2<n)p++;
    if(n==p*(p+1)/2){
        if(k>1)puts("-1");
        else printf("%d\n",n);
    }else{
        if(p%k)puts("-1");
        else{
            int val=p*(p/k-1)/2;
            if((n-val)%(p/k))puts("-1");
            else{
                for(int i=0;i<p/k;i++)printf("%d ",(n-val)/(p/k)+i*k);puts("");
            }
        }
    }
}
int main(){
    int _=read();
    while(_--)solve();
    return 0;
}