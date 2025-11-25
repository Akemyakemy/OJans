#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// #define int long long
#define endl '\n'

void solve(){
	int n;cin>>n;
	vector<double> a(n+1),b(n+1);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	
	double ans=0;
	for(int i=1;i<=n;i++) ans+=a[i]*b[i];
	cout<<ans<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	// int t;cin>>t;
	// while(t--)
	solve();
	return 0;
}