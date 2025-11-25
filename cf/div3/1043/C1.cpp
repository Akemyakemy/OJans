// Problem: C1. The Cunning Seller (easy version)
// Contest: Codeforces - Codeforces Round 1043 (Div. 3)
// URL: https://codeforces.com/contest/2132/problem/C1
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
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
		ll n;cin>>n;
		ll min_k=0;
		ll min_cost=0;
		int sz=0;
		while(n){//3进制的唯一性
			min_k+=n%3;
			min_cost+=(n%3)*cost[sz];
			n/=3;
			sz++;
		}
		cout<<min_cost<<'\n';
	}
	return 0;
}