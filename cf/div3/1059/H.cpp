// Problem: H. Beautiful Problem
// Contest: Codeforces - Codeforces Round 1059 (Div. 3)
// URL: https://codeforces.com/contest/2162/problem/H
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int N=3010;
const int inf=1e8;//INT_MAX~2e9 INT64_MAx~9e18

int n,m;
int a[N],dp[N][N][2],mxr[N];
// dp[cnt_interval][cnt_s][type(0-s,1-b)]==cnt_b

struct seg{
	int l,r;
	seg(){}
	seg(int l,int r):l(l),r(r){}
	int len(){
		if(l==inf) return 0;
		return r-l+1;
	}
};
seg getins(seg x,seg y){
	if(x.l>y.l) swap(x,y);
	if(x.r<y.l) return seg(inf,inf);
	if(x.r<y.r) return seg(y.l,x.r);
	else return y;
}

void init(){
	cin>>n>>m;
	for(int i=0;i<=n;i++) mxr[i]=0;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,l,r;i<=m;i++){
		cin>>l>>r;
		mxr[l]=max(mxr[l],r);
	}
	for(int i=0;i<=n+4;i++){
		for(int j=0;j<=n+4;j++){
			dp[i][j][0]=dp[i][j][1]=-inf;
		}
	}
}

void solve(){
	init();
	int sz,cfree=0;
	vector<int> tag(n+4);
	vector<seg> vs;
	for(int i=1;i<=n;i++){
		if(!mxr[i]) continue;
		
		if(vs.empty() || vs.back().r<mxr[i]){
			vs.push_back(seg(i,mxr[i]));
			for(int j=i;j<=mxr[i];j++) tag[j]=1;
		}
	}
	for(int i=1;i<=n;i++) if(!tag[i]) cfree++;
	
	sz=vs.size();
	dp[1][0][0]=vs[0].len();
	dp[1][vs[0].len()][1]=0;
	for(int i=2;i<=sz;i++){
		seg cur=vs[i-1],ins=getins(vs[i-2],vs[i-1]);
		int len_ins=ins.len();
		for(int j=0;j<=n;j++){
			dp[i][j][0]=max(dp[i][j][0],dp[i-1][j][0]+cur.len()-len_ins);
			if(j+len_ins<=n) dp[i][j][0]=max(dp[i][j][0],dp[i-1][j+len_ins][1]+cur.len()-len_ins);
			if(j-(cur.len()-len_ins)>=0){
				dp[i][j][1]=max(dp[i][j][1],dp[i-1][j-(cur.len()-len_ins)][1]);
				dp[i][j][1]=max(dp[i][j][1],dp[i-1][j-(cur.len()-len_ins)][0]-len_ins);
			}
		}
	}
	
	for(int i=1;i<=n;i++){
		int flg=0;
		int s=0,b=0;
		for(int j=1;j<=n;j++){
			if(a[j]>i) b++;
			else if(a[j]<i) s++;
		}
		for(int j=0;j<=n;j++){//cnt_s => cnt_b
			int need1=max(0,s-j),need2=max(0,b-max(dp[sz][j][0],dp[sz][j][1]));
			if(cfree-need1-need2>=0){
				flg=1;
				break;
			}
		}
		cout<<flg;
	}
	cout<<"\n";
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--) solve();
	return 0;
}