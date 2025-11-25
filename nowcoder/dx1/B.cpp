// Problem: Binary Substrings 2
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108298/B
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int tot,jj,sum;
bool flag1;
  
void solve()
{
    cin>>n>>m;
    flag1=false;
    int i,j;
    for(i=0;i<=n;i++)
    {
        sum=i*(n-i)+n;
        if(sum>=m) flag1=true;
        if(5*abs(sum-m)<=m)
        {
            for(j=1;j<=i;j++) cout<<1;
            for(j=i+1;j<=n;j++) cout<<0;
            cout<<'\n';
            return;
        }
    }
    if(flag1) 
    {
        cout<<-1<<'\n';
        return;
    }
    for(int t=3;t<=6;t++)
    {
        sum=(t-1)*n*n/(2*t);
        if(5*abs(sum-m)<=m)
        {
            tot=1,jj=1;
            while(tot<=n)
            {
                for(i=1;i<=n/t;i++)
                    if(tot<=n) {  cout<<0; tot++; }   
                for(i=1;i<=jj;i++)
                    if(tot<=n) { cout<<1;tot++;}
                jj++;
            }
            cout<<'\n';
            return;
        }
    }
    cout<<-1<<'\n';
    return;
}
signed main()
{
    int t;  cin>>t;
    while(t--) solve();
    return 0;
}
