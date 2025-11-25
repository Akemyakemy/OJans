// Problem: K-th Memorable Sub-string
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/K
// Memory Limit: 2048 MB
// Time Limit: 10000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define ll long long
using namespace std;
 
const int N = 1e4 + 10;
const int mod = 998244353;
 
int n, m; string s;
int cnt = 1, last = 1, len[N << 1], fa[N << 1], ch[N << 1][2], ed[N << 1], siz[N << 1];
vector<int> memlen[N << 1], e[N << 1];
vector<int> f[N];
int tot, a[N << 1]; ll num[N << 1];
int g[N];
 
void add(int w) {
    int p = last, now = ++cnt; last = now;
    len[now] = len[p] + 1;
    for (; p && !ch[p][w]; p = fa[p]) ch[p][w] = now;
    if (!p) fa[now] = 1;
    else {
        int q = ch[p][w];
        if (len[q] == len[p] + 1) fa[now] = q;
        else {
            int nw = ++cnt;
            len[nw] = len[p] + 1, fa[nw] = fa[q];
            fa[now] = fa[q] = nw;
            memcpy(ch[nw], ch[q], sizeof(ch[q]));
            for (; p && ch[p][w] == q; p = fa[p]) ch[p][w] = nw;
        }
    }
    ed[now] = len[now];
    siz[now] = 1;
}
 
void dfs(int x) {
    for (int y : e[x]) {
        dfs(y);
        ed[x] = ed[y];
        siz[x] += siz[y];
    }
    if (e[x].size() == 2 && s[ed[e[x][0]] - len[x]] == '1') {
        reverse(e[x].begin(), e[x].end());
    }
}
 
void dfs2(int x) {
    for (int i = len[fa[x]] + 1; i <= len[x]; i++) {
        int t = ed[x] - f[ed[x]][ed[x] - i + 1] + 1;
        if (t > 0 && i - 2 * t <= m) {
            memlen[x].push_back(i);
        }
    }
    if (memlen[x].size()) {
        tot++;
        a[tot] = x;
        num[tot] = memlen[x].size() * siz[x];
        num[tot] += num[tot - 1];
    }
    for (int y : e[x]) dfs2(y);
}
 
int main() {
    // freopen("in.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n >> m >> s;
    reverse(s.begin(), s.end());
    s = "#" + s;
    for (int i = 1; i <= n; i++) {
        add(s[i] - '0');
    }
    for (int i = n; i >= 1; i--) {
        f[i].resize(i + 3);
        g[i] = i + 1;
        for (int j = i - 1, k = i + 1; j >= 1; j--) {
            while (k <= i && s[k - 1] != s[j]) k = g[k];
            if (s[k - 1] == s[j]) k--;
            g[j] = k;
        }   
        f[i][i] = i + 1;
        for (int j = i - 1, k = i + 1; j >= 1; j--) {
            while (k <= i && s[k - 1] != s[j]) k = g[k];
            if (s[k - 1] == s[j]) k--;
            while ((i - k + 1) * 2 > i - j + 1) k = g[k];
            f[i][j] = k;
        }   
    }
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= i; j++) {
    //         cout << f[i][j] << " \n"[j == i];
    //     }
    // }
    for (int i = 2; i <= cnt; i++) e[fa[i]].push_back(i);
    dfs(1);
    dfs2(1);
    // cout << num[tot] << "\n";
    assert(num[tot] > 0);
    ll lastans = 0;
    int q; cin >> q;
    while (q--) {
        ll vv; cin >> vv;
        ll now = (lastans + vv - 1) % num[tot] + 1;
        int l = 1, r = tot, mid, pos = 0;
        while (l <= r) {
            mid = (l + r) / 2;
            if (num[mid] < now) l = mid + 1, pos = mid;
            else r = mid - 1;
        }
        pos++;
        int x = a[pos];
        now -= num[pos - 1];
        now = (now + siz[x] - 1) / siz[x];
        int len = memlen[x][now - 1];
        lastans = 0;
        for (int i = 0; i < len; i++) {
            lastans = (lastans * 2ll + s[ed[x] - i] - '0') % mod;
            cout << s[ed[x] - i];
        }
        cout << "\n";
    }
    return 0;
}