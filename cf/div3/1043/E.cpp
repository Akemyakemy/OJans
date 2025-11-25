// Problem: E. Arithmetics Competition
// Contest: Codeforces - Codeforces Round 1043 (Div. 3)
// URL: https://codeforces.com/contest/2132/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define endl '\n'
#define pii pair<int,int>

int n,m,q;
vector<int> a,b,sa,sb;
int x,y,z;
vector<pii> ans;

void init(){
	cin>>n>>m>>q;
	
	a.resize(n+1);sa.resize(n+1);
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a.begin()+1,a.end(),greater<int>());
	for(int i=1;i<=n;i++) sa[i]=sa[i-1]+a[i];
	
	b.resize(m+1);sb.resize(m+1);
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(b.begin()+1,b.end(),greater<int>());
	for(int i=1;i<=m;i++) sb[i]=sb[i-1]+b[i];
	
	// ans[z]={l,r} 选z张的最优解，a有l张，b有r张
	ans.resize(n+m+1);
	int l=0,r=0;
	for(int i=1;i<ans.size();i++){
		if(l<n && r<m) 
			if(a[l+1]<b[r+1]) r++;
			else l++;
		else if(l==n) r++;
		else if(r==m) l++;
		ans[i]={l,r};
	}
}

inline void solve(){
	init();
	while(q--){
		cin>>x>>y>>z;
		
		int l=ans[z].first,r=ans[z].second;
		if(l>x) cout<<sa[x]+sb[z-x]<<endl;
		else if(r>y) cout<<sa[z-y]+sb[y]<<endl;
		else cout<<sa[l]+sb[r]<<endl;
	}
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}