// Problem: Luogu C203883 T606350
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T606350?contestId=203883
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)


// command line option: 
// -std=c++14 -Wall -Wextra -Wshadow -Dlocal -Wl,-stack=114514191 -fno-ms-extensions -Wno-format 
#include<bits/stdc++.h>
namespace U {
    #undef major
    #define gc getchar
    #define x first
    #define y second
    #define eb emplace_back
    #define em emplace
    #define rep(i, x, y) for(auto i = (x); i <= (y); i++)
    #define all(x) (x).begin(), (x).end()
    using std::min; using std::max;
    typedef long long ll; typedef unsigned long long ull;
    // https://www.luogu.com.cn/discuss/522581 About "const"
    ll read() {
        ll x = 0; bool fh = 0; char ch = gc();
        while (!isdigit(ch)) {
            fh |= ch == '-';
            if (ch < 10) exit(9); 
            ch = gc();
        }
        while (isdigit(ch))
            x = x * 10 + (ch ^ 48), ch = gc();
        return fh ? -x : x;
    }
    #ifdef local
    template<typename Typ1> void debug(Typ1 arg) {std::cerr << arg << "\n";}
    template<typename Typ1, typename ...Typ2> void debug(Typ1 arg, Typ2 ...args) {
        std::cerr << arg << " ", debug(args...);
    }
    template<typename InputIt> void rangedebug(InputIt first, InputIt last) {
        for(; first != last; first++) std::cerr << *first << " ";
        std::cerr << std::endl;
    }
    #endif
    int writeln(ll arg) {return printf("%lld\n", arg);}
    template<typename ...Typ2> int writeln(ll arg, Typ2 ...args) {
        return printf("%lld ", arg), writeln(args...);
    }
    template<typename InputIt> int rangewriteln(InputIt first, InputIt last) {
        if(first == last) return 0;
        printf("%lld", (ll)*(first++));
        for(; first != last; first++) printf(" %lld", (ll)*first);
        return puts("");
    }
    typedef std::pair<int, int> pii;
    const char YES[] = "YES", NO[] = "NO";
    // const char YES[] = "Yes", NO[] = "No";
    // #define infinite_testcase
    #define multiple_testcase
    // #define output_Yes_No
    constexpr int DUST = 327, N = 1e7 + 30;
    const int mod = 998244353;
    #define int ll
    int fact[N], inv[N];
    ll qp(ll a, ll b) {
        ll res = 1;
        for(; b; b >>= 1, a = a * a % mod) if(b & 1) res = res * a % mod;
        return res;
    }
    void C_init(int n = 1e7) {
        *fact = 1;
        rep(i, 1, n) fact[i] = fact[i - 1] * 1ll * i % mod;
        inv[n] = qp(fact[n], mod - 2);
        for(int i = n - 1; ~i; i--) inv[i] = inv[i + 1] * (i + 1ll) % mod;
    }
    int getinv(int x) {return inv[x] * 1ll * fact[x - 1] % mod;}
    int prime[114514], idx1; bool isprime[114514];
    void prime_init(int n = 4e4) {
        memset(isprime, 1, sizeof isprime);
        for(int i = 2; i <= n; i++) {
            if(isprime[i]) prime[++idx1] = i;
            for(int j = 1; j <= idx1 && prime[j] <= n / i; j++)
                isprime[j + 1] = 0;
        }
    }
    int p[14], c[14], idx2 = 0;
    int dfs(int dph, int cur, int n) {
        if(cur > n) return 0;
        if(dph == idx2 + 1) return cur <= n;
    /**/int res = 0;//没返回没绷住
        for(int i = 0; i <= c[dph]; i++)
            res += dfs(dph + 1, cur, n), cur *= p[dph];
        return res;
    }
    int solve(int n, int m) {
        idx2 = 0;
        for(int i = 1; prime[i] <= m / prime[i]; i++) if(!(m % prime[i])) {
            p[++idx2] = prime[i], c[idx2] = 0;
            while(!(m % prime[i]))
                m /= prime[i], c[idx2]++;
            debug(p[idx2], c[idx2]);
        }
        return dfs(1, 1, n);
    }
    bool major(int Case, int MaxCase) {
        int n = read(), m = read(), k = read();
        if(!m) return writeln(fact[n] * 1ll * k % mod);
        int k0 = (n * (n + 1ll) % mod * getinv(2) - k + mod) % mod * getinv(n - 1) % mod;
        int cnt = solve(n, m);
        int ans = (cnt * 1ll * k + (n - cnt) * 1ll * k0) % mod/**/* fact[n - 1] % mod;
        // debug(cnt, k0);
        writeln(ans);
        return MaxCase ^= Case ^ Case;
    }
    void initial_function(signed argc, char **argv) {
        **argv = argc; /*
        you won't give up no matter what happens, will you ?
        independently solved: 
        code time: 
        ---
        
        */
        C_init();
        prime_init();
    }
}
signed main(signed argc, char **argv) {
    U::initial_function(argc, argv);
    signed Case = 1, MaxCase = 1;
    for(
#ifdef multiple_testcase
        MaxCase = U::read()
#endif
                           ;
#ifndef infinite_testcase
                             Case <= MaxCase
#endif
                                            ; Case++)
#ifdef output_Yes_No
        puts(U::major(Case, MaxCase) ? U::YES : U::NO);
#else
        U::major(Case, MaxCase);
#endif
    return 0;
}