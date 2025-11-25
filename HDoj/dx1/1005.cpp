// Problem: 传送门
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1005
// Memory Limit: 262144 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// Problem: 传送门
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1005
// Memory Limit: 262144 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int int64_t
#define db long double
#define inf 0x3f3f3f3f
#define endl '\n'
#define rep(i, x, y) for(auto i = (x); i <= (y); i++)
#define gc getchar
#define x first
#define y second
#define eb emplace_back
#define em emplace
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
typedef long long ll;

inline int read() {
    int sum = 0, d = 1;
    char c = gc();
    while (c < '0' || c > '9') {
        if (c == '-') d = -1;
        c = gc();
    }
    while (c >= '0' && c <= '9') {
        sum = sum * 10 + c - '0';
        c = gc();
    }
    return sum * d;
}

inline int writeln(int arg) { return printf("%lld\n", arg); }

vector<vector<pii>> graph;

void solve() {
    int T = read();
    while (T--) {
        int n = read(), m = read();
        graph.assign(n + 1, vector<pii>());
        for (int i = 0; i < m; i++) {
            int u = read(), v = read(), c = read();
            graph[u].eb(v, c);
            graph[v].eb(u, c);
        }
        vector<unordered_map<int, int>> dist(n + 1);
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        for (auto& [v, c] : graph[1]) {
            if (!dist[1].count(c) || 1 < dist[1][c]) {
                dist[1][c] = 1;
                pq.emplace(1, 1, c);
            }
        }
        int ans = inf;
        while (!pq.empty()) {
            auto [cost, u, last_c] = pq.top();
            pq.pop();
            if (u == n) {
                ans = min(ans, cost);
                continue;
            }
            if (dist[u].count(last_c) && cost > dist[u][last_c]) {
                continue;
            }
            for (auto& [v, c] : graph[u]) {
                int new_cost = cost;
                if (c != last_c) {
                    new_cost += 1;
                }
                if (!dist[v].count(c) || new_cost < dist[v][c]) {
                    dist[v][c] = new_cost;
                    pq.emplace(new_cost, v, c);
                }
            }
        }

        writeln(ans);
    }
}

signed main() {
    solve();
    return 0;
}