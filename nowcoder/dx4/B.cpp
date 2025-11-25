// Problem: Blind Alley
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/B
// Memory Limit: 2048 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define int long long
#define PII pair<int,int>
#define endl "\n"
const int N=1e6+5;
const int inf=1e16;
const int mod=1e9+7;
const int P=13331;
int dx[]={0,1,-1};
int dy[]={-1,0,0};
int dx1[]={0,1,-1};
int dy1[]={1,0,0};
 
struct node{
    int x,y;
    int len;
};
 
void solve()
{
    int n,m,k;
    cin >> n >> m >> k;
    char a[n+10][m+10];
    int st[n+10][m+10];
    bool vis[n+10][m+10];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin >> a[i][j];st[i][j]=0;vis[i][j]=0;
        }
    }
 
    queue<PII>q;
    a[1][m]='2';
    q.push({1,m});
    while(q.size())
    {
        int stx=q.front().first,sty=q.front().second;
        for(int i=0;i<3;i++)
        {
            int xx=stx+dx[i],yy=sty+dy[i];
            if(xx>0&&xx<=n&&yy>0&&yy<=m&&a[xx][yy]=='0')
            {
                a[xx][yy]='2';
                q.push({xx,yy});
            }
        }
        q.pop();
    }
 
    // for(int i=1;i<=n;i++)
    // {
    //     for(int j=1;j<=m;j++)
    //     {
    //         cout << a[i][j];
    //     }cout <<endl;
    // }cout <<endl;
 
    queue<node>q1;
    q1.push({1,1,0});
    vis[1][1]=1;
    while(q1.size())
    {
        int sum=q1.front().len;
        int stx=q1.front().x,sty=q1.front().y;
        for(int i=0;i<3;i++)
        {
            int xx=stx+dx1[i],yy=sty+dy1[i];
            if(xx>0&&xx<=n&&yy>0&&yy<=m&&a[xx][yy]!='1'&&vis[xx][yy]==0)
            {
                if(a[xx][yy]=='0')
                {
                    if(i==0)
                    {
                        if(st[xx][yy]<sum+1)
                        {
                            if(a[xx][yy]=='0')
                            {
                                st[xx][yy]=sum+1;
                                if(st[xx][yy]>=k)
                                {
                                    cout << "YES\n";
                                    return ;
                                }
                                q1.push({xx,yy,sum+1});
                            }
                        }
                    }
                    else
                    {
                        if(st[xx][yy]<sum)
                        {
                            if(a[xx][yy]=='0')
                            {
                                st[xx][yy]=sum;
                                if(st[xx][yy]>=k)
                                {
                                    cout << "YES\n";
                                    return ;
                                }
                                q1.push({xx,yy,sum});
                            }
                        }
                    }
                }
                else
                {
                    vis[xx][yy]=1;
                    q1.push({xx,yy,0});
                }
            }
        }
        q1.pop();
    }
 
    // for(int i=1;i<=n;i++)
    // {
    //     for(int j=1;j<=m;j++)
    //     {
    //         cout << st[i][j] <<" ";
    //     }cout <<endl;
    // }cout <<endl;
 
    cout << "NO\n";
}
 
signed main()
{
    IOS;
    int _=1; 
    cin >> _;
    while(_--)
    {
        solve();
    }
    return 0;
}