// Problem: P13982 数列分块入门 7
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P13982
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
const int N=3e5+9;
const int mod=1e4+7;

int n,blo,bl[N];
int v[N],add[N],mul[N];

inline void push_down(int x){
	for(int i=(x-1)*blo+1;i<=min(x*blo,n);i++)
		v[i]=(mul[x]*v[i]%mod+add[x])%mod;
	add[x]=0;
	mul[x]=1;
}

inline void add_(int a,int b,int c){
	push_down(bl[a]);
	for(int i=a;i<=min(bl[a]*blo,b);i++) v[i]=(v[i]+c)%mod;
	if(bl[a]!=bl[b]){
		push_down(bl[b]);
		for(int i=(bl[b]-1)*blo+1;i<=b;i++) v[i]=(v[i]+c)%mod;
	}
	for(int i=bl[a]+1;i<bl[b];i++) add[i]=(add[i]+c)%mod;
}

inline void multiply(int a,int b,int c){
	push_down(bl[a]);
	for(int i=a;i<=min(bl[a]*blo,b);i++) v[i]=(v[i]*c)%mod;
	if(bl[a]!=bl[b]){
		push_down(bl[b]);
		for(int i=(bl[b]-1)*blo+1;i<=b;i++) v[i]=(v[i]*c)%mod;
	}
	for(int i=bl[a]+1;i<=bl[b]-1;i++) add[i]=(add[i]*c)%mod,mul[i]=(mul[i]*c)%mod;
}

void solve(){
	cin>>n;
	blo=sqrt(n);
	for(int i=1;i<=n;i++){
		cin>>v[i];
		bl[i]=(i-1)/blo+1;
		mul[bl[i]]=1;
	}
	for(int i=1,f,a,b,c;i<=n;i++){
		cin>>f>>a>>b>>c;
		if(!f) add_(a,b,c);
		else if(f==1) multiply(a,b,c);
		else cout<<((v[b]*mul[bl[b]]%mod+add[bl[b]])%mod+mod)%mod<<endl;
	}
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	//int t;cin>>t;
	//while(t--)
	solve();
	return 0;
}