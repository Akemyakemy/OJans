// Problem: Endless Ladders
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108298/E
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf=0x3f3f3f3f;

int main(){
	int t;cin>>t;
	while(t--){
		ll a,b;cin>>a>>b;
		ll c=abs(b*b-a*a);
		cout<<(c-1)/2+max(c/4-1,0ll)<<endl;
	}
	return 0;
}