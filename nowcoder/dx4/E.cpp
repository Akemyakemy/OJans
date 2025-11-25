// Problem: Echoes of 24
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/E
// Memory Limit: 512 MB
// Time Limit: 6000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr)
#define PRE std::cout << std::fixed << std::setprecision(10)
#define rep(i, l, r) for (long long i = l; i <= r; i++)
#define per(i, r, l) for (long long i = r; i >= l; i--)
 
#define lowbit(x) (x & (-x))
#define int long long
using i64 = long long;
using pii = pair<i64, i64>;
const int N = 5e5 + 5;
 
struct node {
    int to, nxt;
} e[N << 1];
int idx, head[N];
void add(int u, int v) {
    e[++idx].to = v, e[idx].nxt = head[u], head[u] = idx;
}
int n, q;
int a[N], dep[N], f[N];
int son[N], siz[N];
int top[N], dfn[N], rnk[N], cnt;
 
void dfs1(int o) {
    son[o] = -1;
    siz[o] = 1;
    for (int j = head[o]; j; j = e[j].nxt)
        if (!dep[e[j].to]) {
            dep[e[j].to] = dep[o] + 1;
            f[e[j].to] = o;
            dfs1(e[j].to);
            siz[o] += siz[e[j].to];
            if (son[o] == -1 || siz[e[j].to] > siz[son[o]]) son[o] = e[j].to;
        }
}
 
void dfs2(int o, int t) {
    top[o] = t;
    cnt++;
    dfn[o] = cnt;
    rnk[cnt] = o;
    if (son[o] == -1) return;
    dfs2(son[o], t);
    for (int j = head[o]; j; j = e[j].nxt)
        if (e[j].to != son[o] && e[j].to != f[o]) dfs2(e[j].to, e[j].to);
}
 
int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]])
            u = f[top[u]];
        else
            v = f[top[v]];
    }
    return dep[u] > dep[v] ? v : u;
}
 
#define lc o << 1
#define rc o << 1 | 1
 
struct SegTree {
    int sum[N * 4];
 
    void build(int o, int l, int r) {
        if (l == r) {
            sum[o] = (a[rnk[l]] == 1 ? 0 : a[rnk[l]]);
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        sum[o] = sum[lc] + sum[rc];
    }
 
    int query(int o, int l, int r, int ql, int qr) {  // 查询 sum
        if (l > qr || r < ql) return 0;
        if (ql <= l && r <= qr) return sum[o];
        int mid = (l + r) >> 1;
        return query(lc, l, mid, ql, qr) + query(rc, mid + 1, r, ql, qr);
    }
 
    void update(int o, int l, int r, int x, int t) {  // 更新
        if (l == r) {
            sum[o] = t;
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(lc, l, mid, x, t);  // 左右分别更新
        else
            update(rc, mid + 1, r, x, t);
        sum[o] = sum[lc] + sum[rc];
    }
} st;
 
int querysum(int x, int y) {
    int ret = 0, fx = top[x], fy = top[y];
    while (fx != fy) {
        if (dep[fx] >= dep[fy])
            ret += st.query(1, 1, n, dfn[fx], dfn[x]), x = f[fx];
        else
            ret += st.query(1, 1, n, dfn[fy], dfn[y]), y = f[fy];
        fx = top[x];
        fy = top[y];
    }
    if (dfn[x] < dfn[y])
        ret += st.query(1, 1, n, dfn[x], dfn[y]);
    else
        ret += st.query(1, 1, n, dfn[y], dfn[x]);
    return ret;
}
 
void solve() {
    cin >> n >> q;
    rep(i, 1, n) cin >> a[i];
    rep(i, 2, n) {
        int u, v; cin >> u >> v;
        add(u, v); add(v, u);
    }
    dep[1] = 1;
    dfs1(1);
    dfs2(1, 1);
    st.build(1, 1, n);
 
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int l, r; cin >> l >> r;
            int ff = lca(l, r);
            int dis = dep[l] + dep[r] - 2 * dep[ff];
            if (dis <= 24) {
                int x = l, y = r;
                vector<int> c;
                while (x != ff) {
                    c.push_back(a[x]);
                    x = f[x];
                }
                c.push_back(a[ff]);
                stack<int> st;
                while (y != ff) {
                    st.push(a[y]);
                    y = f[y];
                }
                while (!st.empty()) {
                    c.push_back(st.top());
                    st.pop();
                }
                vector<bitset<25>> dp(25);
                dp[0][c[0]] = 1;
                for (int i = 1; i < c.size(); i++) {
                    rep(j, 1, 24)
                        if (dp[i - 1][j]) {
                            if (j + c[i] <= 24) dp[i][j + c[i]] = 1;
                            if (j * c[i] <= 24) dp[i][j * c[i]] = 1;
                        }
                }
                cout << dp[c.size() - 1][24] << "\n";
            }
            else {
                int t = (querysum(l, r) <= 24);
                cout << t << "\n";
            }
        }
        else {
            int x, d; cin >> x >> d;
            a[x] = d;
            if (d == 1) d = 0;
            st.update(1, 1, n, dfn[x], d);
        }
    }
}
 
signed main() {
    IOS; PRE;
    int T = 1; //cin >> T;
    while (T--) solve();
    return 0;
}