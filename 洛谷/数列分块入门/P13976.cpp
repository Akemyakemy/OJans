// Problem: P13976 数列分块入门 1
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P13976
// Memory Limit: 512 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int N=3e5+9;

int L[N],R[N],pos[N],cnt,B,n;
vector<int> a;

void bd(){
	cin>>n;
	B=sqrt(n);
	a.assign(n+1,0);
	for(int i=1;i<=n;i++) cin>>a[i];
	while(1){
		cnt++;
		L[cnt]=(cnt-1)*B+1;
		R[cnt]=cnt*B;
		if(R[cnt]>=n){
			R[cnt]=n;
			// for(int i=L[i];i<=R[i];i++) pos[i]=cnt;
			break;
		}
		// for(int i=L[i];i<=R[i];i++) pos[i]=cnt;
	}
	
	for(int i=1;i<=cnt;i++){//这部分可以直接计算得出,如果计算就可以直接不用这部分
		for(int j=L[i];j<=R[i];j++){
			pos[j]=i;
		}
	}
}

int tag[N];
void update(int l,int r,int x){
	if(pos[l]==pos[r]){
		for(int i=l;i<=r;i++) a[i]+=x;
		return;
	}
	
	for(int i=l;i<=R[pos[l]];i++) a[i]+=x;
	for(int i=L[pos[r]];i<=r;i++) a[i]+=x;
	for(int i=pos[l]+1;i<pos[r];i++) tag[i]+=x;
}

int query(int x){return a[x]+tag[pos[x]];}
void solve(){
	bd();
	
	for(int i=0,op,l,r,c;i<n;i++){
		cin>>op>>l>>r>>c;
		
		if(op){
			cout<<query(r)<<endl;
			
		}else{
			update(l,r,c);
		}
	}
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	// int t;cin>>t;
	// while(t--)
	solve();
	return 0;
}