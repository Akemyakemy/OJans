// Problem: Love Wins All
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/L
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int int64_t
#define inf 0x3f3f3f3f
#define endl '\n'
const int mod = 998244353;
const int maxn = 5e5 + 9;

inline int read() {
    int sum = 0, d = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') d = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum * d;
}

int t, n, a[maxn];
bool vis[maxn];
vector<int> cycles;

void init() {
    cycles.clear();
    fill(vis, vis + n + 1, false);
}

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = true;
    cycles.back()++;
    dfs(a[u]);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    t = read();
    while (t--) {
        n = read();
        init();
        for (int i = 1; i <= n; i++) a[i] = read();
        
        // 分解置换为环
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                cycles.push_back(0);
                dfs(i);
            }
        }
        
        // 统计环的类型
        int odd = 0, even = 0, cnt2 = 0;
        bool invalid = false;  // 标记是否有三个奇数环
        for (int siz : cycles) {
            if (siz % 2 == 1) {
                odd++;
                if (odd >= 3) {
                    invalid = true;
                    break;  // 跳出循环
                }
            } else if (siz > 2) {
                even++;
            } else {
                cnt2++;
            }
        }
        
        // 如果无效，直接输出0并继续下一组数据
        if (invalid) {
            cout << 0 << endl;
            continue;
        }
        
        // 计算答案
        int ans = 1;
        if (odd == 2) {
            // 情况1：存在两个奇数环
            for (int siz : cycles) {
                if (siz % 2 == 1) {
                    ans = ans * siz % mod;
                }
            }
            for (int i = 0; i < even; i++) {
                ans = ans * 2 % mod;
            }
        } else {
            // 情况2：没有奇数环
            ans = 0;
            for (int siz : cycles) {
                int res = 0;
                for (int i = 1; i * 2 <= siz; i += 2) {
                    if (i * 2 == siz) {
                        res += siz / 2;
                    } else {
                        res += siz;
                    }
                }
                if (siz == 2 && even) {
                    res *= 2;
                }
                ans = (ans + res) % mod;
            }
            for (int i = 0; i < even - 1; i++) {
                ans = ans * 2 % mod;
            }
        }
        cout << ans << endl;
    }
    return 0;
}