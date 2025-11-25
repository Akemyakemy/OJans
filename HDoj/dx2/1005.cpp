// Problem: 循环位移
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1005
// Memory Limit: 524288 MB
// Time Limit: 4000 ms
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
const int N=20007;
int n,a[N],o;
vi S;
void mov(int x)
{
	S.eb(x);
	fo(i,x,x+o-2) swap(a[i],a[i+1]);
}
void movR(int x)
{
	fo(i,1,o-1) S.eb(x);
	fd(i,x+o-1,x+1) swap(a[i],a[i-1]);
}
mt19937 rnd(0);
void work()
{
//	n=190;
//	fo(i,1,n) a[i]=i;
//	shuffle(a+1,a+n+1,rnd);
	S.clear();
	scanf("%d",&n);
	fo(i,1,n) scanf("%d",&a[i]);
	if(n==2)
	{
		o=2;
		if(a[1]>a[2]) S.eb(1);
		printf("%d\n%d\n",o,(int)S.size());
		for(int x:S) printf("%d ",x);
		printf("\n");
		return;
	}
	o=90;
	while(o>=n) o-=2;
	fd(i,n,o+2)
	{
		int k=0;
		fo(j,1,i) if(a[j]==i){k=j;break;}
		while(k<i)
		{
			if(k+o-1<=i) mov(k),k=k+o-1;
			else mov(i-o+1),k--;
		}
	}
	int w=0;
//	printf("%d\n",(int)S.size());
	fo(i,1,o+1) if(a[i]==o+1) w=i;
	fd(i,o,1)
	{
		int k=0;
		fo(j,1,o+1) if(a[j]==i){k=j;break;}
		while(k!=1)
		{
			mov(2);mov(1);
			k=k<=2?k+o+1-2:k-2;
			w=w<=2?w+o+1-2:w-2;
		}
		while(w!=o+1)
		{
			mov(2);
			w=w==2?o+1:w-1;
		}
		mov(2);mov(1);w-=2;k=o;
	}
	while(w!=o+1)
	{
		mov(2);mov(1);
		w=w<=2?w+o+1-2:w-2;
	}
	printf("%d\n%d\n",o,(int)S.size());
	for(int x:S) printf("%d ",x);
	printf("\n");
//	fo(i,1,n) printf("%d ",a[i]); printf("\n");
}
int main()
{
//	int T=3;
	int T;scanf("%d",&T);
	while(T--) work();
}