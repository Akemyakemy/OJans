// Problem: E. Mexification
// Contest: Codeforces - Codeforces Round 1047 (Div. 3)
// URL: https://codeforces.com/contest/2137/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define endl '\n'

void solve(){
	int n,k;cin>>n>>k;
	vector<int> a(n+1);
	for(int i=1;i<=n;i++) cin>>a[i];
	vector<int> l,sl;
	sort(a.begin(),a.end());
	
	while(k && l!=a){
		k--;
		sl=l;
		l=a;
		vector<int> f(n+1);
		for(int i=1;i<=n;i++) f[a[i]]++;
		vector<int> b(n+1);
		int mex=0;
		while(f[mex]) mex++;
		int mm=0;
		for(int i=1;i<=n;i++){
			if(f[a[i]]>1) b[i]=mex;
			else b[i]=mm;
			if(a[i]==mm) mm++;
		}
		sort(b.begin(),b.end());
		a=b;
		if(a==sl) k&=1;
	}
	int sum=0;
	for(int i=1;i<=n;i++) sum+=a[i];
	cout<<sum<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}