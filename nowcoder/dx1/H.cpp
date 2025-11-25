// Problem: Symmetry Intervals 2
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108298/H
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <cstdio>
#include <vector>
using namespace std;
typedef unsigned long long ull;
const int N = 1e6 + 5;
int n, q, L[65536], R[65536];
ull Val[N], Cnt[65536];
bool F[N];
char s[N];
inline ull Bit(int l, int r) {
    return (r == 63 ? -1ull : (1ull << (r + 1)) - 1) ^ ((1ull << l) - 1);
}
inline void update(ull u, unsigned &rr, ull &ret) {
    ret += Cnt[u] + rr * L[u];
    rr = R[u] == 16 ? rr + 16 : R[u];
}
struct Bitset {
    int sz, ptr;
    vector<ull> vec;
    Bitset(int _sz = 0) {
        sz = _sz;
        ptr = 0;
        vec.resize((_sz + 63) >> 6);
    }
    void add(int cnt, ull val) {
        if (cnt <= 64 - (ptr & 63)) vec[ptr >> 6] |= val << (ptr & 63);
        else {
            vec[ptr >> 6] |= (val & Bit(0, 64 - (ptr & 63) - 1)) << (ptr & 63);
            vec[(ptr >> 6) + 1] |= val >> (64 - (ptr & 63));
        }
        ptr += cnt;
    }
    void same(const Bitset &u) {
        for (unsigned i = 0; i < vec.size() - 1; i++)
            vec[i] ^= ~u.vec[i];
        if (!(sz & 63)) vec[vec.size() - 1] ^= ~u.vec[vec.size() - 1];
        else vec[vec.size() - 1] ^= u.vec[vec.size() - 1] ^ Bit(0, (sz - 1) & 63);
    }
    ull cal() const {
        ull ret = 0;
        for (unsigned i = 0, rr = 0; i < vec.size(); i++) {
            update(vec[i] & 65535, rr, ret);
            update(vec[i] >> 16 & 65535, rr, ret);
            update(vec[i] >> 32 & 65535, rr, ret);
            update(vec[i] >> 48 & 65535, rr, ret);
        }
        return ret;
    }
};
Bitset Get(int l, int r) {
    Bitset ret(r - l + 1);
    if ((l >> 6) == (r >> 6)) ret.add(r - l + 1, (Val[l >> 6] & Bit(l & 63, r & 63)) >> (l & 63));
    else {
        ret.add(63 - (l & 63) + 1, (Val[l >> 6] & Bit(l & 63, 63)) >> (l & 63));
        for (int i = (l >> 6) + 1; i < (r >> 6); i++) ret.add(64, Val[i]);
        ret.add((r & 63) + 1, Val[r >> 6] & Bit(0, r & 63));
    }
    return ret;
}
int main() {
    for (int i = 0; i < 65536; i++) {
        for (int j = 0; j < 16; j++) {
            if (i & (1 << j)) L[i]++;
            else break;
        }
        for (int j = 15; j >= 0; j--) {
            if (i & (1 << j)) R[i]++;
            else break;
        }
        for (int j = 0, tot = 0; j < 16; j++) {
            if (i & (1 << j)) Cnt[i] += ++tot;
            else tot = 0;
        }
    }
    scanf("%d%d%s", &n, &q, s);
    for (int i = 0; i < n; i += 64)
        for (int j = 0; j < 64 && i + j < n; j++)
            Val[i >> 6] |= ull(s[i + j] - '0') << j;
    int opt, l, r, a, b;
    while (q--) {
        scanf("%d%d", &opt, &l);
        if (opt == 1) {
            scanf("%d", &r);
            l--, r--;
            if ((l >> 6) == (r >> 6)) Val[l >> 6] ^= Bit(l & 63, r & 63);
            else {
                Val[l >> 6] ^= Bit(l & 63, 63);
                Val[r >> 6] ^= Bit(0, r & 63);
                F[(l >> 6) + 1] ^= true;
                F[r >> 6] ^= true;
            }
        }
        else {
            for (int i = 0, pre = 0; (i << 6) < n; i++) {
                pre ^= F[i];
                if (pre) Val[i] ^= -1ull;
                F[i] = false;
            }
            scanf("%d%d", &a, &b);
            a--, b--;
            Bitset u = Get(a, a + l - 1), v = Get(b, b + l - 1);
            u.same(v);
            printf("%lld\n", u.cal());
        }
    }
    return 0;
}
