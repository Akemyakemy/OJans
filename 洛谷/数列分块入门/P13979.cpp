// Problem: P13979 数列分块入门 4
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P13979
// Memory Limit: 512 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#pragma optimize(3)
#define int long long
using namespace std;
int n;
int bl=0;
double k=0.5,p=0.5;
int bid[314514],a[314514],b[314514],bls[314514];
void build(int n){
    bl=p*pow(n,k);
    for(int i=1;i<=n;i++){
        bid[i]=(i-1)/bl+1;
        bls[bid[i]]+=a[i];
    }
}
int li(int id){return bl*(id-1)+1;}
int ri(int id){return min(n,bl*id);}
inline void change(int l,int r,int c){
    int t=min(r,ri(bid[l])),f=bid[l];
    for(int i=l;i<=t;i++){
        a[i]+=c;
        bls[f]+=c;
    }
    if(bid[l]!=bid[r]){
        int t=li(bid[r]),f=bid[r];
        for(int i=t;i<=r;i++){
            a[i]+=c;
            bls[f]+=c;
        }
    }
    for(int i=bid[l]+1;i<bid[r];i++)b[i]+=c;
}
inline int query(int l,int r,int modk){
    const int mod=modk;
    int t=ri(bid[l]),f=bid[l];
    int ans=0;
    for(int i=l;i<=min(r,t);i++){
        ans=ans+a[i]+b[f];
    }
    if(bid[l]!=bid[r]){
        int t=li(bid[r]),f=bid[r];
        for(int i=t;i<=r;i++)ans=ans+a[i]+b[f];
    }
    for(int i=bid[l]+1;i<bid[r];i++)ans=ans+b[i]*bl+bls[i];
    return (ans%mod+mod)%mod;
}
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(n);
    int op,l,r,c;
    for(int i=1;i<=n;i++){
        cin>>op>>l>>r>>c;
        if(op==1){
            cout<<query(l,r,c+1)<<"\n";
        }
        else{
            change(l,r,c);
        }
    }
}