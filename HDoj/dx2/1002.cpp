// Problem: 数上的图
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1002
// Memory Limit: 512000 MB
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
#define boost ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
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
typedef unsigned long long ull;
#define lowbit(x) ((x)&(-x))// 直接 (x)&(-x) 容易出现问题
using i128 = __int128_t;
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

inline void solve(){
	int n,x,y;n=read();x=read();y=read();
	if(__builtin_popcountll(x)==__builtin_popcountll(y) || lowbit(x)==lowbit(y)) writeln(1);
	else writeln(2);
}
signed main(){
	//boost;
	int t;t=read();
	while(t--)
	solve();
	return 0;
}