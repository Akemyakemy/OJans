// Problem: For the Treasury!
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/F
// Memory Limit: 2048 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
int n,k,c;
int a[300005];
int v[300005];
inline int re(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int main(){
    cin>>n>>k>>c;
    for(int i=1;i<=n;++i)
    a[i]=re();
     
    for(int i=1;i<=n;++i){
        v[i]=a[i]+(k-i)*c;
      //  cout<<"v["<<i<<"]="<<v[i]<<endl;
    }
    int ans=0,k1=0,k2=0;
    for(int i=1;i<=k;++i)
    ans+=a[i],k1+=v[i];
     
    sort(v+1,v+n+1);
    for(int i=n;i>=n-k+1;--i)
    k2+=v[i];
     
    ans+=k2-k1;
    cout<<ans;
}