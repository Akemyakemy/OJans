#include <bits/stdc++.h>
#define boost ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

// 定义常量，N 表示铁棒数量的最大可能值（题目中 n 最多 420，这里设 425 留有余地）
const int N = 425;
// 定义极大值，用于表示无穷大的代价，方便后续比较取最小值等操作
const ll INF = 1e18;
// imb[l][r] 用于记录在区间 [l, r] 进行一次切割时，{不平衡度, 代价} 构成的键值对集合
vector<pll> imb[N][N];
// cmin[l][r] 用于记录针对 imb[l][r] 中不平衡度，对应的最小代价（做了优化处理，避免重复计算找最小值）
vector<ll> cmin[N][N];
// log_2[i][j] 预处理从第 i 根到第 j 根铁棒组成的整体长度对应的 log2 向上取整后的值，用于快速计算切割代价
ll log_2[N][N]; 
// a 数组存储每根铁棒的长度，psum 是前缀和数组，用于快速计算区间长度和
vector<ll> a(N), psum(N);

// 声明 solve 函数，后续定义
inline void solve();

int main()
{
    // 加速输入输出，关闭同步，让 cin/cout 速度接近 scanf/printf
    boost;
    int t;
    // 读取测试数据的组数
    cin >> t;
    while(t --) 
        // 处理每组测试数据
        solve();
    return 0;
}

inline void solve()
{
    int n;
    // 读取当前测试用例中铁棒的数量
    cin >> n;
    for(int i = 1; i <= n; i ++)
    {
        // 读取每根铁棒的长度
        cin >> a[i];
        // 计算前缀和，psum[i] 表示前 i 根铁棒的总长度，方便后续快速求区间和
        psum[i] = psum[i - 1] + a[i];
    }

    // 预处理 log_2 数组，计算从第 i 根到第 j 根铁棒组成的整体长度对应的 log2 向上取整后的值
    for(int i = 1; i <= n; i ++)
        for(int j = i; j <= n; j ++)
        {
            // 先清空 imb 和 cmin 对应区间的旧数据，为新测试用例做准备
            imb[i][j].clear();
            cmin[i][j].clear();
            // 计算 i 到 j 区间铁棒的总长度
            ll sum = psum[j] - psum[i - 1];
            ll res = 0;
            ll now = 1;
            // 通过不断左移（乘以 2），找到大于等于 sum 的最小 2 的幂次，res 就是对应的指数，即 log2(sum) 向上取整的值
            while(now < sum)
            {
                res ++;
                now <<= 1;
            }
            log_2[i][j] = res;
        }

    // 定义一个 lambda 表达式，用于计算在区间 [l, r] 切割点为 m 时的切割代价
    auto cost = [&](int i, int j, int m)->ll
    {
        // 计算切割点 m 左边区间（l 到 m）的长度
        ll lenl = psum[m] - psum[i - 1];
        // 计算切割点 m 右边区间（m+1 到 r）的长度
        ll lenr = psum[j] - psum[m];
        // 代价公式：min(左长度, 右长度) * log2(总长度)，总长度对应的 log2 值已预处理在 log_2[i][j]
        return min(lenl, lenr) * log_2[i][j];
    };

    // ans 数组用于存储最终结果，ans[i] 表示第一次切割在第 i 个焊点时的最小总代价，初始化为 -1 表示不可行
    vector<ll> ans(n + 1, -1);
    // 枚举区间长度，从 2 开始（因为至少需要 2 根铁棒才能切割），到 n 结束
    for(int len = 2; len <= n; len ++)
        // 枚举区间的左端点 l，右端点 r = l + len - 1
        for(int l = 1; l + len - 1 <= n; l ++)
        {
            int r = l + len - 1;

            // 双指针法枚举切割点，i 初始指向区间左半部分，j 初始指向区间右半部分，往中间靠拢
            int i = l, j = r - 1; 
            while(i <= j)
            {
                // 计算切割点为 i 时的代价
                ll icost = cost(l, r, i);
                // 计算切割点为 j 时的代价
                ll jcost = cost(l, r, j);
                // 计算切割点为 i 时的不平衡度（两段长度的绝对差）
                ll imbi = abs((psum[i] - psum[l - 1]) - (psum[r] - psum[i])), 
                // 计算切割点为 j 时的不平衡度
                imbj = abs((psum[j] - psum[l - 1]) - (psum[r] - psum[j]));
                // 根据不平衡度大小，选择当前更优的切割点 m（不平衡度大的优先，因为后续要满足 b1 >= b2 >= ... ）
                ll m = (imbi > imbj) ? i : j;
                // 取对应切割点的代价
                ll mcost = (imbi > imbj) ? icost : jcost;
                // 取对应切割点的不平衡度
                ll mimb = (imbi > imbj) ? imbi : imbj;
                // 移动指针，准备下一轮比较
                if(imbi > imbj) i ++;
                else j --;

                ll lcost, rcost;

                // 处理切割点 m 左边区间的最小代价，如果左边区间就是切割点本身（l == m），则左边没有更多切割，代价为 0
                if(l == m) lcost = 0;
                else 
                {
                    // 在 imb[l][m] 中找到不平衡度 <= mimb 的最大不平衡度对应的迭代器（upper_bound 找第一个大于 mimb 的，再往前移一位）
                    auto it1 = upper_bound(imb[l][m].begin(), imb[l][m].end(), make_pair(mimb, INF));
                    if(it1 != imb[l][m].begin())
                    {
                        it1 --;
                        // 取出对应的最小代价
                        lcost = it1->second;
                    }
                    else 
                        // 如果找不到符合条件的，说明当前切割方式不可行，跳过
                        continue;
                }

                // 处理切割点 m 右边区间的最小代价，如果右边区间就是切割点的下一个位置（m + 1 == r），则右边没有更多切割，代价为 0
                if(m + 1 == r) rcost = 0;
                else
                {
                    // 类似左边区间的处理，在 imb[m + 1][r] 中找不平衡度 <= mimb 的最大不平衡度对应的最小代价
                    auto it2 = upper_bound(imb[m + 1][r].begin(), imb[m + 1][r].end(), make_pair(mimb, INF));
                    if(it2 != imb[m + 1][r].begin())
                    {
                        it2 --;
                        rcost = it2->second;
                    }
                    else 
                        // 找不到符合条件的，跳过
                        continue;
                }

                // 计算当前切割点 m 对应的总代价：当前切割代价 + 左边区间最小代价 + 右边区间最小代价
                ll tcost = mcost + lcost + rcost;
                // 优化：如果当前 imb[l][r] 中已有的末尾元素的代价大于等于当前计算的 tcost，说明末尾元素可以删除（因为当前元素不平衡度更小或相等，代价还更小，更优）
                while(!imb[l][r].empty() && imb[l][r].back().second >= tcost) 
                    imb[l][r].pop_back();
                // 将当前 {不平衡度, 总代价} 加入 imb[l][r]
                imb[l][r].emplace_back(mimb, tcost);
                // 如果当前处理的是整个铁棒区间（len == n），说明是第一次切割的情况，记录到 ans 数组中
                if(len == n) 
                    ans[m] = tcost;
            }

            // 反转 imb[l][r]，方便后续 cmin 数组处理（让不平衡度从小到大排序，或者说调整顺序方便取最小代价）
            reverse(imb[l][r].begin(), imb[l][r].end());
            // 为 cmin[l][r] 预留空间，避免多次扩容影响效率
            cmin[l][r].reserve(imb[l][r].size());
            int sz = imb[l][r].size();
            for(int i = 0; i < sz; i ++)
            {
                // 构建 cmin 数组，cmin[l][r][i] 表示前 i + 1 个元素中的最小代价
                if(i == 0) 
                    cmin[l][r][i] = imb[l][r][i].second;
                else 
                    cmin[l][r][i] = min(cmin[l][r].back(), imb[l][r][i].second);
            }
        }
    
    // 输出结果，遍历 ans[1] 到 ans[n - 1]，对应每个焊点的最小总代价
    for(int i = 1; i <= n - 1; i ++)
        cout << ans[i] << " ";
    cout << "\n";
    return;
}