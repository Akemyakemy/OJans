#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[200005],d[200005];
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
    t=re();
    while(t--){
        n=re();
        for(int i=1;i<=n;++i)
        a[i]=re();
        d[n]=a[n]; 
        for(int i=n-1;i>=1;--i)
        d[i]=min(a[i],d[i+1]);
        int ans=0;
        for(int i=1;i<=n;++i)
        ans=max(ans,a[i]-d[i]);
        cout<<ans<<endl;
    }
    return 0;
}