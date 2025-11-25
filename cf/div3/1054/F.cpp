// Problem: F. Nezuko in the Clearing
// Contest: Codeforces - Codeforces Round 1054 (Div. 3)
// URL: https://codeforces.com/contest/2149/problem/F
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long

// #define debug
// #define brute
#define true_solution
void solve(){
	#ifdef brute
	ll h,d;cin>>h>>d;
	int p=0;
	ll ans=0,cost=0;
	while(p<d){
		int k=0;
		while(cost+(k+1)<h && p<d){
			k++;
			cost+=k;
			p++;
			ans++;
		}
		if(p==d) break;
		h++;
		ans++;
		#ifdef debug
		cout<<ans<<endl;
		#endif
	}
	cout<<ans<<endl;
	#ifdef debug
	cout<<endl;
	#endif
	#elif defined(true_solution)
	int h,d;cin>>h>>d;
	
	//mid 是休息次数，需要走（mid+1）次，每次期望走d/(mid+1)步，少的部分走d/(mid+1)+1步
	auto check=[&](int mid){
		int w1=d/(mid+1);
		int w2=d/(mid+1)+1;
		int cost1=w1*(w1+1)/2;
		int cost2=w2*(w2+1)/2;
		int b2=d%(mid+1),b1=mid+1-b2;
		
		#ifdef debug
		// cout<<mid<<" "<<b2*cost2+b1*cost1<<" "<<h+mid<<" ";
		cout<<b1<<" "<<w1<<" "<<cost1<<" "<<b2<<" "<<w2<<" "<<cost2<<endl;
		#endif
		return b2*cost2+b1*cost1<h+mid;
	};
	
	int l=0,r=d;
	while(l<r){
		int mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid+1;
		#ifdef debug
		cout<<l<<" "<<r<<endl;
		#endif
	}
	
	cout<<r+d<<endl;
	#ifdef debug
	cout<<endl;
	#endif
	#else
	ll h,d;cin>>h>>d;
	if(d*(d+1)/2<h){
		cout<<d<<endl;
		return ;
	}
	ll ans=0,p=0;
	if(h==2){
		ans++;
		p++;
	}
	while(h>2){
		if(ans){
			h++;
			ans++;
		}
		#ifdef debug
		cout<<ans<<endl;
		#endif
		ll x=(-1+sqrt(1+8*h))/2;
		if(x*(x+1)/2==h) x--;
		h-=x*(x+1)/2;
		ans+=x;
		p+=x;
	}
	assert(h>0);
	cout<<ans+(d-p)*2<<endl;
	#ifdef debug
	cout<<endl;
	#endif
	#endif
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}