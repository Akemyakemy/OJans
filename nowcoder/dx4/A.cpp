// Problem: All Kinds of Dice
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/A
// Memory Limit: 2048 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mit map<int,int>::iterator
#define sit set<int>::iterator
#define itrm(g,x) for(mit g=x.begin();g!=x.end();g++)
#define itrs(g,x) for(sit g=x.begin();g!=x.end();g++)
#define ltype int
#define rep(i,j,k) for(ltype(i)=(j);(i)<=(k);(i)++)
#define rap(i,j,k) for(ltype(i)=(j);(i)<(k);(i)++)
#define per(i,j,k) for(ltype(i)=(j);(i)>=(k);(i)--)
#define pii pair<int,int>
#define fi first
#define se second
#define mpr make_pair
#define pb push_back
#define fastio ios::sync_with_stdio(false)
#define check(x) if(x>=mod) x-=mod
const ll inf=0x3f3f3f3f3f3f3f3f,mod=1000000007;
const double pi=3.1415926535897932,eps=1e-6;
template <typename T> void chmax(T &x,T y){if(x < y) x = y;}
template <typename T> void chmin(T &x,T y){if(x > y) x = y;}
int qpow(int x,int y){
    int ret = 1;
    while(y) {
        if(y & 1) ret = (ll)ret * x % mod;
        x = (ll)x * x % mod;
        y >>= 1;
    }
    return ret;
}
int n;
char s[105][105];
vector<int> ans[105];
//vector<vector<pii>> v;
int tot = 0;
void cons(vector<pii> v)
{
    vector<int> l(n + 1), r(n + 1), vis(n + 1);
    int id = 1;
    for(auto [x, y] : v) {
        /*if(vis[x] || vis[y]) {
            for(auto [X, Y] : v) {
                printf("%d %d\n",X,Y);
            }
        }*/
        assert(!vis[x] && !vis[y]);
        vis[x] = vis[y] = 1;
        l[x] = id;r[x] = (n + n + 1 - id);
        l[y] = id + 1;r[y] = (n + n - id);
        if(s[x][y] == '1') {
            swap(l[x], l[y]);
        }
        else {
            swap(r[x], r[y]);
        }
        id += 2;
    }
    rep(i,1,n) if(!vis[i]) {
        assert(id <= n);
        l[i] = id;r[i] = n + n + 1 - id;
        id++;
    }
    rep(i,1,n) {
        ans[i].pb(l[i] + tot * (n + n));
        ans[i].pb(r[i] + tot * (n + n));
    }
    tot++;
}
void cons_matching()
{
    rep(d,1,n/2) {
        if(d + d == n) {
            vector<pii> v;
            rep(j,1,n/2) v.pb(mpr(j, j + n / 2));
            cons(v);
            break;
        }
        vector<int> vis(n + 1);
        vector<pii> vec[3];
        rep(i,1,n) if(!vis[i]){
            int j = i;
            vector<int> path;
            while(!vis[j]) {
                path.pb(j);
                vis[j] = 1;
                j += d;
                j = (j - 1) % n + 1;
            }
            if(path.size() % 2 == 1) {
                rap(i,0,path.size()) {
                    int x = path[i];
                    if(i + 1 == path.size()) vec[2].pb(mpr(x, (x + d - 1) % n + 1));
                    else vec[i & 1].pb(mpr(x, (x + d - 1) % n + 1));
                }
            }
            else {
                rap(i,0,path.size()) {
                    int x = path[i];
                    vec[i & 1].pb(mpr(x, (x + d - 1) % n + 1));
                }
            }
        }
        cons(vec[0]);
        cons(vec[1]);
        if(vec[2].size()) cons(vec[2]);
    }
}
int main()
{
    scanf("%d",&n);
    rep(i,1,n) scanf("%s",s[i]+1);
    cons_matching();
    rep(i,1,n) {
        printf("%d ",ans[i].size());
        for(int x : ans[i]) {
            printf("%d ",x);
        }
        puts("");
    }
    return 0;
}