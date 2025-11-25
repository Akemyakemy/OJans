// Problem: Clamped Sequence 2
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108298/C
// Memory Limit: 1024 MB
// Time Limit: 16000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define ll long long
using namespace std;
 
const int N = 1e3 + 10, Q = 1e6 + 10;
 
int n, q, cnt, a[N], s[N], b[N];
vector<int> pos[N];
bool v[N]; 
struct node {
    int x; ll val;
} e[N * N]; int ecnt;
ll kl[N], kr[N];
struct Query {
    int d, id;
} ask[Q]; ll ans[Q];
struct seg {
    int u, v; ll k, b;
} c[N * N]; int ccnt;
vector<int> t[Q << 2];
struct convex_hull {
    int l, r; ll k, b;
} sta[N * N]; int tp;
 
bool cmp(const Query &p1, const Query &p2) {
    return p1.d < p2.d;
}
bool cmp2(const node &p1, const node &p2) {
    return p1.x < p2.x;
}
bool cmp3(const seg &p1, const seg &p2) {
    return p1.k < p2.k;
}
 
void addseg(int p, int l, int r, int x, int y, int id) {
    if (x <= ask[l].d && ask[r].d <= y) {
        t[p].push_back(id);
        return;
    }
    if (l == r) return;
    int mid = (l + r) / 2;
    if (x <= ask[mid].d) addseg(p << 1, l, mid, x, y, id);
    if (ask[mid + 1].d <= y) addseg(p << 1 | 1, mid + 1, r, x, y, id);
}
 
bool check(ll k1, ll b1, ll k2, ll b2, int x) {
    return k1 * x + b1 >= k2 * x + b2;
}
 
void dfs(int p, int l, int r) {
    if (t[p].size()) {
        sta[tp = 1] = (convex_hull){ask[l].d, ask[r].d, c[t[p][0]].k, c[t[p][0]].b};
        for (int i = 1; i < t[p].size(); i++) {
            ll k = c[t[p][i]].k, b = c[t[p][i]].b;
            while (tp && check(k, b, sta[tp].k, sta[tp].b, sta[tp].l)) tp--;
            if (!tp) {
                sta[tp = 1] = (convex_hull){ask[l].d, ask[r].d, k, b};
                continue;
            }
            if (!check(k, b, sta[tp].k, sta[tp].b, sta[tp].r)) {
                if (sta[tp].r < ask[r].d) {
                    int last = sta[tp].r;
                    sta[++tp] = (convex_hull){last + 1, ask[r].d, k, b};
                }
                continue;
            }
            ll pp = sta[tp].b - b;
            ll qq = k - sta[tp].k;
            int x = (pp + qq - 1) / qq;
            // assert(!check(k, b, sta[tp].k, sta[tp].b, x - 1) && check(k, b, sta[tp].k, sta[tp].b, x));
            sta[tp].r = x - 1;
            sta[++tp] = (convex_hull){x, ask[r].d, k, b};
             
        }
        for (int i = l, j = 1; i <= r; i++) {
            while (sta[j].r < ask[i].d) j++;
            ans[ask[i].id] = max(ans[ask[i].id], sta[j].k * ask[i].d + sta[j].b);
        }
    }
    if (l == r) return;
    int mid = (l + r) / 2;
    dfs(p << 1, l, mid);
    dfs(p << 1 | 1, mid + 1, r);
}
 
int main() {
//     freopen("in.in", "r", stdin);
//     freopen("out.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
     
    // auto start = chrono::high_resolution_clock::now();
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[++cnt] = a[i];
    }
    for (int i = 1; i < n; i++) cin >> b[i];
    sort(s + 1, s + cnt + 1);
    cnt = unique(s + 1, s + cnt + 1) - s - 1;
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(s + 1, s + cnt + 1, a[i]) - s;
        pos[a[i]].push_back(i);
    }
    for (int i = 1; i <= 1; i++) {
        memset(v, 0, sizeof(v));
        ll k = 0;
        for (int j = cnt; j > i; j--) {
            for (int x : pos[j]) {
                if (x > 1) {
                    if (v[x - 1]) k -= b[x - 1];
                    else k += b[x - 1];
                }
                if (x < n) {
                    if (v[x + 1]) k -= b[x];
                    else k += b[x];
                }
                v[x] = 1;
            }
            kr[j] = k;
        }
    }
    for (int i = cnt; i >= cnt; i--) {
        memset(v, 0, sizeof(v));
        ll k = 0;
        for (int j = 1; j < i; j++) {
            for (int x : pos[j]) {
                if (x > 1) {
                    if (v[x - 1]) k -= b[x - 1];
                    else k += b[x - 1];
                }
                if (x < n) {
                    if (v[x + 1]) k -= b[x];
                    else k += b[x];
                }
                v[x] = 1;
            }
            kl[j] = k;
        }
    }
    for (int i = 1; i <= q; i++) {
        cin >> ask[i].d;
        ask[i].id = i;
    }
    sort(ask + 1, ask + q + 1, cmp);
 
    ll sum = 0;
    for (int i = 1; i < n; i++) sum += 1ll * abs(s[a[i]]- s[a[i + 1]]) * b[i];
    ll now = sum;
    for (int l = 1; l < cnt; l++) {
        int d = s[cnt] - s[l];
        ll noww = now;
        for (int r = cnt; r > l; r--) {
            int dd = s[r] - s[r - 1];
            ll k = kr[r];
            ll b = noww - k * dd;
            d -= dd;
            int u = d, v = d + dd;
            if (k <= 0) {
                e[++ecnt] = (node){u, b};
            }
            else {
                e[++ecnt] = (node){v, noww};
                b -= u * k;
                c[++ccnt] = (seg){u, v, k, b};
            }
            noww -= dd * k;
        }
        now -= kl[l] * (s[l + 1] - s[l]);
    }
    now = sum;
    for (int r = cnt; r > 1; r--) {
        int d = s[r] - s[1];
        ll noww = now;
        for (int l = 1; l < r; l++) {
            int dd = s[l + 1] - s[l];
            ll k = kl[l];
            ll b = noww - k * dd;
            d -= dd;
            int u = d, v = d + dd;
            if (k <= 0) {
                e[++ecnt] = (node){u, b};
            }
            else {
                e[++ecnt] = (node){v, noww};
                b -= u * k;
                c[++ccnt] = (seg){u, v, k, b};
            }
            noww -= dd * k;
        }
        now -= kr[r] * (s[r] - s[r - 1]);
    }
    sort(c + 1, c + ccnt + 1, cmp3);
    for (int i = 1; i <= ccnt; i++) {
        addseg(1, 1, q, c[i].u, c[i].v, i);
    }
    dfs(1, 1, q);
    sort(e + 1, e + ecnt + 1, cmp2);
    for (int i = 2; i <= ecnt; i++) e[i].val = max(e[i].val, e[i - 1].val);for (int i = 1; i <= q; i++) {
        int l = 1, r = ecnt, mid, pos = -1;
        while (l <= r) {
            mid = (l + r) / 2;
            if (e[mid].x <= ask[i].d) l = mid + 1, pos = mid;
            else r = mid - 1;
        }
        if (pos != -1) {
            ans[ask[i].id] = max(ans[ask[i].id], e[pos].val);
        }
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << "\n";
    // for (int i = 1; i <= ecnt; i++) cout << e[i].x << " " << e[i].val << "\n";
    // for (int i = 1; i < cnt; i++) cout << kl[i] << " \n"[i == cnt - 1];
    // for (int i = 2; i <= cnt; i++) cout << kr[i] << " \n"[i == cnt];
    // auto end = chrono::high_resolution_clock::now();
     
    // auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    // cerr << "Time taken: " << duration.count() << " milliseconds" << endl;
    return 0;
}
