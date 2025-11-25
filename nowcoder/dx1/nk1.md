# [ nkdx1](https://ac.nowcoder.com/acm/contest/108298)

### 补题

入门

- [x] E  
- [ ] G  

简单

- [ ] K
- [ ] L

中等

- [ ] B
- [ ] H
- [ ] I

较难

- [ ] A
- [ ] C
- [ ] F

困难

- [ ] D
- [ ] J

### E- Endless Ladders

```c++
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if (a < b) swap(a, b);
        LL prod = LL(a + b) * (a - b);
        printf("%lld\n", max(prod - 1, 0LL) / 2 + max(prod - 4, 0LL) / 4);
    }
    return 0;
}

```

### G- Symmetry Intervals

```c++
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 100000 + 5

int n, q;
char s[N], t[N];

int main()
{
    scanf("%d%d", &n, &q);
    scanf("%s", s + 1);
    for (int i = 1, a; i <= q; i ++)
    {
        scanf("%s%d", t + 1, &a);
        LL ans = 0;
        for (int j = 1, pre = 0; t[j]; j ++)
        {
            if (t[j] == s[a + j - 1])
                pre ++;
            else pre = 0;
            ans += pre;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

### K- Museum Acceptance

```c++

```



### [题解](E:/Oj ans/nowcoder/dx1/2025_Nowcoder_Multi_University_Training_Contest_1_Editorial.pdf)