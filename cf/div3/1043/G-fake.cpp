// Problem: G. Famous Choreographer
// Contest: Codeforces - Codeforces Round 1043 (Div. 3)
// URL: https://codeforces.com/contest/2132/problem/G
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
// typedef long long ll;
#define int long long
#define endl '\n'
#define pii pair<int,int>

const int mod=998244353;
const int p[2]={271,61};
int bp[2];
vector<int> pows[2],bpows[2];

int bin_pow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=(1ll*res*a)%mod;
		a=(1ll*a*a)%mod;
		b>>=1; 
	}
	return res;
}

inline int add(int a,int b){
	int res=a+b;
	if(res>=mod) res-=mod;
	return res;
}

inline int sub(int a,int b){
	int res=a-b;
	if(res<0) res+=mod;
	return res;
}

inline int mult(int a,int b){
	int res=1ll*a*b%mod;
	return (1ll*res%mod+mod)%mod;
}

void init(){
	bp[0]=bin_pow(p[0],mod-2);
	bp[1]=bin_pow(p[1],mod-2);
	
	for(int j=0;j<2;j++){
		pows[j].resize(1e6,1);
		bpows[j].resize(1e6,1);
		for(int i=1;i<1e6;i++){
			pows[j][i]=mult(pows[j][i-1],p[j]);
			bpows[j][i]=mult(bpows[j][i-1],bp[j]);
		}
	}
}

inline void solve(){
	int n,m;cin>>n>>m;
	
	vector<string> f(n);
	for(int i=0;i<n;i++) cin>>f[i];
	
	vector<vector<int>> hash(n+2,vector<int>(m+2,0));
	vector<vector<int>> bhash(n+2,vector<int>(m+2,0));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int cur=mult((f[i-1][j-1]-'a'+1),mult(pows[0][i-1],pows[1][j-1]));
			hash[i][j]=add(sub(add(hash[i-1][j],hash[i][j-1]),hash[i-1][j-1]),cur);
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
			int cur=mult((f[i-1][j-1]-'a'+1),mult(pows[0][n-i],pows[1][m-j]));
			bhash[i][j]=add(sub(add(bhash[i+1][j],bhash[i][j+1]),bhash[i+1][j+1]),cur);
		}
	}
	auto isp=[&](int x,int y,int xx,int yy){
		int hsh=add(sub(sub(hash[xx][yy],hash[x-1][yy]),hash[xx][y-1]),hash[x-1][y-1]);
		int bhsh=add(sub(sub(bhash[x][y],bhash[xx+1][y]),bhash[x][yy+1]),bhash[xx+1][yy+1]);
		hsh=mult(hsh,mult(bpows[0][x-1],bpows[1][y-1]));
		bhsh=mult(bhsh,mult(bpows[0][n-xx],bpows[1][m-yy]));
		return hsh==bhsh;
	};
	
	int mn=1ll*n*m*4;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(isp(1,1,i,j)) mn=min(mn,(2*n-i)*(2*m-j));
			if(isp(1,j,i,m)) mn=min(mn,(2*n-i)*(m+j-1));
			if(isp(i,1,n,j)) mn=min(mn,(n+i-1)*(2*m-j));
			if(isp(i,j,n,m)) mn=min(mn,(n+i-1)*(m+j-1));
		}
	}
	cout<<mn-n*m<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	
	init();
	
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}