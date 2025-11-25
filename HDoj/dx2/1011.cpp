// Problem: 10010
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1011
// Memory Limit: 512000 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

inline string sread() {
    string str;
    char c = getchar();
    while (c == ' ' || c == '\n' || c == '\t') c = getchar();
    while (c != ' ' && c != '\n' && c != '\t' && c != EOF) {
        str += c;
        c = getchar();
    }
    return str;
}

// 计算 lowbit(x) 的指数 y（即 lowbit(x) = 2^y）
ll get_y(ll x) {
    if (x == 0) return -1;  // 实际上不会调用 x=0 的情况
    return __builtin_ctzll(x);  // 返回 x 末尾0的个数，即 lowbit 的指数
}

// 正确计算 f(x) 的函数
ll f(ll x) {
    if (x == 0) return 0;
    ll y = get_y(x);
    ll z = x / (1LL << (y + 1));  // x / (2^(y+1))
    if (z == 0) {
        return y;
    } else {
        return f(z) + (1LL << y);  // f(z) + 2^y
    }
}

inline void solve() {
    int n, m;
    n = read();
    m = read();																																																																																																																																																																																																																																																																																																																																																																																																																															
-/+
    string s = sread();
    
    for (int i = 1; i <= m; i++) {
        int opt = read();
        if (opt == 1) {
            int l = read();
            int r = read();
            // 提取子串并转换为整数
            ll x = 0;
            for (int j = l - 1; j < r; j++) {  // 注意索引转换（0-索引）
                x = (x << 1) | (s[j] - '0');
            }
            ll ans = f(x);
            printf("%lld\n", ans);
        } else {
            int x = read();
            // 修正字符翻转（注意索引转换）
            x--;  // 转换为0-索引
            if (s[x] == '0') s[x] = '1';
            else s[x] = '0';
        }
    }
}

int main() {
    int t = read();
    while (t--) solve();
    return 0;
}