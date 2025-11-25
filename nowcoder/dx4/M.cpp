// Problem: Monopoly
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/M
// Memory Limit: 2048 MB
// Time Limit: 24000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
int n,a[55];
#define ull unsigned long long
ull se=1313131313131313131,wz[55];
ull ran(){
    return se^=se<<13,se^=se>>7,se^=se<<17,se;
}
#include<bits/extc++.h>
__gnu_pbds::gp_hash_table<ull,int>mp;
int dfs(std::vector<int> a){
    ull he=0;
    std::sort(a.begin(),a.end());
    int mi=a[0];
    for(int i=0;i<a.size();i++) {
        a[i]-=mi;
    }
    for(int i=0;i<a.size();i++) {
        if(i&&a[i]==a[i-1]) continue;
        for(int j=i;j<a.size();j++) {
            if(a[j]>=a[i]+(1<<j-i)) {
                break;
            }
            a[j]=a[i];
        }
    }
    while((!a.empty())&&a[a.size()-1]<=(1<<a.size()-1)-1) {
        a.pop_back();
    }
    if(a.empty()) return mi;
    for(int i=0;i<a.size();i++) he+=wz[a[i]];
    auto it=mp.find(he);
    if(it!=mp.end()) return (*it).second+mi;
    int qq=a[a.size()-1];
    a.pop_back();
    int ans=qq;
    int mii=dfs(a);
    a.push_back(qq);
    for(int x=0;x<a.size()&&(ans>mii);x++) {
        if(x&&a[x]==a[x-1]) continue;
        for(int y=x+1;y<a.size()&&(ans>mii);y++) {
            if(a[x]!=a[y]&&(y+1==a.size()||a[y]!=a[y+1])){
                int aa=a[x],bb=a[y];
                a[x]=a[y]=(aa+bb)/2;
                ans=min(ans,dfs(a));
                a[x]=aa,a[y]=bb;
            }
        }
    }
    mp[he]=ans;
    return ans+mi;
}
int main(){
    for(int i=0;i<=50;++i)wz[i]=ran();
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        std::vector<int> a;
        for(int i=1;i<=n;++i){
            int x;scanf("%d",&x);
            a.push_back(x);
        }
        sort(a.begin(),a.end());
        if(a.size()>6) a.resize(6);
        printf("%d\n",dfs(a));
    }
    return 0;
}