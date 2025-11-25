// Problem: Equal
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108300/E
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ll long long
int a[1000006];
ull dp[5000006];
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int vis[5000006];
int prime[5000006];
int cnt=0;
void sieve(int n)
{
    for(int i=2;i<=n;i++)
    {
        if(!vis[i])
        {
            prime[++cnt]=i;
            dp[i]=rnd();
        }
        for(int j=1;j<=cnt;j++)
        {
            if((ll)i*prime[j]>n) break;
            vis[i*prime[j]]=1;
            dp[i*prime[j]]=dp[i]^dp[prime[j]];
            if(i%prime[j]==0) break;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int T;cin>>T;
    sieve(5000001);
    while(T--)
    {
        int n;cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        if(n==2)
        {
            if(a[1]==a[2]) cout<<"YES\n";
            else cout<<"NO\n";
            continue;
        }
        if(n%2!=0)
        {
            cout<<"YES\n";
        }
        else
        {
            ull res=0;
            for(int i=1;i<=n;i++)
            {
                res=res^dp[a[i]];
            }
            if(res==0) cout<<"YES\n";
            else cout<<"NO\n";
        }
    }
    return 0;
}
