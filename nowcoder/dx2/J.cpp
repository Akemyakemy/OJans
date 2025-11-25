// Problem: Just Curve it
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/J
// Memory Limit: 2048 MB
// Time Limit: 12000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <cstdio>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
const int max1 = 1e5;
 
int n, q;
 
struct Data1
{
    double k, b;
 
    Data1 () {}
    Data1 ( double __k, double __b )
        { k = __k, b = __b; }
     
    Data1 operator * ( const Data1 &A ) const
    {
        return Data1(k * A.k, k * A.b + b);
    }
    Data1 operator + ( const Data1 &A ) const
    {
        return Data1(k + A.k, b + A.b);
    }
};
 
int opt[max1 + 5];
Data1 a[max1 + 5];
 
struct Data2
{
    int cnt;
    Data1 trans[31], sum_trans[31];
    double result, sum;
 
    Data2 () {}
 
    pair <double, double> Get_Result ( const double &x ) const
    {
        pair <double, double> ans = make_pair(0, 0);
        double now = x;
        for ( int i = 0; i <= min(30, cnt); i ++ )
        {
            ans.second += sum_trans[i].k * now + sum_trans[i].b;
            now = trans[i].k * now + trans[i].b;
 
            if ( i != min(30, cnt) )
            {
                now = sqrt(now);
                ans.second += now;
            }
        }
        ans.first = now;
 
        if ( cnt > 30 )
        {
            now = 1;
            for ( int i = 0; i <= 30; i ++ )
            {
                ans.second -= sum_trans[i].k * now + sum_trans[i].b;
                now = trans[i].k * now + trans[i].b;
 
                if ( i != min(30, cnt) )
                {
                    now = sqrt(now);
                    ans.second -= now;
                }
            }
            ans.second += sum;
            ans.first = result;
        }
        return ans;
    }
 
    Data2 operator + ( const Data2 &A ) const
    {
        Data2 res;
        res.cnt = cnt + A.cnt;
        for ( int i = 0; i <= min(res.cnt, 30); i ++ )
        {
            if ( i < cnt )
            {
                res.trans[i] = trans[i];
                res.sum_trans[i] = sum_trans[i];
            }
            else if ( i == cnt )
            {
                res.trans[i] = A.trans[0] * trans[i];
                res.sum_trans[i] = A.sum_trans[0] * trans[i] + sum_trans[i];
            }
            else
            {
                res.trans[i] = A.trans[i - cnt];
                res.sum_trans[i] = A.sum_trans[i - cnt];
            }
        }
 
        pair <double, double> tmp = A.Get_Result(result);
        res.result = tmp.first;
        res.sum = sum + tmp.second;
        return res;
    }
};
 
struct Segment_Tree
{
    #define lson(now) (now << 1)
    #define rson(now) (now << 1 | 1)
    Data2 tree[max1 * 4 + 5];
 
    void Build ( int now, int L, int R )
    {
        if ( L == R )
        {
            if ( opt[L] == 1 )
            {
                tree[now].cnt = 0;
                tree[now].trans[0] = tree[now].sum_trans[0] = a[L];
                tree[now].result = tree[now].sum = a[L].k + a[L].b;
            }
            else
            {
                tree[now].cnt = 1;
                tree[now].trans[0] = tree[now].trans[1] = Data1(1, 0);
                tree[now].sum_trans[0] = tree[now].sum_trans[1] = Data1(0, 0);
                tree[now].result = tree[now].sum = 1;
            }
            return;
        }
 
        int mid = (L + R) >> 1;
        Build(lson(now), L, mid);
        Build(rson(now), mid + 1, R);
        tree[now] = tree[lson(now)] + tree[rson(now)];
        return;
    }
 
    void Insert ( int now, int L, int R, int pos )
    {
        if ( L == R )
        {
            if ( opt[L] == 1 )
            {
                tree[now].cnt = 0;
                tree[now].trans[0] = tree[now].sum_trans[0] = a[L];
                tree[now].result = tree[now].sum = a[L].k + a[L].b;
            }
            else
            {
                tree[now].cnt = 1;
                tree[now].trans[0] = tree[now].trans[1] = Data1(1, 0);
                tree[now].sum_trans[0] = tree[now].sum_trans[1] = Data1(0, 0);
                tree[now].result = tree[now].sum = 1;
            }
            return;
        }
 
        int mid = (L + R) >> 1;
        if ( pos <= mid )
            Insert(lson(now), L, mid, pos);
        else
            Insert(rson(now), mid + 1, R, pos);
        tree[now] = tree[lson(now)] + tree[rson(now)];
        return;
    }
 
    Data2 Query ( int now, int L, int R, int ql, int qr )
    {
        if ( L >= ql && R <= qr )
            return tree[now];
         
        int mid = (L + R) >> 1;
        if ( qr <= mid )
            return Query(lson(now), L, mid, ql, qr);
        else if ( ql > mid )
            return Query(rson(now), mid + 1, R, ql, qr);
        return Query(lson(now), L, mid, ql, qr) + Query(rson(now), mid + 1, R, ql, qr);
    }
}Tree;
 
int main ()
{
    scanf("%d", &n);
    for ( int i = 1; i <= n; i ++ )
    {
        scanf("%d", &opt[i]);
        if ( opt[i] == 1 )
            scanf("%lf%lf", &a[i].k, &a[i].b);
    }
 
    Tree.Build(1, 1, n);
 
    int op, l, r, x;
    scanf("%d", &q);
    while ( q -- )
    {
        scanf("%d", &op);
        if ( op == 1 )
        {
            scanf("%d%d%d", &l, &r, &x);
 
            Data2 que = Tree.Query(1, 1, n, l, r);
            pair <double, double> ans = que.Get_Result(x);
 
            // printf("cnt = %d\n", que.cnt);
            // for ( int i = 0; i <= que.cnt; i ++ )
            //     printf("%lf %lf\n", que.sum_trans[i].k, que.sum_trans[i].b);
 
            printf("%.10lf %.10lf\n", ans.first, ans.second);
        }
        else
        {
            scanf("%d", &x);
            scanf("%d", &opt[x]);
            if ( opt[x] == 1 )
                scanf("%lf%lf", &a[x].k, &a[x].b);
             
            Tree.Insert(1, 1, n, x);
        }
    }
 
    return 0;
}
/*
10
2
2
2
1 1.0 50.00
2
1 0.5 100.00
2
1 0.1 98.23
1 0.2 23.55
2
5
1 1 2 4
1 1 9 7
1 2 10 8
1 3 4 999
1 2 2 114
*/