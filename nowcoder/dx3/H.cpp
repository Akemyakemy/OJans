// Problem: Head out to the Target
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108300/H
// Memory Limit: 1024 MB
// Time Limit: 6000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<iostream>
#include<vector>
using namespace std;
int f[21][1000001];
int u[1000001],l[1000001],r[1000001];
bool vis[1000001];
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n,k;
    cin>>n>>k;
    f[0][1]=1;
    for(int i=2;i<=n;i++)
        cin>>f[0][i];
    for(int i=1;i<=k;i++)
        cin>>u[i]>>l[i]>>r[i];
    for(int i=1;i<=20;i++)
        for(int j=1;j<=n;j++)
            f[i][j]=f[i-1][f[i-1][j]];
    vis[1]=1;
    for(int i=1;i<=k;i++)
    {
        int x=u[i],st=0;
        for(int j=20;j>=0;j--)
            if(!vis[f[j][x]])
                x=f[j][x],st+=(1<<j);
        st++;
        if(st<=r[i]-l[i]+1)
        {
            cout<<l[i]+st-1;
            return 0;
        }
        x=u[i];
        st-=(r[i]-l[i]+1);
        int stt=0;
        for(int j=20;j>=1;j--)
        {
            if(stt+(1<<j)<=st)
                stt+=(1<<j),x=f[j][x];
        }
        for(int j=1;j<=r[i]-l[i]+1;j++)
            vis[x]=1,x=f[0][x];
    }
    cout<<-1;
    return 0;
}