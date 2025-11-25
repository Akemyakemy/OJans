// Problem: Effective Numbers
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/E
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define int LL
constexpr int MAXS = 200000;  // 2sqrt(n)
constexpr int mod = 1000000007;
 
template <typename x_t, typename y_t>
void inc(x_t &x, const y_t &y) {
  x += y;
  (mod <= x) && (x -= mod);
}
 
template <typename x_t, typename y_t>
void dec(x_t &x, const y_t &y) {
  x -= y;
  (x < 0) && (x += mod);
}
 
template <typename x_t, typename y_t>
int sum(const x_t &x, const y_t &y) {
  return x + y < mod ? x + y : (x + y - mod);
}
 
template <typename x_t, typename y_t>
int sub(const x_t &x, const y_t &y) {
  return x < y ? x - y + mod : (x - y);
}
 
template <typename _Tp>
int div2(const _Tp &x) {
  return ((x & 1) ? x + mod : x) >> 1;
}
 
// 以上目的均为防负数和取模
template <typename _Tp>
long long sqrll(const _Tp &x) {  // 平方函数
  return (long long)x * x;
}
 
int pri[MAXS], lpf[MAXS + 1], spri[MAXS + 1], pcnt;
 
void sieve(const int &n) {
  for (int i = 2; i <= n; ++i) {
    if (lpf[i] == 0) {  // 记录质数
      lpf[i] = ++pcnt;
      pri[lpf[i]] = i;
      spri[pcnt] = spri[pcnt - 1] + 1;  // 前缀和
  }
    for (int j = 1, v; j <= lpf[i] && (v = i * pri[j]) <= n; ++j) lpf[v] = j;
  }
}
 
long long global_n;
int lim;
int le[MAXS + 1],  // x <= \sqrt{n}
    ge[MAXS + 1];  // x > \sqrt{n}
#define idx(v) (v <= lim ? le[v] : ge[global_n / v])
 
//主要是更改G函数
int G[MAXS + 1][2], Fprime[MAXS + 1];
long long lis[MAXS + 1];
int cnt;
 
void init(const long long &n) {
    cnt = 0;
    lim = sqrt(n);
 
  for (long long i = 1, j, v; i <= n; i = n / j + 1) {
    j = n / i;
    v = j;
    lis[++cnt] = j;
    (j <= lim ? le[j] : ge[global_n / j]) = cnt;
    G[cnt][0] = v-1;//初始化G[n][k] = g[i][k]前n项和,其中g[i][k] = i^k
  }
}
 
void calcFprime() {
  for (int k = 1; k <= pcnt; ++k) {
    const int p = pri[k];
    const long long sqrp = sqrll(p);//sqrll(x) -> x*x
    for (int i = 1; lis[i] >= sqrp; ++i) {
      const long long v = lis[i] / p;
      const int id = idx(v);
      //G[i] -= [p_k *p_k<=n]*g[p_k]*(G[id] - G[p_{k-1}])
      G[i][0]-= (G[id][0] - (k-1));
    }
  }
  /* F_prime = G_1 - G_0 */
  for (int i = 1; i <= cnt; ++i) Fprime[i] = G[i][0];
}
 
int f_p(const int &p, const int &c) {
  /* f(p^{c}) = p xor c */
  return 1;
}
 
int F(const int &k, const long long &n) {
  if (n < pri[k] || n <= 1) return 0;
  const int id = idx(n);
  long long ans = Fprime[id] - (spri[k - 1] - (k - 1));
  for (int i = k; i <= pcnt && sqrll(pri[i]) <= n; ++i) {
    long long pw = pri[i], pw2 = sqrll(pw);
    for (int c = 1; pw2 <= n; ++c, pw = pw2, pw2 *= pri[i])
      ans +=
          ((long long)f_p(pri[i], c) * F(i + 1, n / pw) + f_p(pri[i], c + 1)) %
          mod;
  }
  return ans % mod;
}
int get(int R){
    int ans = 0;
    if(R == 1) return 0;
    global_n = sqrt(R);
    while(global_n*global_n<R) global_n++;
    init(global_n);
    calcFprime();
    for(int l = 1,r;l<=global_n;l =r+1){
        r = global_n/(global_n/l);
        ans+=global_n/l *(Fprime[idx(r)] - Fprime[idx((l-1) )]);
    }
    int temp = global_n*global_n;
    for(int i = 2;i*i<=global_n;i++){
        if(global_n% i== 0){
            if(temp -i>R){
                ans--;
            }
            while(global_n%i==0) global_n/=i;
        }
    }
    if(global_n>1){
        if(temp -global_n>R){
                ans--;
        }
    }
    return ans;
}
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  sieve(100000+10);
  int  l,r;
  cin>>l>>r;
  cout<<get(r) - get(l - 1)<<"\n";
  return 0;
}