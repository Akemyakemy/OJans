// Problem: D. From 1 to Infinity
// Contest: Codeforces - Codeforces Round 1043 (Div. 3)
// URL: https://codeforces.com/contest/2132/problem/D
// Memory Limit: 256 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define endl '\n'

// int pre[]={45,9495,142200,1894500,23670000,283950000,3312000000,37845000000};

inline void solve(){
	int k;cin>>k;
	int cur=9,len=1;
	int ans=0;
	while(k-cur*len>0){
		// ans+=pre[len-1];
		k-=cur*len;
		cur*=10;
		len++;
	}
	string s=to_string(cur/9 + (k-1)/len);
	
	for(int i=0;i<(k-1)%len+1;i++) ans+=s[i]-'0';
	int pr_s=0;
	for(int i=0;i<s.size();i++){
		int curd=s[i]-'0';
		if(curd) ans+=curd*(2*pr_s+curd-1)/2*cur/9+curd*(len-1)*cur/2;
		cur/=10,len--;
		pr_s+=curd;
	}
	cout<<ans<<endl;
	// int sum=0;
	// for(int i=10000000;i<=99999999;i++){
		// string s=to_string(i);
		// for(char c:s){
			// sum+=(int) c;
		// }
	// }
	// cout<<sum;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}