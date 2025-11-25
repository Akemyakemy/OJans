// Problem: Highway Upgrade
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/H
// Memory Limit: 1024 MB
// Time Limit: 6000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <list>
 
using namespace std;
 
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<LL, int> PLI;
typedef pair<LL, LL> PLL;
 
const int N = 2e5 + 10;
const int M = 6e5 + 10;
const LL INF = 1e18;
 
int fh[N], rh[N], fe[M], re[M], fnxt[M], rnxt[M], fidx, ridx;
LL fw[M], rw[M], ft[M], rt[M];
int n, m;
 
void addf(int u, int v, LL wi, LL ti)
{
    fe[fidx] = v;
    fw[fidx] = wi;
    ft[fidx] = ti;
    fnxt[fidx] = fh[u];
    fh[u] = fidx++;
}
 
void addb(int u, int v, LL wi, LL ti)
{
    re[ridx] = v;
    rw[ridx] = wi;
    rt[ridx] = ti;
    rnxt[ridx] = rh[u];
    rh[u] = ridx++;
}
 
LL fdist[N], bdist[N];
bool st[N];
 
void dijkstra(int rt, LL dist[], int nxt[], LL t[], int e[], int h[])
{
    for (int i = 1; i <= n; i++) st[i] = false;
    for (int i = 1; i <= n; i++) dist[i] = INF;
 
    dist[rt] = 0;
    priority_queue<PLI, vector<PLI>, greater<PLI>> heap;
    heap.push({ 0, rt });
 
    while (heap.size())
    {
        auto top = heap.top();
        heap.pop();
 
        int ver = top.second;
        LL dis = top.first;
 
        if (st[ver]) continue;
        st[ver] = true;
 
        for (int i = h[ver]; i != -1; i = nxt[i])
        {
            int j = e[i];
            if (dist[j] > dis + t[i])
            {
                dist[j] = dis + t[i];
                heap.push({ dist[j], j });
            }
        }
    }
}
 
struct line {
    LL k, b;
    LL el, er;
}p[M * 2];
 
int lnum;
 
struct node {
    int ls, rs;
    LL tag;
}tr[M * 100];
 
int tot, root;
 
inline LL Y(int id, LL x)
{
    return p[id].k * x + p[id].b;
}
 
void change(int& u, LL id, LL l, LL r, LL L, LL R)
{
    LL mid = l + r >> 1ll;
 
    if (!u) 
    {
        u = ++tot; 
        tr[u] = { 0, 0, 0 };
    }
 
    int& ls = tr[u].ls;
    int& rs = tr[u].rs;
 
    if (L <= l && r <= R)
    {
        if (Y(id, mid) < Y(tr[u].tag, mid)) swap(id, tr[u].tag);
        if (Y(id, l) < Y(tr[u].tag, l)) change(ls, id, l, mid, L, R);
        if (Y(id, r) < Y(tr[u].tag, r)) change(rs, id, mid + 1, r, L, R);
        return;
    }
    else
    {
        if (L <= mid) change(ls, id, l, mid, L, R);
        if (mid < R) change(rs, id, mid + 1, r, L, R);
    }
}
 
LL query(int u, LL x, LL l, LL r)
{
    if (u == 0) return INF;
    if (l == r) return Y(tr[u].tag, x);
 
    LL mid = l + r >> 1ll;
    LL t = Y(tr[u].tag, x);
    int ls = tr[u].ls, rs = tr[u].rs;
 
    if (x <= mid)
        return min(t, query(ls, x, l, mid));
    else
        return min(t, query(rs, x, mid + 1, r));
}
 
LL k[M];
 
void solve()
{
    scanf("%d %d", &n, &m);
 
    //node tmpnode;
    for (int i = 1; i <= n; i++) fh[i] = rh[i] = -1;
    //memset(tr, 0, (sizeof tr));
    //memset(tr, 0, (sizeof tmpnode) * (tot + 10));
    tot = 0, lnum = 0, root = 0, fidx = 0, ridx = 0;
 
    int u, v;
    LL ti, wi;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d %lld %lld", &u, &v, &ti, &wi);
        addf(u, v, wi, ti);
        addb(v, u, wi, ti);
    }
 
    int q;
    scanf("%d", &q);
    LL kmax = 0;
    for (int i = 1; i <= q; i++)
    {
        scanf("%lld", &k[i]);
        kmax = max(kmax, k[i]);
    }
    kmax += 5;
 
    //cout << "kmax: " << kmax << endl;
 
    dijkstra(1, fdist, fnxt, ft, fe, fh);
    dijkstra(n, bdist, rnxt, rt, re, rh);
 
    p[0] = { 0, INF, 0, kmax };
    for (int i = 1; i <= n; i++)
    {
        for (int j = fh[i]; j != -1; j = fnxt[j])
        {
            int v = fe[j];
            if (fdist[i] >= INF || bdist[v] >= INF) continue;
 
            LL ck = -fw[j];
            LL cb = fdist[i] + bdist[v] + ft[j];
 
            //cout << i << " " << v << " " << ck << " " << cb << endl;
 
            p[++lnum] = { ck, cb, 0, kmax };
            change(root, lnum, 0, kmax, 0, kmax);
        }
    }
 
    for (int i = 1; i <= q; i++)
    {
        LL ans = query(root, k[i], 0, kmax);
        printf("%lld\n", ans);
    }
}
 
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}