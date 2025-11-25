// Problem: Symmetry Intervals
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108298/G
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=0x3f3f3f3f;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,q;cin>>n>>q;
	string s;cin>>s;
	for(int i=0;i<q;i++){
		string t;cin>>t;
		int a;cin>>a;
		int cnt=0,ans=0;
		for(int j=0;j<(int)t.size();j++){
			if(t[j]==s[a-1+j]) cnt++;
			else{
				ans+=(cnt+1)*cnt/2;
				cnt=0;
			}
		}
		ans+=(cnt+1)*cnt/2;
		cout<<ans<<endl;
	}
	return 0;
}