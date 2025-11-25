// Problem: F. Unjust Binary Life
// Contest: Codeforces - Codeforces Round 1042 (Div. 3)
// URL: https://codeforces.com/contest/2131/problem/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
// typedef long long ll;
#define int long long
#define endl '\n'
#define pii pair<int,int>

inline void solve(){
	int n;cin>>n;
	string s;
	vector<int> a(n+1,0);
	vector<int> b(n+1,0);
	vector<vector<int>> cnt0(n+1,vector<int>(2,0));
	vector<vector<int>> cnt1(n+1,vector<int>(2,0));
	vector<int> prea(n+1,0),preb(n+1,0);
	vector<int> spa(n+1,0);
	cin>>s;
	for(int i=1;i<=n;i++){
		a[i]=(s[i-1]-'0');
		cnt0[i][0]=cnt0[i-1][0]+(a[i]==0ll);
		cnt1[i][0]=cnt1[i-1][0]+(a[i]==1ll);
		prea[i]=cnt0[i][0]-cnt1[i][0];
	}
	sort(prea.begin()+1,prea.end());
	for(int i=1;i<=n;i++) spa[i]=spa[i-1]+prea[i];
	
	cin>>s;
	for(int i=1;i<=n;i++){
		b[i]=(s[i-1]-'0');
		cnt0[i][1]=cnt0[i-1][1]+(b[i]==0ll);
		cnt1[i][1]=cnt1[i-1][1]+(b[i]==1ll);
		preb[i]=cnt1[i][1]-cnt0[i][1];
	}
	
	int ans=n*(n+1)/2*n;
	int tot=0;
	for(int i=1;i<=n;i++){
		int z=preb[i];
		int pos=upper_bound(prea.begin()+1,prea.end(),z)-prea.begin()-1;
		tot+=z*pos-spa[pos]*2+spa[n]-z*(n-pos);
	}
	
	cout<<ans-tot/2<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}