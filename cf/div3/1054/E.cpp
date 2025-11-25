// Problem: E. Hidden Knowledge of the Ancients
// Contest: Codeforces - Codeforces Round 1054 (Div. 3)
// URL: https://codeforces.com/contest/2149/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf=INT_MAX/2;

struct seg{
	int l,r;
	seg(){}
	seg(int l,int r):l(l),r(r){}
	int len(){
		if(l==inf) return 0;
		else return r-l+1;
	}
};
seg getins(seg x,seg y){
	if(x.l>y.l) swap(x,y);
	if(x.r<y.l) return seg(inf,inf);
	if(x.r<y.r) return seg(y.l,x.r);
	return y;
}

// #define debug
void solve(){
	ll ans=0;
	int n,k,l,r;cin>>n>>k>>l>>r;
	vector<int> a(n+1);
	for(int i=1;i<=n;i++) cin>>a[i];
	
	map<int,int> cnt;
	vector<int> lk(n+1,0),rk(n+1,0);
	int j=1;
	for(int i=1;i<=n;i++){
		int sz=cnt.size();
		cnt[a[i]]++;
		if(sz<cnt.size() && cnt.size()==k){
			while(cnt.size()==k){
				lk[j]=i;
				if(--cnt[a[j]]==0) cnt.erase(a[j]);
				j++;
			}
		}
	}
	cnt.clear();
	j=1;
	for(int i=1;i<=n;i++){
		int sz=cnt.size();
		cnt[a[i]]++;
		if(sz<cnt.size() && cnt.size()>k){
			while(cnt.size()>k){
				rk[j]=i-1;
				if(--cnt[a[j]]==0) cnt.erase(a[j]);
				j++;
			}
		}
	}
	for(int i=1;i<=n;i++) if(lk[i] && !rk[i]) rk[i]=n;
	
	for(int i=1;i<=n;i++){
		if(i+l-1>n) break;
		seg range_len=seg(i+l-1,min(n,i+r-1));
		// int lk=-1,rk=-1;
		// set<int> s;
		// for(int j=i;j<=n;j++){
			// int sz=s.size();
			// s.insert(a[j]);
			// if(sz<s.size() && s.size()==k) lk=j;
			// if(sz<s.size() && s.size()>k){
				// rk=j-1;
				// break;
			// }
			// if(lk!=-1 && rk==-1 && j==n) rk=n;
		// }
		// if(lk==-1) break;
		if(!lk[i]) break;
		seg k_len=seg(lk[i],rk[i]);
		
		seg res=getins(range_len,k_len);
		ans+=res.len();
		#ifdef debug
		cout<<range_len.l<<"/"<<range_len.r<<" "<<lk<<"/"<<rk<<endl<<res.len()<<endl;
		#endif
	}
	
	cout<<ans<<endl;
	#ifdef debug
	cout<<endl;
	#endif
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}