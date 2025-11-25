// Problem: #6277. 数列分块入门 1
// Contest: LibreOJ
// URL: https://loj.ac/p/6277
// Memory Limit: 256 MB
// Time Limit: 100 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 50050;
int n, m, a[maxn], p[maxn], v[300], op, l, r, c;
void add(int l, int r, int c) {
    if (p[l] == p[r]) { // 说明在同一个分块，直接更新
        for (int i = l; i <= r; i ++) a[i] += c;
        return;
    }
    if (l % m != 1) {    // 说明l不是分块p[l]的第一个元素
        for (int i = l; p[i]==p[l]; i ++)
            a[i] += c;
    }
    else v[p[l]] += c;
    if (r % m != 0) { // 说明r不是分块p[r]的最后一个元素
        for (int i = r; p[i]==p[r]; i --)
            a[i] += c;
    }
    else v[p[r]] += c;
    for (int i = p[l]+1; i < p[r]; i ++)
        v[i] += c;
}
int main() {
    scanf("%d", &n);
    m = sqrt(n);
    for (int i = 1; i <= n; i ++) p[i] = (i-1)/m + 1;
    for (int i = 1; i <= n; i ++) scanf("%d", a+i);
    for (int i = 0; i < n; i ++) {
        scanf("%d%d%d%d", &op, &l, &r, &c);
        if (op == 0) add(l, r, c);
        else printf("%d\n", a[r] + v[p[r]]);
    }
    return 0;
}
