// Problem: 景区建设
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1006
// Memory Limit: 65536 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define For(i, j, k) for (int i = (j); i <= (k); ++i)
#define ForDown(i, j, k) for (int i = (j); i >= (k); --i)
#define Debug(fmt, args...) fprintf(stderr, "(func %s, line #%d): " fmt, __func__, __LINE__, ##args), fflush(stderr)
#define debug(fmt, args...) fprintf(stderr, fmt, ##args), fflush(stderr)
#define within :
#define LJY main
using namespace std;
typedef long long ll;
const int N = 105;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
inline int read() {
  char ch = getchar(); int x = 0, f = 1;
  while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
  while (ch >= '0' && ch <= '9')
    x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return x * f;
}
int n, m, a[N][N]; bool vis[N][N];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
void ljy() {
  n = read(); m = read(); memset(vis, 0, sizeof(vis));
  vis[1][1] = 1;
  For(i, 1, n) For(j, 1, m) a[i][j] = read();
  vector<pair<int, int> > vec = {{1, 1}};
  For(i, 1, n) For(j, 1, m) if(i != 1 || j != 1){
    bool flg = 1;
    For(dir, 0, 3) {
      int x = i + dx[dir], y = j + dy[dir];
      if(x >= 1 && x <= n && y >= 1 && y <= m && a[x][y] > a[i][j]) {flg = 0; break;}
    } if(flg) vec.emplace_back(i, j);
  } ll ans = ((vec.size() - 1) << 34);
  sort(vec.begin(), vec.end(), [&](auto x, auto y) {return a[x.first][x.second] < a[y.first][y.second];});
  int len = vec.size();
  For(i, 0, len - 2) {
    auto [x, y] = vec[i]; auto [xx, yy] = vec[i + 1];
    ans += 114 * abs(xx - x) + 5141 * abs(yy - y) + 919810ll * (a[xx][yy] - a[x][y]);
  } printf("%lld\n", ans);
}
signed LJY() { int T = read(); while(T--) ljy();}