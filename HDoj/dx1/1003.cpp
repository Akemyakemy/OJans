// Problem: 奸商
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1003
// Memory Limit: 262144 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1003
// Memory Limit: 262144 MB
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
    constexpr int DUST = 327, N = 3145;
    int ww[19];
    char s[N];
    using namespace std;
    bitset<17> req[N]; int idx1 = 0;
    void get(int l, int r) {
        bitset<17> ret(0);
        while(l <= r) {
            if(s[l] != s[r]) ret.set(min(s[l], s[r]) - 'a');
        /**/else return;
            l++, r--;
        }
        // return ret;
        req[idx1++] = ret;
    }
    bool chk(int st) {
        bitset<17> ret(st);
        for(int i = 0; i < idx1; i++) if((ret & req[i]).none()) return 0;
        return 1;
    }
    bool major(int Case, int MaxCase) {
    /**/idx1 = 0;
        int n = read(), len;
        scanf("%s", s + 1);
        rep(i, 0, 16) ww[i] = read();
        len = read();
        if(len & 1) len++;
        for(int l = 1, r = len; r <= n; l++, r++)
            get(l, r);
        // for(int l = 1, r = len + 1; r <= n; l++, r++)
            // req[idx1++] = get(l, r);
        // for(int i = 0; i < idx1; i++) debug(req[i]);
        int ans = 1e9;
        for(int st = 0; st < 1 << 17; st++) if(chk(st)) {
            int ret = 0;
            rep(i, 0, 16) if(st >> i & 1) ret += ww[i];
            ans = min(ans, ret);
        }
    /**/if(len > n) ans = 0;
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