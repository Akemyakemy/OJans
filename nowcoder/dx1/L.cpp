// Problem: Numb Numbers
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108298/L
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int int64_t
#define inf 0x3f3f3f3f
#define endl '\n'
const int maxn=2e5+9;

inline int read(){//手动读取数字更加快速
    int sum=0,d=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')d=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        sum=sum*10+c-'0';
        c=getchar();
    }
    return sum*d;
}

int a[maxn];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int t;t=read();
	while(t--){
		int n,q;n=read();q=read();
		int lim=n/2,aft=n;
		int pos=0;
		map<int,int> rec;//自动根据键（key）从小到大排序
		for(int i=1;i<=n;i++){
			a[i]=read();
			rec[a[i]]++;
		}
		while(q--){
			int p,v;p=read();v=read();
			if(a[p]<=pos && a[p]+v>pos) aft++;
			rec[a[p]]--;
			a[p]+=v;
			rec[a[p]]++;
			while(rec.upper_bound(pos)!=rec.end() && aft-rec.upper_bound(pos)->second>=lim)
				pos=rec.upper_bound(pos)->first,aft-=rec[pos];
			cout<<n-aft<<endl;
		}
	}
	return 0;
}