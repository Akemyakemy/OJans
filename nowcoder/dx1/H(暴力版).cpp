// Problem: Symmetry Intervals 2
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108298/H
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int int64_t
#define db long double
#define inf 0x3f3f3f3f
#define endl '\n'
#define rep(i, x, y) for(auto i = (x); i <= (y); i++)
#define gc getchar
#define x first
#define y second
#define eb emplace_back
#define em emplace
#define all(x) (x).begin(), (x).end()
typedef long long ll;
//const int mod=;
//const int maxn N+10;
inline int read(){//手动读取数字更加快速
    int sum=0,d=1;
    char c=gc();
    while(c<'0'||c>'9'){
        if(c=='-')d=-1;
        c=gc();
    }
    while(c>='0'&&c<='9'){
        sum=sum*10+c-'0';
        c=gc();
    }
    return sum*d;
}
inline int writeln(int arg) {return printf("%lld\n", arg);}

void solve(){
	int n,q;n=read();q=read();
	string s;cin>>s;
	while(q--){
		int type,l;type=read();l=read();l--;
		if(type==1){
			int r;r=read();r--;
			rep(i,l,r){
				if(s[i]=='0') s[i]='1';
				else s[i]='0';
			}
		}else{
			int a,b;a=read();b=read();
			int ans=0,cnt=0;
			for(int i=0;i<=l;i++){
				if(a+i-1>=n && b+i-1>=n) break;
				if(s[a+i-1]==s[b+i-1]) cnt++;
				else{
					if(!cnt) continue;
					ans+=(cnt+1)*cnt/2;
					cnt=0;
				}
			}
			ans+=(cnt+1)*cnt/2;
			writeln(ans);
		}
	}
}
signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(nullptr),cout.tie(nullptr);
	//int t;t=read();
	//while(t--)
	solve();
	return 0;
}