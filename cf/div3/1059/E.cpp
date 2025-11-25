#include<bits/stdc++.h>
using namespace std;
void solve(){
	int n,k;cin>>n>>k;
	vector<int> a(n+1),cnt(n+1,0);
	for(int i=1;i<=n;i++) cin>>a[i],cnt[a[i]]++;
	int x=-1;
	for(int i=1;i<=n;i++) if(cnt[i]==0){
		x=i;
		break;
	}
	if(x==-1){
		for(int i=0;i<k;i++) cout<<a[n-2+(i%3)]<<" ";
		cout<<"\n";
	}else{
		int y=-1;
		for(int i=1;i<=n;i++) if(i!=x &&i!=a[n]){
			y=i;
			break;
		}
		vector<int> v={x,y,a[n]};
		for(int i=0;i<k;i++) cout<<v[i%3]<<" ";
		cout<<"\n";
	}
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}