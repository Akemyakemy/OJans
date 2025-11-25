[CF2162H Beautiful Problem - 洛谷](https://www.luogu.com.cn/problem/CF2162H)

[Problem - H - Codeforces](https://codeforces.com/contest/2162/problem/H)

这是我的第一次仔细思考，也就是细糠。

*f*(*a*,*x*,*l*,*r*)={0,1,如果 (*x*−min*j*=*l**r*(*a**j*))⋅(*x*−max*j*=*l**r*(*a**j*))<0如果 (*x*−min*j*=*l**r*(*a**j*))⋅(*x*−max*j*=*l**r*(*a**j*))≥0

当 f 的值是 [li,ri] 的 1 时， [li,ri] 中的所有数字要么是 ≤x ，要么是 ≥x 。

我们注意到，对于每个区间，我们需要将其划分为 S-区间（较小）和 B-区间（较大）。S 型区间只能包含数字 ≤x ，而 B 型区间只能包含数字 ≥x 。

假设我们已经固定了 S-椭圆和 B-椭圆。每个索引 i 有 4 种类型：

- 类型 1： i 只包含 S-区间；
- 类型 2： i 仅由 B 型区间覆盖；
- 类型 3： i 同时被 S-intervals 和 B-intervals 覆盖；
- 类型 4： i 既未被 S-intervals 覆盖，也未被 B-intervals 覆盖。

设 cnts 是值 <xlt; xlt;xlt; x的个数，cnt _ b是值> xgt;x 的个数。

当不存在类型 4 索引时，我们只需检查是否存在以下情况：

- cnts≤ （类型 1 索引的总数）
- cntb≤ （类型 2 索引总数）

当存在第 4 类索引时，我们只需对条件稍作修改（该修改由读者自行决定）。

考虑一种更简单的情况：所有区间都不重叠。在这种情况下，问题就简化成了经典的 "knapsack "问题，即每个区间都是一个独立的项目。我们考虑将 DP 的思想扩展到原始问题。

我们发现，包含在其他区间内的区间是无用的，可以删除。然后，可以根据区间的左端点对区间进行排序。这样，对于 i<j ，我们可以确保 li<lj 和 ri<rj 。然后，我们根据区间的顺序执行 DP。

我们定义

dp[i][j][k=0 or 1] :对于前 i 个区间，类型 1 索引的总数为 j ，最后一个区间为 S-区间（ k=0 ）或 B-区间（ k=1 ），获得的类型 2 索引总数最多。

设 inslen[i] 是 i -th区间与 (i−1) -th区间的交集长度。

过渡

- dp[i][j][0]=max(dp[i−1][j−inslen[i]][0],dp[i−1][j−inslen[i]][1]−inslen[i])
- dp[i][j][1]=max(dp[i−1][j][1]+inslen[i],dp[i−1][j+inslen[i]][1]+inslen[i])

注：对于区间 (i−2) 、 (i−1) 、 i ，如果区间 (i−1) 的类型与 (i−2) 和 i 以及 r[i−2]≥l[i] 都不同，则可能会重复减去一些重叠部分。然而，我们发现这并不影响最终答案，因为它并不比三个区间都是同一类型时的答案更好。在这里，我们应用了一种常见的 DP 思路：如果记录了 "不正确 "的状态，但它们不能成为最优状态，那么 DP 转换可以保持不变（[https://codeforces.com/contest/1859/problem/E)](https://codeforces.com/contest/1859/problem/E) 中也使用了类似的思路）。

 一些重叠部分（中间）被重复减去。| 更好，因为中间位置的值范围严格来说更大。|

之后，使用 DP 数组回答查询就变得微不足道了。时间复杂度为 O(n2) 。

第一步：预处理，去重区间

```c++
for(int i=1,l,r;i<=m;i++){
    cin>>l>>r;
    mxr[l]=max(mxr[l],r);
}

int sz,cfree=0;

vector<int> tag(n+4);//标记被覆盖的位置
vector<seg> vs;//去重后的区间集
for(int i=1;i<=n;i++){
    if(!mxr[i]) continue;

    if(vs.empty() || vs.back().r<mxr[i]){
        vs.push_back(seg(i,mxr[i]));
        
        for(int j=i;j<=mxr[i];j++) tag[j]=1;
    }
}

for(int i=1;i<=n;i++) if(!tag[i]) cfree++;//留下没被覆盖的位置，里面可以重排任何数
```

第二步：dp

```c++
dp[pre-i-vs][cnt_s][last-vs-type(1-s,2-b)]==cnt_b
cnt_s:the count of num < x
cnt_b:the count of num > x

sz=vs.size();

dp[1][0][0]=vs[0].len();//cnt_b=vs[0].len() because of cnt_s==0 in vs[0].len()
dp[1][vs[0].len()][1]=0;

for(int i=2;i<=sz;i++){
    seg cur=vs[i-1],ins=getins(vs[i-2],vs[i-1]);
    int len_ins=ins.len();
    for(int j=0;j<=n;j++){
        
        //dp 在转移时要考虑自身的值，并转移最大
        //cnt_s not increase,cnt_b inc
        dp[i][j][0]=max(dp[i][j][0],dp[i-1][j][0]+cur.len()-len_ins);
        //original b-interval trans to s-interval
        //insection of i-th & (i-1)-th vs(len_ins) turn to b from s(j+len_ins)
        //
        if(j+len_ins<=n) dp[i][j][0]=max(dp[i][j][0],dp[i-1][j+len_ins][1]+cur.len()-len_ins);
        
        if(j-(cur.len()-len_ins)>=0){//同理
            dp[i][j][1]=max(dp[i][j][1],dp[i-1][j-(cur.len()-len_ins)][1]);
            dp[i][j][1]=max(dp[i][j][1],dp[i-1][j-(cur.len()-len_ins)][0]-len_ins);
        }
    }
}
```

第三步：输出答案

```c++
for(int i=1;i<=n;i++){
    int flg=0;
    int s=0,b=0;
    for(int j=1;j<=n;j++){
        if(a[j]>i) b++;
        else if(a[j]<i) s++;
    }//统计大于x的数和小于x的数，剩下的都是等于x的数，等于x的数必须填在sb-ins里，剩余的填在cfree
    
    for(int j=0;j<=n;j++){//cnt_s => cnt_b
        //s<j时，所有s数都能被s-interval容纳，返回0，need2亦然
        //由于只有n个位子，所以除了s和b就是x了，cfree不够就输出0，够就输出1
        int need1=max(0,s-j),need2=max(0,b-max(dp[sz][j][0],dp[sz][j][1]));
        if(cfree-need1-need2>=0){
            flg=1;
            break;
        }
    }
    cout<<flg;
}
```

总之是一个非常难懂的dp，蒟蒻看了半天。

