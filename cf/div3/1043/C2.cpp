// Problem: C2. The Cunning Seller (hard version)
// Contest: Codeforces - Codeforces Round 1043 (Div. 3)
// URL: https://codeforces.com/contest/2132/problem/C2
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// #define int long long
#define endl '\n'

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	vector<ll> cost;
	ll c=3;
	ll cnt=1;
	for(int i=0;i<21;i++){
		cost.push_back(c);
		c=3*c+cnt;
		cnt*=3;
	}
	
	int t;cin>>t;
	while(t--){
		ll n,k;
		cin>>n>>k;
		vector<ll> tr;
		ll min_k=0;
		while(n){
			tr.push_back(n%3);
			min_k+=n%3;
			n/=3;
		}
		if(min_k>k){
			cout<<-1<<'\n';
			continue;
		}
		k-=min_k;
		k/=2;
		for(int i=(int)tr.size()-1;i>=1;i--){
			if(tr[i]<=k){
				tr[i-1]+=3*tr[i];
				k-=tr[i];
				tr[i]=0;
			}else{
				tr[i-1]+=k*3;
				tr[i]-=k;
				break;
			}
		}
		ll ans=0;
		for(int i=(int)tr.size()-1;i>=0;i--) ans+=cost[i]*tr[i];
		cout<<ans<<'\n';
	}
	return 0;
}