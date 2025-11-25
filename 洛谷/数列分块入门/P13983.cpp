// Problem: P13983 数列分块入门 8
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P13983
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, q, a[300005], kl[8005], kr[8005], bel[300005], pure[8005];
const int mod = 10007;
int ks, kc;
void BuildBlock() {
    kc = sqrt(n);
    ks = (n + kc - 1) / kc;

    for (int i = 1; i <= ks; i++) {
        kl[i] = kr[i - 1] + 1;
        kr[i] = kl[i] + kc - 1;
    }

    kr[ks] = n;

    for (int i = 1; i <= ks; i++) {
        for (int j = kl[i]; j <= kr[i]; j++)
            bel[j] = i;

        pure[i] = LLONG_MIN;
    }
}
void pdn(int u) {
    if (pure[u] == LLONG_MIN)
        return;

    for (int i = kl[u]; i <= kr[u]; i++)
        a[i] = pure[u];

    pure[u] = LLONG_MIN;
}
int qry(int l, int r, int c) {
    if (bel[l] == bel[r]) {
        pdn(bel[l]);
        int ans = 0;

        for (int i = l; i <= r; i++)
            ans += (a[i] == c);

        return ans;
    }

    pdn(bel[l]);
    pdn(bel[r]);
    int ans = 0;

    for (int i = l; i <= kr[bel[l]]; i++)
        ans += (a[i] == c);

    for (int i = kl[bel[r]]; i <= r; i++)
        ans += (a[i] == c);

    for (int i = bel[l] + 1; i < bel[r]; i++) {
        if (pure[i] != LLONG_MIN)
            ans += kc * (pure[i] == c);
        else
            ans += qry(kl[i], kr[i], c);
    }

    return ans;
}
void upd(int l, int r, int c) {
    if (bel[l] == bel[r]) {
        pdn(bel[l]);

        for (int i = l; i <= r; i++)
            a[i] = c;

        return;
    }

    pdn(bel[l]);
    pdn(bel[r]);

    for (int i = l; i <= kr[bel[l]]; i++)
        a[i] = c;

    for (int i = kl[bel[r]]; i <= r; i++)
        a[i] = c;

    for (int i = bel[l] + 1; i < bel[r]; i++)
        pure[i] = c;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    q = n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    BuildBlock();

    while (q--) {
        int l, r, c;
        cin >> l >> r >> c;
        cout << qry(l, r, c) << "\n";
        upd(l, r, c);
    }

    return 0;
}