// Problem: Kindred Sums
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/K
// Memory Limit: 2048 MB
// Time Limit: 10000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
 
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
 
constexpr u32 P = 1E9;
constexpr u64 mod = 1E18;
constexpr int N = 1000;
 
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
 
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
 
  std::vector<u64> A(N);
  for (int i = 0; i < N; i++) {
    std::cin >> A[i];
  }
 
  auto work = [&](std::vector<u32> a) -> std::array<u32, 2> {
    const u32 V = u32(1) << 31;
    std::map<u32, u32> mp;
    while (true) {
      u32 s = 0, t = rng() % (V - 1) + 1;
      for (int i = 0; i < 31; i++) {
        if (t >> i & 1) {
          s = (s + a[i]) % P;
        }
      }
      if (mp.count(s) && mp[s] != t) {
        return {t, mp[s]};
      }
      mp[s] = t;
    }
  };
 
  std::vector<u32> na(31);
  std::vector<u32> x(31), y(31);
  for (int i = 0; i < 31; i++) {
    std::vector<u32> a(31);
    for (int j = 0; j < 31; j++) {
      a[j] = A[i * 31 + j] % P;
    }
    auto [X, Y] = work(a);
    x[i] = X;
    y[i] = Y;
    u64 sum = 0;
    for (int j = 0; j < 31; j++) {
      if (X >> j & 1) {
        sum = (sum + A[i * 31 + j]) % mod;
      }
      if (Y >> j & 1) {
        sum = (sum + mod - A[i * 31 + j]) % mod;
      }
    }
    na[i] = sum / P;
    assert(sum % P == 0);
  }
 
  auto [u, v] = work(na);
  for (int i = 0; i < 31; i++) {
    if ((u >> i & 1) == (v >> i & 1)) {
      for (int j = 0; j < 31; j++) {
        std::cout << 0;
      }
    } else {
      for (int j = 0; j < 31; j++) {
        if ((x[i] >> j & 1) == (y[i] >> j & 1)) {
          std::cout << 0;
        } else if (x[i] >> j & 1) {
          std::cout << 1 + (v >> i & 1);
        } else {
          std::cout << 2 - (v >> i & 1);
        }
      }
    }
  }
  for (int i = 31 * 31; i < 1000; i++) {
    std::cout << 0;
  }
 
  return 0;
}