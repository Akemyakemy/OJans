// Problem: Bitwise Puzzle
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108300/B
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
typedef  long long ll;
typedef unsigned long long ull;
typedef  __int128 lli;
typedef pair<int,int>pii;
typedef pair<int,pair<int,int> >piii;
const __int128 iiinf=1e36;
const int inf=0x3f3f3f3f;const long long linf=5e18;
const int M=998244353;
mt19937_64 rnd(time(0));
int a,b,c;
vector<int>ans;
void p1()
{
    ans.push_back(1);a<<=1;
}
void p2()
{
    ans.push_back(2);b>>=1;
}
void p3()
{
    ans.push_back(3);a=(a^b);
}
void p4()
{
    ans.push_back(4);b=(b^a);
}
void solve()
{
    cin>>a>>b>>c;ans.clear();
    if (a==b&&a==c)
    {
        cout<<0<<'\n';cout<<'\n';return ;
    }
    if (a==b&&b==0)
    {
        cout<<-1<<'\n';return ;
    }
    int ra=-1,rb=-1,rc=-1;
    for (int i=0;i<31;i++)
    {
        if (a>>i&1)ra=i;
        if (b>>i&1)rb=i;
        if (c>>i&1)rc=i;
    }
    if (ra!=rb)
    {
        if (ra>rb)p4();
        else p3();
        ra=max(ra,rb);rb=max(ra,rb);
    }
    int dis=rc-rb;
    while (ra<rc)
    {
        if ((c>>(rb+dis)&1)!=(a>>rb&1))
        {
            p3();
        }
        ra++;p1();dis--;
    }
    while (b)
    {
        if ((a>>rb&1)!=(c>>rb&1))
        {
            p3();
        }
        p2();rb--;
    }
    p4();
    cout<<ans.size()<<'\n';
    for (auto x:ans)cout<<x<<' ';cout<<'\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t=1;cin>>t;
    while(t--)solve();
}
// 2 0 0 1 1 0 1 1 1 2 1 0