// Problem: Luogu C203883 T616958
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T616958?contestId=203883
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
    // #define multiple_testcase
    // #define output_Yes_No
    constexpr int DUST = 327, N = 514514;
    int head[N], to[N << 1], ne[N << 1], idx1 = 0;
    void add(int u, int v) {
        to[++idx1] = v, ne[idx1] = head[u], head[u] = idx1;
    }
    int n, k; ll ans2;
    int /*dphcnt[N], */mxdph;
    int subtreemxdph[N];
    void dfs0(int u, int dph, int f) {
        subtreemxdph[u] = dph;
        for(int i = head[u]; i; i = ne[i]) /**/if(to[i] != f) {
            dfs0(to[i], dph + 1, u);
            subtreemxdph[u] = max(subtreemxdph[u], subtreemxdph[to[i]]);
        }
    }
    bool tag[N];
    void dfs(int u, int dph, int f) {
        int soncnt = 0;
        for(int i = head[u]; i; i = ne[i]) if(to[i] != f) {
            soncnt++;
            dfs(to[i], dph + 1, u);
        }
    /**/if(dph == mxdph);//啥事不用管，不特判会进下面一行给 ans2 加爆
        else if(subtreemxdph[u] == mxdph) ans2 += k - soncnt;//触底救不了
        else // 今天无论如何也要给 u 打上 tag
        if(soncnt) {//没触底（极值）的救不了，tag在那放着
            ans2 += k - soncnt;//没来的救不了必须全剪
            for(int i = head[u]; i; i = ne[i]) if(to[i] != f) {
                int v = to[i];
                if(tag[v]/**/&& subtreemxdph[v] /*!= 继续唐，*/== subtreemxdph[u])
                    tag[u] = 1, tag[v] = 0;
            }
            assert(tag[u]);
        }
        else /*if(dph != mxdph)*/ tag[u] = 1;
    }
    bool major(int Case, int MaxCase) {
        n = read(), k = read();
        rep(i, 1, n - 1) {
            int u = read(), v = read();
            add(u, v), add(v, u);
        }
        dfs0(1, 0, -1);
        mxdph = subtreemxdph[1];
        dfs(1, 0, -1);//主函数没 dfs 小丑了
        // rep(i, 1, mxdph)
            // ans2 += dphcnt[i - 1] * 1ll * k - dphcnt[i];
        ans2 += std::accumulate(tag + 1, tag + n + 1, 0);
        writeln(mxdph, ans2);
        return MaxCase ^= Case ^ Case;
    }
    void initial_function(signed argc, char **argv) {
        **argv = argc; /*
        you won't give up no matter what happens, will you ?
        independently solved: 
        code time: 15：15~16：12
        ---
        哎呀不wa还不知道自己算法假了）
        hack:
5 2
1 2
2 3
3 4
1 5
ans: 3 3. 没有考虑提前删的情况而输出 3 4
        
        15：40：对于有son但不满 k 的节点，直接在最后减。
        否则，对于没有son的节点（且深度不是全局最大，比如上例 5 号），
        只需要（不是在最后）减一次就行，打上标记。
        如果一个节点的所有孩子（不需要满k个）都有标记，那么标记可以上移；
        当然，如果一个点子树内节点没有reach父亲的子树内深度最大，比如
            1    
         2  3  4 
        345---678
        （但全局深度大于 3）
        那么 345678 标记上移给 2和4，而3虽然有标记但是得 1 剪一次之后再剪所以标记不能上移
        最后标记就是 1 和 3，剪 2 次
        
        啥？60pts？开始怀疑没开ll了
        哦，我唐，算法想好结果代码没敲上去
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