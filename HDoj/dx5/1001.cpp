#define QwQ 0

//#include<iostream>
//#include<iomanip>
//#include<string>
//#include<sstring>
//#include <vector>        // 动态数组
//#include <list>          // 双向链表
//#include <deque>         // 双端队列
//#include <stack>         // 栈 (LIFO)
//#include <queue>         // 队列 (FIFO) 及优先队列
//#include <set>           // 有序集合 (红黑树)
//#include <map>           // 有序映射 (红黑树)
//#include <unordered_set> // 无序集合 (哈希表)
//#include <unordered_map> // 无序映射 (哈希表)
//#include <algorithm>     // 常用算法 (sort, find, reverse, max_element)
//#include <numeric>       // 数值算法 (accumulate, iota)
//#include <functional>    // 函数对象 (greater, less, bind)
//#include <cmath>         // 数学函数 (sqrt, sin, cos, exp, log)
//#include <complex>       // 复数运算
//#include <random>        // 随机数生成 (C++11及以后)
#include<bits/stdc++.h>
using namespace std;
#define boost ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
// #define int int64_t
#define db long double
#define endl '\n'
#define rep(i, x, y) for(auto i = (x); i < (y); i++)
#define gc getchar
// #define x first
// #define y second
#define eb emplace_back
#define em emplace
#define all(x) (x).begin(), (x).end()
#define pii pair<int,int>
typedef long long ll;
typedef unsigned long long ull;
#define lowbit(x) ((x)&(-x))// 直接 (x)&(-x) 容易出现问题
#define  bp(x) __builtin_popcountll(x)
using i128 = __int128_t;

// inline int read(){//手动读取数字更加快速
    // int sum=0,d=1;
    // char c=gc();
    // while(c<'0'||c>'9'){
        // if(c=='-')d=-1;
        // c=gc();
    // }
    // while(c>='0'&&c<='9'){
        // sum=sum*10+c-'0';
        // c=gc();
    // }
    // return sum*d;
// }
// inline int writeln(int arg) {return printf("%lld\n", arg);}
// inline string sread() {
    // string str;
    // char c = gc();// 跳过前导空白符（空格、换行、制表符）
    // while (c == ' ' || c == '\n' || c == '\t') c = gc();// 读取非空白字符，直到遇到空白符或EOF
    // while (c != ' ' && c != '\n' && c != '\t' && c != EOF) {
        // str += c;
        // c = gc();
    // }
    // return str;
// }
/*int pow_mod(int a, int b) {// 快速幂计算逆元
    int res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}*/
//const int mod=;
//const int N=NeM+10;
//const db eps=1e-;
// const int inf=0x3f3f3f3f3f3f3f3f;
// #define brute
// #define debug
struct query{
    int id;
    int x;
    ll y;
};
struct Dsu{
    vector<int> p;
    vector<ll> sum_b;
    vector<int> sz;
    Dsu(int n,const vector<ll>& b_vals){
        p.resize(n+1);
        iota(all(p),0);
        sum_b.assign(n+1,0);
        sz.assign(n+1,1);
        for(int i=1;i<=n;++i){
            sum_b[i]=b_vals[i];
        }
    }
    int find(int i) {
        if(p[i]==i) return i;
        return p[i]=find(p[i]);
    }
    void unite(int i,int j){
        int root_i=find(i);
        int root_j=find(j);
        if(root_i!=root_j){
            if(sz[root_i]<sz[root_j]) swap(root_i,root_j);
            p[root_j]=root_i;
            sz[root_i]+=sz[root_j];
            sum_b[root_i]+=sum_b[root_j];
        }
    }
};

inline void solve(){
#ifdef brute
	
#else
    int n, q;
    cin>>n>>q;
    vector<ll> a(n+1),b(n+1);
    for(int i=1;i<=n;++i) cin>>a[i];
    for(int i=1;i<=n;++i) cin>>b[i];
    vector<vector<int>> adj(n+1);
    for(int i=0;i<n-1;++i) {
        int u,v;
        cin >>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<query> qs(q);
    for(int i=0;i<q;++i){
        qs[i].id=i;
        cin>>qs[i].x>>qs[i].y;
    }
    vector<ll> ans(q);
    vector<pair<ll,int>> sorted_nodes(n);
    for(int i=1;i<=n;++i){
        sorted_nodes[i-1]={a[i],i};
    }
    sort(sorted_nodes.begin(),sorted_nodes.end());
    vector<pair<ll, int>> sorted_queries(q);
    for(int i=0;i<q;++i){
        sorted_queries[i]={qs[i].y,i};
    }
    sort(sorted_queries.begin(),sorted_queries.end());
    Dsu dsu(n,b);
    int node_ptr=0;
    vector<bool> visited(n+1);
    for(const auto& q_event:sorted_queries){
        ll y = q_event.first;
        int q_id=q_event.second;
        int x=qs[q_id].x;
        while(node_ptr<n && sorted_nodes[node_ptr].first<=y){
            int u=sorted_nodes[node_ptr].second;
            for(int v:adj[u]){
                if(a[v]<=a[u]){
                    dsu.unite(u,v);
                }
            }
            node_ptr++;
        }
        ll current_y=y;
        if(current_y<a[x]) {
            ans[q_id]=y;
            continue;
        }
        fill(visited.begin(),visited.end(),false);
        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq;
        int root=dsu.find(x);
        current_y+=dsu.sum_b[root];
        queue<int> q_bfs;
        q_bfs.push(x);
        visited[x]=true;
        while(!q_bfs.empty()){
            int u=q_bfs.front();
            q_bfs.pop();
            for(int v:adj[u]){
                if(!visited[v] && dsu.find(v)==root){
                    visited[v]=true;
                    q_bfs.push(v);
                }
            }
        }
        for(int u=1;u<=n;++u){
            if(visited[u]){
                for(int v:adj[u]){
                    if(!visited[v] && a[v]>a[u]){
                        pq.emplace(a[v],v);
                    }
                }
            }
        }
        while(!pq.empty()){
            auto [req_level, u]=pq.top();
            pq.pop();
            if(visited[u]) continue;
            if(req_level > current_y) break;
            int u_root = dsu.find(u);
            current_y += dsu.sum_b[u_root];
            q_bfs.push(u);
            visited[u] = true;
            while(!q_bfs.empty()){
                int v = q_bfs.front();
                q_bfs.pop();
                for(int w:adj[v]){
                    if(!visited[w] && dsu.find(w)==u_root){
                        visited[w]=true;
                        q_bfs.push(w);
                    }
                }
            }
            for(int v=1;v<=n;++v){
                if(visited[v]){
                    for(int w:adj[v]){
                        if(!visited[w] && dsu.find(w)!=u_root){
                            pq.emplace(a[w],w);
                        }
                    }
                }
            }
        }
        ans[q_id]=current_y;
    }
    for(ll val:ans){
        cout << val << '\n';
    }
#endif
}
signed main(){
	boost;
	int t;cin>>t;
	while(t--)
	solve();
	return QwQ;
}
/*
																				created by versus0
									                        __            __      __                                                   ______ 
									.----.----.-----.---.-.|  |_.-----.--|  |    |  |--.--.--.    .--.--.-----.----.-----.--.--.-----.|      |
									|  __|   _|  -__|  _  ||   _|  -__|  _  |    |  _  |  |  |    |  |  |  -__|   _|__ --|  |  |__ --||  --  |
									|____|__| |_____|___._||____|_____|_____|    |_____|___  |     \___/|_____|__| |_____|_____|_____||______|
									                                                   |_____|                                                
										                                                   
										                                                   
                                                                   .<?;^^^^^^^^```````I?[[[[[[[[[[[]\r.                                                                                                     
                                                                  `{+^`^^",;I!i<~~~~><{{}[]][[[[[[[[]z;                                                                                                     
                                                                 '|>':l>>>!lI;;:;;Ili<_[)\/(}]][[[[[]z)+]{|/jxxxnnxrjf/\((){]?_~iI:"`.                                                                      
                                                                 >)!<!:^.          .^;>-)jJwUj)][[[[}LccYJXvxf/\||(((((((|\\//tjjrrxxxrt([+!,'                                                              
                                                               . <xI.        ^l_1tnvnjt(1[_+~-fn{][]rx-]]???]]]]]?-_+<>i!lII;;;;;;Il!>~-[)\jnxf|[<,'                                                        
                                                                 ';    .,<{fnnj|]<!!!>+_?][[[[])z){/t}{{}[}}}}]-+<ilI;:,"^^^^^^^^^^^^^^````^";!+{/rr\[>".                                                   
                                                                   `![fvut}<:`. ':!<++_-?][[[{(tnncx/|)}]-_+<>i!lIII;;:::"^^^^^^^^^^^^^^^^^^^^^```^:i?)/\}<:.                                               
                                                               'l1nXu(+:' ..'``^^^^^^^^"",:I!><+_+<!l;:,""^^^^`````^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^``^:>](([i^                                            
                                                            ^<|vv|<". .'`^^^^^^^^^^^^^^^^^^^^^^^^^`^^^^^^^^^^";l!l;,^^^^^^^^^^^^^^^^^^^^"^^^^^^^^^^^^^^^^^``:<{/(+"                                         
                                                         ^<)f|_:. .'`^^^^^^^`^;><<>,^^^^^^^^^^^^^^^^^^^^^^^^^"i~_-?]?-<I"`^^^^^^^^^^^^^^"",,"^^^^^^^^^^^^^^^^``"!}/)<`                                      
                                                      '!}([!^...'`^^^^^^^`">}()?>I:"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^,;i+[11-l^`^^^^^^^^^^^^^^":::"^^^^^^^^^^^^^^^^^`^i)t{I.                                   
                                                    :-{-I'..''`^^^^^^^`"!{j\_I"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^:i?))+"`^^^^^^^^^^^^^^",;;,^^^^^^^^^^^^^^^^^^`,-tf_`                                 
                                                 '![[!`..'''^^^^^^^^^:+11+:``^^^^^:,^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^`"!}(-,^^^^^^^^^^^^^^^^";I:^^^^^^^^^^^^^^^^^^^,~/n}"                               
                                               `_|[;..'''`^^^^^^^^^I_?<:``^^^^^^^!l^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^`,<?>,^^^^^^^^^^^^^^^^";l:^^^^^^^^^^^^^^^^^"Il!\v}^                             
                                             ^1n{;..''`^^^^^^^^^^I~<;``^^^^^^^^^<!^^^^^^^^^^"^^^^^^^^^^^^^^^^,,^^^^^^^^^^^^^^^`^I>!"^^^^^^^^^^^^^^^^";l:^^^^^^^^^^^^^^^^^l+Ilfu-'                           
                                           `{z|:..''`^^^^^^^^^^;>!"`^^^^^^^^^^^<!^^^"^""^^^""^^^^^^^^^^^^^^^^^l"^^^^^^^^^^^^^^^^^^;!;^^^^^^^^^^^^^^^^^"l!"^^^^^^^^^^^^^^^^:?+,~nf!                          
                .                     .. .-u|: .''`^^^^^^^^^^,il"`^^^^^^^^^^^^!!`^^,:^,,^^^:^^^^^^^^^^^^^^^^^^,l^^^^^^^^^^^^^^^^^^^^;l,^^^^^^^^^^^^^^^^^:!I^^^^^^^^^^^^^^^^,-[!"{c1`                        
                 ''                     lj/; .''`^^^^^^^^^^^;!,^^^^^^^^^^^^^^;>^^^^l,^;,^^";^^^^^^^^^^^^^^^^^^^l;^^^^^^^^^^^^^^^^^^^^"I:^^^^^^^^^^^^^^^^^^li"^^^^^^^^^^^^^^^,-}-,!xnl                       
             . .,il.                  '{r<..'''^^^^^^^^^^^^";^^^^^^^^^^^^^^^"<"^^^">^^l"^^,;^^^^^^^^^^^^^^^^^^^">^^^^^^^^^^^^^^^^^^^^^^:;"^^^^^^^^^^^^^^^^^:>;^^^^^^^^^^^^^^^:]}[i"(Y_  .                   
              'l>>>` .               lj1^.'''`^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^!l^^^^,>^^i"^^I:^^^^^^^^^^^^^^^^^^^^l;^^^^^^^^^^^^^^^^^^^^^^"l,^^^^^^^^^^^^^^^^^">!^^^`^^^^^^^^^^^l[[}_^?Y}.                    
    .'...   .,i>>>>" ..             ]n<..'''^^^^^^^^^^^^":^^^^^^^^^^^^^^^^^,<^^^^^;i^^>"^^i:^^^^^^^^^^^^^^^^^^^^,>^^^^^^^^^^^^^^^^^^^^^^^"!:^^^^^^^^^^^^^^^^^^!>^^^^^^^^^^^^^^^~}[}?,>X|.                   
    .;i!l;:"I>>>>>>:            . `\f,.'''`^^^^^^^^^^^^^l:^^^^^^^^^^^^^^^^`>l^^^^^;i^^<,^^<,^^^^^^^^^^^^^^^^^^^^^>,^^^^^^^^^^^^^^^^^^^^^^^^i;^^^^^^^^^^^^^^^^^^l<^^^^^^^^^^^^^^:][[}[;IXj' .                
     .,i>>>>>>>>>>>!I;,"^'       "x)'.'''`^^^^^^^^^^^^^!:^^^^^^^^^^^^^^^^^!{^^^^^^;i^^<;^"+,^^^^^^^^^^^^^^^^^^^^^ll^^^^^^^^^^^^^^^^^^^^^^^^^>I^^^^^^^^^^^^^^^^^^l~^^^^^^^^^^^^^^<}[[[[;:Jf.                 
       'l>>>>>>>>>>>>>>iI^.  .  ;u?.''''`^^^^^^^^^^^^^i;^^^^^^^^^^^^^^^^^;(-`^^^^^:>^^>!`,+"^^^^^^^^^^^^^^^^^^^^^:i^^^^^^^^^^^^^^^^^^^^^^^^^^<;^^^^^^^^^^^^^^^^^^l+^^^^^^""^^^^^:][[[[[;;Q)                 
      .^l>>>>>>>>>>>>i:'     . Ic+ ''''`^^^^^^^^^^^^^!l^^^^^^^^^^^^^^^^^,-fl^^^^^^"<^^;_`,_"^^^^^^^^^^^^^^^^^^^^^"I^^^^^^^^'..'`^^^^^^^^^^^^^"_:^^^^^^^^^^^^^^^^^`i~^^^^^^;:^^^^^~[[[[[[:iO_                
    ."l><>>>>>>>>>>!iiil".    ;v~ ''''`^^^^^^^^^^^^^;>^^^^^`'.'^^^^^^^^^<}r"^^^^^^^~,^"]",_,^^^^^^^^^^^^^^^^^^^^^`<:^^^^^^^'....`^^^^^^^^^.'^^:]"^^``^^^^^^^^^^^^^`+>`^^^^"+:^^^^l[[[[[[]^]Q;               
   ';!l;:,",i>>>>>:..''''.   ,n~ ``''`^^^'`^^^^^^^^"<"^^^^`...'^^^^^^^^l{Uv'^^^^^^^i!^^~!"+,^^^^^^^^^^^''`^^^^^^^`]-'^^^^^^^`'..'^^^^^^^^^^`^^`~{`^^^^^^^^^^^^^^^^^^?;`^^^^i-"^^^:][[[[[}-`fz'              
   ...      ^!>>>i`         `j_ ^"''`^^^^^^^^^^^^^^>I`^^^`...'`"^^^^^^"\Laj'^^^^^^^:_^^:?^~:`'''^^^^^^`...`^^^^^^`-X^^^^^^^^^^^``^^^^^^^^^^^^^^`j~`^^^^^^^^^^^^^^^^^:},^^^^,]~^^^"_[[[[[[}~"U}              
             'l><;         .\].`:''`^^^^^^^^^^^^^^:_^^^^^`'''^^^^^^^^`{pLJ|'^^^^^^^^+;^`-!>;^'..^^^^^^^'''^^^^^^^`<d['^^^^^^^^^^^^^^^^^^^^^^^^^`>v"^^^^^^^^^^^^^^^^^`~1,^^^^~[!^^^~}[[[[[[}!<J"             
              .:I' .       ]{.';`'`^^^^^^^^^^^^^^`+i`^^^^^^^^",^^^^^`~kC_z)'^^^^^^^^;_^^:}il^^`^^^^^^^^^^^"^^^^^^`<dL;`^^^^^^^^^^^^^^^^^^^^^^^^^^f1'^^^^^^^^^^^^^^^^^^)]"^^^l[?:^^>}[[[[[[[],j)             
            ...   .       i|`.;:.`^^^^^^^^^^^^^^^:{,^^^^^^^^^I"^^^^^,ZL-+v('^^^^^^^^`_l^^~{!^^^^^^^^^^^^^^^^^^^^^`+OYj`^^^^^^^^^^^^"^^^^^^^^^^^^`+X;^^^^^^^^^^^^^^^^^`!t~"^^:?[~^^i}[[[[[[[}_!u"            
                         ^\:.^i''^^^^^^^^^^^^^^^`+?^^^^^^^^^:I^^^^^'n0-__r/'^^^^^^^^^,?"^^)]^^^^^^^^^^^^^^^^^^^^^`~C]C?'^^^^^^^^^^^:"^^^^^^^^^^^^lx1'^^^^^^^^^^^^^^^^^`(1>^^"-[];^![[[[[[[[[}l(]            
                      . .{+.'>,.^^^^^^^^^^^^^^^^^)>`^^^^^^^^>"^^^"']m[_-_\j'^^^^^^^^^^i~^^:/l`^^^^^^^^^^^^^^^^^^"`+Y+1UI`^^^^^^^^^^,I^^^^^^^^^^^^;{v"^^^^^^^^^^^^^^^^^`>t]I^^_[[~^l[[[[[[[[[[->j.           
                        >1'',<.`^^^^^^^^^^^^^^^^!\l^^^^^^^^;~`^^^^;Q|+--_{u`^^^^^^^^^^^+l^^l[^^^^^^^^^^^^^^^^^^^^`-v__\c:`^^^^^^"""^!"^^^^^^^^^^^:?u<`^^^^^^^^^^^^^^^^^"t}-"^+[[]:l[[[[[[[[[[[lt!           
                       `/;.'<,'^^^^^^^^^^^^^^^^`])I^^^^^^^`_!^^^^'ju+-----v:^^^^^^^^^^^"_:^^!+^^^^^^^^^^^^^^^^^^^`}f_-_/x,^^^^^""""^Ii`^^^^^^^^^^:?\|'^^^^^^^^^^^^^^^^^`})[<^+[[[i![[[[[[[[[[[+])           
                       [?.'"+'`^^^^^^^^^^^^^^^^^(};^^^^^^^"t,^^^`+Y_-----_x~`^^^"^^^^^^^,_,^^i~^^^^^^^^^^^^^^^^^^`1(_--_|j:`"""^""""^?,^^^^^^^^^^;][r"^^^^^^^^^^^^^^^^^`>/]]:_[[[-<[[[[[[[[[[[]~x^          
                      :f^'.<!.^^^^^^^^^^^^^^^^^:/];^^^^^^`_j`^^^"c1_-----_)('^^^!"^^^^^^^;_,^^i+^^^^^^^^^^^^^!:^"`([_-_-_)jI`"""""""^+\`^^^^^^^"^l]?x!^^^^^^^^^^^^^^^^^^;t][_?[[[]][[[[[[[[[[[[+v~          
                   .. (_.'`1^`^^^^^^^^^^^^^^^^^!/]I^^^^^^`c|'^"`}n+----~I-?j,^^^+i^^^^^^"^;_,^^!_"^^^^"^""""`}i^^"\?-+;+?_}r<`""""""^^X\:lI,^^""^~]?t_`^^^^^^^^^"^^^^^^^"j[][[[[[[[[[[[[[[[[[[}_x/          
                     ;f^''<|.^^^^^^^^^^^^^^^^^`~\]l^^^^^`<p(""^:c]_---_:'!_/+`^`+('^""""""^:_;^^l_,^""""""""`u-`^;\_-!'"<?_]f]^^""^":;(hn"^""""^:?]?|}`^^""^^^^^^^^^"""^"n{][[[[}[[[[[[[[[[[[[[-tz.         
                   . 1-''"t].^^^^^^^^^^^^^^^^^`-(]i^^^^^^vk1:!;)r+----!''^<}|^^^lX:^"""""""^,+!^^;-I^""""""^,Z{`^>\__,''^!--_\(;^;li!;;UCx:`"""^>]??)(`""""""""""^^"""^"^v|][[[]1[[[[[[[[[[[[[[?\Q"         
                    "f,'`<z>'^^^^^^^^^^^^^^^^^`[(]+^^""`?mn['"IJ\]-_-~^``'"+/>^^"U\`""""""""^^>~:`,_i^"""""^+p{`^[(_i````',>_?tv}l:,""^}f|ri^"^l???-{\`"""""""""""""""""^zn[[[[[1{[[[[[[[[[[[[[](Zl         
                    ?}'':(Q;`^^^^""^^^^^^^^^^^`{)??,^"^"U/){`^iz?1(1?,'````:]/^"`jw>^"""""""""^;+>"^>+:^"""^(L}^^t}+,`'''^l-|\(}((l^,,,:f-]t]";-?---}\`^"""""""""""""""^"YJ(][[[{)][[[[[[[[[[[[]tp+         
                   'f;'`~c0"^^^^^:,^^^^^^^^^^^`{)?]l^"`)v+1)``{/+_-}]<!,'''`,/+^^_bU;^"""""""""""i?<^;_!"",:ju{`In_;'^l-(t(~,`,>+}t}:","-|_-(/[__--_[|`""""""""""""""""^lLCx][[[[([[[[[[[[[[[[[]/b1         
                   ~|'`:}qJ^^^^^^I:^^^^"""""""`})-]+"^>X?_[\^^\]_-->`"!?[_I^.:f:^:YYv"""""""","""",?r_;>_I^-jY|;(v1)fx/[i^.'`^^^,I>{/_,",\>~_]/|_+__[)^""""""""""""""""^+0UX1][[[(}[[[[[[[[[[[[[}mf  .      
                   \>'`>x*c`^^^^^l;^^^"""""""^`?)-??;"v)_-?\,:t_--+^'''',~1/|?)/``((xr"",,,,,,,,,,"^_1[?+[-/_Y/)Ovu\<,^";l!!llIII;l<}nv-I}{l+]]|r{~+}[^"""""""""""""""",{mZCf][[[){][[[[[[[[[[[[_Lz  .      
                  ,t^^,]Z*x'^^^^^Il^^^""""""^^`+(_-?</u_++l}li|~+~"^""^^`''">{fCr])z{/f;",,,,,,,,,,,"<!;>+{n{n+{f::l>++_-}(jvUQwka*#MMMMO|qhhakpCLn+}+^"""",""""""""""^itY/CC[[[[1)][[[[[[[[[[[}~vO`        
                  -}'`ljZQ/'^^^^^;i^^"""""""""^i(__+10vYJJxv]?Uuuf11{]_~>ilI:,^"\\~r)<}/i",,::,:,,,:,,~i":]_>\>t~:-{/z0qoW&M*ohhoaaaaaaoWhpvYwaM*bamv<^^"""",""""""""":?nv:'\z][[{(][[[[[[[[[[[}>1p; .      
                . \!`^_0(U\'^^^^^,<^""""""""^"^;(_]{OooWW8W#zfMMM###*oabwQzf1?+~<({+f_,:]_:,::,:,:::::,>>)],"-+~'~xJCzxo*wwmZZZZZZZZZZZZmh&t!~?\XqoWhj(]!;,",,,,""""""+[zfc?.tj][}(][[[[[[[[[[[}<lq- .      
                 ^f"^"|Q"0t'^^^^^^~,""""""""""""/\(Y#o&*C\}]/Y1/odqppdkhao#MW*qX\+_]}<'`'>[!,:::::::::::]\,'l}_',>!lil{x!:|YLQ000O00OOOOOOkb+~<>><}Zm+Xc->,,,,,,"""""i})v+[z~,u[[}([[[[[[[[[[[[[?^zj        
                 <|`^IY(.mr'^^^^^^!l^""""""""""^{??b&hv?><++<x+cp[uOO000OO0OZmwCkx?;>};``',_-l,:::::::,lll?,[?```''":"_`'"'{YJCCCwCJCCLQU/Q*-:i<~~!YU)),"",,,,,,,"""l[]uu+_{('/1[[([[[[[[[[[[[[[}I+Q^       
                 )_``_Q,^qc`^^^^^^">^""""""""""^<[u8q]!<+~!"'">f<  l|LCCLwCJCCCCmJ>"',;```'';+-I,::::l!:,,!|}''````'.'0XcXuUUYXYQp0YzXYUUXJd_ '^;!1w(I^",,,,",,,,""I][{Yn_-]{'|{[[|[[[[[[[[[[[[[[-^Y[       
                .tI``/r ;dQ"^^^^^^^I,"""""""""""lfCk1!<~l^..'..Yn<{[/UXXzmmYXzXXXQ1^````````.!?~+l:;<</)~!l!<!`'````.'OmXXzcvuxrxCrjxuvcczYw!.''.~Uc"",,,,,,,,,,,"l][1ju]-_]~"t[[[(}[[[[[[[[[[[[1}l_U'      
                ^f"^^v~ ikql`";^^^^^;"""""""","""XpY[i<:'''''' raUJYcvuuzCZXxnnuucz^```````';?:,I-1[>:!)l<+<!~~,````' jhunnf|1}[[{][})/xvuLz'''`>_\+",,,,,,,,,,""i[[1n/t+-}>"/(][[(}[[[[[[[[[[[[/}?^v}      
                ;\`^,v^ ~bb['"}"^^^^;!^"""""""""`tMMc;:`''''''.;pOvvnxxf|{\({)\fxxJ!'``````I-!i~+>:"!~>_~'`";li~;````'"1Cf{]]???--???<:;~rfl.'`:"_{",,,,,,,,,"^l_}]1J-n]]\~lxt][[[(}[[[[[[[[[[[]/)[>lJ,     
                i)`^!j  -bQr``)<`^^^^>!^""""",,,"<JmMv^'`''''''._ZYrrt1[]]?--?<;!}fl'`````,<il;"`''''`":!"``''''````^`''tc)-_________l..,};'`^^`+{:,,,,,,,,"^;)\}]/Z)_v{}i{c|][[[[){][[[[[[[[[[[(v][:{r     
                <{'`_\  }h[n;'?u`^^^^^_l^","",,,""xjchX"```'''''.^rJf]??--____I...+"```````''''````````''```````````^^^^'!1\({?____-[1)+I^,:,",_-<l,,,,,,"^l|Lt]}vpn`r_~{nt[[[[[[[)1][[[[[[[[[[[[Qt]?"r]    
                <{''1/  1p:{{';Z['^^^^"]>^,,,,,,,^}c/rqc^^^^^^``'.^?jt{?_++++++<<i"`^````````````,^``````````````^^^^^^""^^;~?]???---+l:,::::!-_-!,::,"":+jQdj[fXUc:>mQZr[]}([[[[[1)][[[[[[[[[[[]cp1[~:ci   
                <(''/n  (m^^x:'nci`^""^"}-^",,,,,";nufrO\^"",,,:;"^'^i](\)1{}11{<"^^^^^^`````````;"``````````````^^^^"""",,,,,::::::::;II;I>?]}-;",",I+(ucnXt\cx|n!'XaX}][[[\}[[[[{(][[[[[[[[[[[]|aZ{[>ic:  
                !f``tL` |Z` </'_r|!`""^^^jr;^",,,,"+Ynrvw-":::;I;::::,,;!><<il;"^""^^^^^`````````'```````````````^^^^"",,::::II;;II;;llIl<[1{_I:l>_[(tf|}1nrj\_[f!'_ZX/][[[])|][[[}\][[[[[[[[[[[[[mZz1[!_n" 
                "t"'fq] |w`  [{`j-z>'"""^iwQ[:^,,,,"[CurQX::;Il;;;;I;;I;:::::::,,"""^^^^`````````````````````````^^^^"",,:::II;;II;;lli]/f/([)c){{}[]?]}fn(_l^<\I^:JJXt][[[[}f}[[[[\[[[[[[[[[[[[[]cm?U1]![n"
                .)l'/CL^}p"   [}>nQZ?^^""`{bYf[I"",,"[Cvvw>:;l;;;;I;;II;I;;;:;;,,,,""^^^^``````````````````````````^^^""",,:;::;I;;;;;>+~>!llUJ+__?]]]-_<:^^^i[;l,jZXYj][[[[[\/][[]\}[[[[[[[[[[[[])k?+J)]>)v
                 _].(jYz_d! .  ~)nqQXf!`^"^/0}|f(+I,"^~XX0)":::::;;:II:;;:;;;;:,,,""^^^^`````````````````'``````````^^^^""",,,,:::::::,,""^^tO[-]?-~!;"^^""":!l<,1pUXYn][[[[[}z{][]|1][[[[[[[[[[[[]UU +J\]~(
                 `|"_j[JQd1 .   ^]Ym((u\>"^^jn?[1\t\[~;lfJQ-^^",::::;::;:::::,,,"""^^^^```````````'`^`'^,:,^'``````````^^^^^""""""""""^``I[Xw)+~!;,"""""""^"!+i^]b0XYYz[[[[[[]xc][]1|][[[[[[[[[[[[](q~ >Jr]-
                  ~1,t[[zow"      ;Z\?]|xf]l"|/][[[{)||1[jQmc]I^`^"",,,,,,,,"""""^^^^^````````````1j}_i+__-?<^``````````````^^^^``''^I_/YZkQ~:,""",,,,""":<-<""+XqXYYYU1][[[}])Zf][}/[[[[[[[[[[[[[[]JX. ;YX}
                   }?<}[]/0U?"    ;O1][[]{/rrff(][[}[[[[|JruYLQX\_I^```^^^^^^^^^^^```````````````'<i:::,,,,,l"```````````'''..'^I_(uLmwZLZcI^,,,,,,""":i--i"`l__qUXYYYJt][[[[[]Cq|]]\{][[}[[[[[[[[[])p_  ^xQ
                   .}1{][]]|cXn\{?|Q)}[[[[]])Y><iI:i[}[[)JrrrrxvZhOJu|-i;"`''''''''''`````````````'''''``''''`````''''''`,!-(uJ0mmmqUYXJQ\,",,,,"":l<--<:^`,<<^XmzXXYYUv][[[[[]rhQ{])\][[1}[[[[[[[[[?jQ`  .[
                     >fr1[]]][)\//\1}[[[[[[[[ci`l`^^l?}[{JxxxxxrJaJXJQ00QLLcx/{?~il;,^`''...................''```^;!+])tObpddZbb0CQpCL0c<^""":;!~?]_i:^``"i~;'(MpmZOQLCC{?]][[[)dOU}}t[[[}|[[[[[[[[[[>Qt    
                      .>)\\)1{{{1)t{i~[[[[[[]j[`+"^^^,~[[cnxxxxxC00czzzzXU#OLOZmmZZmm0LCJYzvxf/|\|)}[[]][{(\(}?_~_]}[[??pMbZf])XaoZmqL{:I<+?}}]_i;^^^^`,>+l^'!pmZqdkkkkbmCzj|{[[O0Cz]|(][[1\][[[[[[[}++m~   
                         ^l+][]?~?j:`!}[[[[[[|t`<l^^^^^I_rvxxxxx0tOcXXXXXJhUczXYCQZpkdddbbqmmqbkqLcrYoM#kmc|[?------__+-Lhv{[}}[|LdpY--//?<!;"^`^,;:"I-]!^^^^JZzXYUCL0O000OZmZQYw0XLx[j[[[[(|][[[[[[[[:|X;  
                                 (-`^<][[[[[[}u;;+`^^^^^^?YxxxnvC]ZzXXzzzZhOqdbpwmOQCCCJYUJ0qLf{]]?\Zpkq{_+__-----__?)xvf}][}}}}[{wuI!<I`````";ll;I+)(~"`^^'jqXYYYYYXXXYUUUUJYC0qbkqZj|/][[[|(][[[[[[}~^rf" 
                                +/^^"~i[[[[[[]j?'_,^^^^^^,XnxnxYj{QczYLZphbw0CUYXzULQ00QLJmqr]?][]|pmLcY-_-----__?1fxf([][}}}}}}1z?;>I^^^^:!<>!i-(t)~,`^^^'{pYYYYYYYYYYYYYYXUQYzccJma*0C{][[[\|][[[[[[],lx|`
                               ,fl`^:I;[[[[[[[1f"I<`^^^^^'|XxnnC+nCZdbpZCYXXXXXXCwwLXnf|1rY[1]]]]}Y/[_}/_-----_[fn1:"":;l!i>>>><t+!I^^";!>>>_/nx\-l"`^^^^']pUXYYYYYYYYYYYYYJZ0xjjffjuQaMq\][[[vx][[[[[}<'-x(
                              '\+`"^:";[[[[[[[[t-`<:^^^^^^;YnxnLvokmCYXXXYYYYXUdaLj(111/Uv_rd}]]]f\+_-]------_(u)jL/^.''''''...iv["'`"l<-1cqwu-I"^^^^^^^']qUXYYYYYYYYYYYUUYznffffffffvXw&ox][[1Zn][[[[[],`\j
                              1)`^^,;^I[[[[[[[[}t:"l^^^^^^`{JLb&oQXzXXYYYYYYYO#m/{11)\xzc-xXYr?]]/----------_(c]/Y}ru'''..`,Iifv\)//(vYYLdbn~"^^^^^^^^^'{qUXYYYYYYYYUJJYvxftfjjfjfffrXYYh&#x][]rdn][[[[}>`Iz
                             _/"^""~,^l[[[[[[[[[\{'""^^^^^^^c&MaXXXYYYYYYYXCwoc[{11((|(x+|ffUpt?]r--------_+(z[)x|xUq/.:<?[]+!i]COwhdkOLY|l``^^^^^^^^`^/dQCCJUYYUJJUXurffffjjfffffruXUJUpWMk)][[0kc][[[}?"`-
                            !j:^"`-+^^i}[[[[[[[[{c!`^""`^^^^:LhdXYYYYYYYYX0mmf'^,;}];,(_fYmXxkqv}xr+----__[fv{|vULJYLq|]~l,'^}xQpJXqbCt~^'^^^^^^^^^^'lvJfjxvYO0YzuxfffffffffjjrnvXJJCCLqM#*Mf][]fkpX[][[}l^^
                           "j!`"`+x,^^<}[[[[[[[[)\n,^"?i'^^^`lLkCXYYYYYYXZOUz`''.;!..ljt{~v][QXQQrXj____\vunxr/1(xLZn~;l>>:<YJfmYUZL}:'`^^^^^^^^^^`^[YufrnvvvnrfffffjjrxnvczXUJCCLQOwbo##**MJ?[[}ZYtU}][}+^^
                          't_`"`iO{`^^+}[[[[[[[[\[fr:'[k/:'`^`;vbCXYYYYYOQzL[ .,"'.''^^. i{^'>n\vQ00u{)vQXn\-+[|/zniI??i:`{Jf|LJLc-^'^^^^^^^^,:"``+zQYXcuxjffffjrxvXCQ0OZZmqdkhao**###****okZ][[]up,)C{][]:^
                          {1`^`;0Z;^^"?[[[[[[[[}/[]rc;l*&dj<"''']YUUYYXJOXYCI !<`'''''...:|i?{fn\vx{))|Jnx|)rx)<|/?zx!^^`1n(jnzX?``^^^^^^^^;l;`^~cq0XnjfjxvXJQ0Zmqdbbbbbbbbbka***********#dp0][[[(b- 1C}[}!^
                      .  <j^^^:C*j`^^:][[[[[[[](|[}]/c?u*habQx}>,">\vXYJUYUJ^++'''''.':<}(j\1[][]n}<+~jX?~_])|(nU1tu^`^`>0n)>ft,'^^^^^^^";!;`:}X0JunvYCOwpdbbbbbbbbbdddddddddb***********aOhX][[[[Zf  (J}}+^
                        "xl^^"Xpb<`^^l[[[[[[[[[f{[}[[}cLZbdbkhhdm0U\txYUXYCX]_.''.';_1({?+~<?|fj/r)~+}v-jf}+~~_}/jY('^^`-c",u(`^^^^^^^^;l,^>jQOLCQmpbbbbbbbbdddddddbbbbdbbbbdb**********ommd)][[[]Jz   fX]],
                        /]'^^vvcJ^^^^>}[[[[[[[1r]}}}}]jWbbdddddbbkaOncXXYXOm[.'.`<1)[+~~++++++~<_nmUvCC~+(/?+++~~+[x\;`^"(>n)^^^^^^^^:I",[JkkpdbbbbbwzccczczcczzzzzczzzzzzcczUJUUO*****ammd/][[[[]vU   'Xx]I
                       ~j^^'/YIq{'^"^+}[[[[[[]j|[}[[[]\hbddddddbbbdk0XXYYXkY'''i|{_~~++++++~<~1cOhxn?JdC{<<+++++++~~}/_^`"\j;^^^^^^;<<!/wMobbbddddbbmxvvvzczncYYXnzcnXYUvnXcYLCCcL#####khbj][[[[}]nY    ;L\!
                      `n!`'[0^{m;^"""-[[[[[[[{n[[]{|tfvhkddddddddbbbkLXXXJo<.''\?<+++++++~~?fOpYmC(\<QuUmn?<++++++++~+1(:'()`^^^`I?1tzpohddddbdddddbmxuvvcXcuvzccvvvvzYXczYzXCJJcLM###*#&C][[}}[[]xc     [J_
                      {|'`!m> JX`^"",][[[[[[]jt](J0Owa#&#bdddddddbbbbkLXXOO`'''>|~~++++~~}jJmX{|df{^!q|-YCc{<+++++++++~{r`)-`"^^]rXmkhbdddbbddddddddpQQQQ00OZZmmmmZZmwqwqqwwwwwwwd******#MX][}}[[]vr     'c/
                     "c;`"C) :p)'^"^:][[[[[[}c{}QCczbMW#M#bdbddddddbdbkLzqr.'''.+\-~++~)uXJc{~_LJ[`.-Q}<?cXYr+++++++~~_{}!?"^`!Ypbkbdbdbbbbbbddddbbbkhaao***#ohkkbbbbk############*******#b\]}}}[[J1      _Y
                     )/''tU. _p<`^^^;[[[[[[]fn]jZvcw&#***##kddddddddddbkCp{.``''.I{1_~)0Uv)+~+fwrl'.fc[~~_nYCv+<~~+]{((_:],^`;O#bbdbbbddddbbkkhaaooaaakkbkkkbdddbbbbbbao*****************kbL?[[}[)C~;`,,^ ^Y
                    ^Ui'<wl  (mI^^^^:[[[[[[[z|]QCczho*****#Mobdddbbbbddbkk{''``'''':jfju(+~++1LX('';cn[~+++|vz|(/ut}_iI:(1`^;Jhddbdbbbkhoo*#*oohkbbbbddbkkbdddbbbbbbbbbbkhao************kZ#X?[}[]uv;I",;"  x
                    ~U^`Yx   jL:^^^^:][[[[[(X)jdUcXko*******#MobdbbbbbbbkMf:''''''.~j+_+<+++-uZ){I'[jn{~+++~_}//{zj~?][]C[`;vkbbbka**##MM#oakbbbbbbbbbhhbdbbbbbbbbbbbbbbbbbbka**********mwM\][}[)L_      . /
*/