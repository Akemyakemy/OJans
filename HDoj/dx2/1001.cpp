// Problem: 骰子
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1001
// Memory Limit: 524288 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define fo(i,l,r) for(int i=(l);i<=(r);++i)
#define fd(i,l,r) for(int i=(l);i>=(r);--i)
#define fu(i,l,r) for(int i=(l);i<(r);++i)
#define pi pair<int,int>
#define eb emplace_back
#define vi vector<int>
#define fi first
#define se second
#define ll long long
using namespace std;
const int biao[120]={0,1,1,1,3,1,3,1,7,3,3,1,15,1,3,3,19,1,15,1,15,3,3,1,65,3,3,7,15,1,25,1,51,3,3,3,113,1,3,3,65,1,25,1,15,15,3,1,279,3,15,3,15,1,65,3,65,3,3,1,249,1,3,15,141,3,25,1,15,3,25,1,695,1,3,15,15,3,25,1,279,19,3,1,243,3,3,3,65,1,235,3,15,3,3,3,1165,1,15,15,117,1,25,1,65,25,3,1,697,1,25,3,279,1,25,3,15,15,3,3};
void work()
{
	int n;
	scanf("%d",&n);
	printf("%d\n",biao[n]);
}
int main()
{
	int T;scanf("%d",&T);
	while(T--) work();
}