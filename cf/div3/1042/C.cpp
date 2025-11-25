// Problem: C. Make it Equal
// Contest: Codeforces - Codeforces Round 1042 (Div. 3)
// URL: https://codeforces.com/contest/2131/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define endl '\n'
#define pii pair<int,int>
#define x first
#define y second

bool cmp(pii &a,pii &b){
	int l=min(a.x,a.y),r=min(b.x,b.y);
	return l<r;
}

inline void solve(){
	int n,k;cin>>n>>k;
	vector<pii> s(n+1),t(n+1);
	for(int i=1;i<=n;i++){
		cin>>s[i].x;
		s[i].x%=k;
		s[i].y=-(s[i].x-k);
	}
	sort(s.begin()+1,s.end(),cmp);
	for(int i=1;i<=n;i++){
		cin>>t[i].x;
		t[i].x%=k;
		t[i].y=-(t[i].x-k);
	}
	sort(t.begin()+1,t.end(),cmp);
	int f=1;
	for(int i=1;i<=n;i++)
		if(s[i].x!=t[i].x && s[i].y!=t[i].x && s[i].x!=t[i].y && s[i].y!=t[i].y){
			f=0;
			break;
		}
	if(f) cout<<"YES";
	else cout<<"NO";
	cout<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}