// Problem: Kaleidoscope
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108300/K
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb push_back
#define sz(a) ((int)a.size())
#define re return
#define all(a) a.begin(),a.end()
#define rept(i,a,b) for(int i=(a);i<(b);i++)
#define rep(i,a) rept(i,0,a)
#define vi vector<int>
#define pii pair<int,int>
#define F first
#define S second
#define de(x) cout<<#x<<"="<<x<<"\n";
#define int long long
#define il inline
#define db double
#define ld long db
using namespace std;
const int MOD=998244353,INF=1000000000000000000;
template<typename T>inline void Mx(T &a,T b){a=max(a,b);}
template<typename T>inline void Mi(T &a,T b){a=min(a,b);}
void FILEIO(string s){
    freopen((s+".in").c_str(),"r",stdin);
    freopen((s+".out").c_str(),"w",stdout);
}
const int N=5005;
int n,a[N],dp[N][N],in[N],r[N];
void run(){
    cin>>n;
    rep(i,n+2)in[i]=-1;
    rep(i,n){
        cin>>a[i];a[i]--;
        if(~a[i])in[a[i]]=i;
    }
    rep(i,n+1){
        rept(j,i,n+2)if(!~in[j]){
            r[i]=j;break;
        }
    }
    rep(i,n+1)rep(j,n+1)dp[i][j]=0;
    dp[0][(~a[0])?a[0]:r[0]]=1;
    rep(i,n){
        int cnt=0,np=a[i+1];
        rep(j,n){
            if(in[j]<=i)cnt++;
            if(dp[i][j]){
//              cout<<i<<" "<<j<<" "<<dp[i][j]<<"\n";
                if(~np){
                    if(np<j)(dp[i+1][j]+=dp[i][j]*(i+1))%=MOD;
                    else{
                        (dp[i+1][np]+=dp[i][j])%=MOD;
                        if(!~in[j]&&r[np+1]<n)(dp[i+1][r[np+1]]+=dp[i][j]*(i+1))%=MOD;
                    }
                }
                else{
                    if(r[j+1]<n)(dp[i+1][r[j+1]]+=dp[i][j])%=MOD;
                    if(cnt>=i+2)(dp[i+1][j]+=dp[i][j]*(i+1))%=MOD;
                    else if(!~in[j]&&r[j+1]<n)(dp[i+1][r[j+1]]+=dp[i][j]*(i+1))%=MOD;
                }
            }
        }
    }
    cout<<dp[n-1][n-1]<<"\n";
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T=1;
    cin>>T;
    while(T--)
        run();
    re 0;
}