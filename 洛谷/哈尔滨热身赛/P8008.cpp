// Problem: P8008 「Wdsr-3」迷途竹林
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8008
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf=2147483647;
const int N=1e6+3;
double x[N],y[N],a,o,ans;

void solve(){
	int n;cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	cin>>o>>a,o=o/180*acos(-1),a*=sin(o);
	
	for(int i=1;i<=n;i++){
		double xx=x[i],yy=y[i];
		double l=sqrt(pow(xx,2)+pow(yy,2)),b=atan2(yy,xx);
		b-=o,xx=l*cos(b),yy=l*sin(b),x[i]=xx-1e-9,y[i]=yy-1e-9;
	}
	x[n+1]=x[1],y[n+1]=y[1];
	
	for(int i=1;i<=n;i++){
		double u,v;
		if(y[i]<y[i+1]) u=ceil(y[i]/a)*a,v=floor(y[i+1]/a)*a;
		else u=ceil(y[i+1]/a)*a,v=floor(y[i]/a)*a;
		double xx,yy,w=(v-u)/a+1;
		xx=(u-y[i])/(y[i+1]-y[i])*(x[i+1]-x[i])+x[i];
		yy=(v-y[i])/(y[i+1]-y[i])*(x[i+1]-x[i])+x[i];
		if(y[i]>y[i+1]) ans+=(xx+yy)*w/2;
		else ans-=(xx+yy)*w/2;
	}
	printf("%.10lf\n",ans);
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	// int t;cin>>t;
	// while(t--)
	solve();
	return 0;
}