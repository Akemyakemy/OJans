// Problem: T634816 [语言月赛 202507] 地铁计费
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T634816?contestId=256033
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
#define pii pair<int,int>
typedef long long ll;
//const int mod=;
//const int maxn=NeM+10;
inline int read(){//手动读取数字更加快速
    int sum=0,d=1;
    char c=gc();
    while(c<'0'||c>'9'){
        if(c=='-')d=-1;
        c=gc();
    }
    while(c>='0'&&c<='9'){
        sum=sum*10+c-'0';
        c=gc();
    }
    return sum*d;
}
inline int writeln(int arg) {return printf("%lld\n", arg);}
inline string sread() {
    string str;
    char c = gc();// 跳过前导空白符（空格、换行、制表符）
    while (c == ' ' || c == '\n' || c == '\t') c = gc();// 读取非空白字符，直到遇到空白符或EOF
    while (c != ' ' && c != '\n' && c != '\t' && c != EOF) {
        str += c;
        c = gc();
    }
    return str;
}
/*int pow_mod(int a, int b) {// 快速幂计算逆元
    int res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}*/

void solve() {
    int n, k;
    n = read(); k = read();
    vector<int> p(k + 1);  // 存储分界点 p_0 到 p_k（1-based 改为 0-based 更直观）
    for (int i = 0; i <= k; ++i) {
        p[i] = read();
    }
    int q = read();
    while (q--) {
        int x = read(), y = read();
        if (x == y) {
            writeln(1);  // 同站进出，收费1元
            continue;
        }
        // 统一处理 x > y 的情况（计费与方向无关）
        if (x > y) swap(x, y);
        
        // 查找 x 所在的收费区（左闭右开 [p[a], p[a+1})
        int a = upper_bound(p.begin(), p.end(), x) - p.begin() - 1;
        // 查找 y 所在的收费区
        int b = upper_bound(p.begin(), p.end(), y) - p.begin() - 1;
        
        if (a == b) {
            // 同一收费区的不同车站，收费2元
            writeln(2);
        } else {
            // 不同收费区：中间包含的完整收费区数量为 (b - a - 1)
            int m = b - a - 1;
            writeln(2 + m);
        }
    }
}
signed main(){
	//ios::sync_with_stdio(false);
	//cin.tie(nullptr),cout.tie(nullptr);
	//int t;t=read();
	//while(t--)
	solve();
	return 0;
}