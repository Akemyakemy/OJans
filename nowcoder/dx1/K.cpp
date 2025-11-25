// Problem: Museum Acceptance
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108298/K
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f
#define maxn 200009

inline int read(){//手动读取数据更加快速
    int sum=0,d=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')d=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        sum=sum*10+c-'0';
        c=getchar();
    }
    return sum*d;
}

int n,d[maxn][4],ans[maxn*3],fa[maxn*3],rid[maxn*3];
int nt[maxn*3],id[maxn][4],tot=0;
bool vis[maxn*3];

void dfs(int u,int f){
	if(vis[u]) return;
	vis[u]=true;fa[u]=f;ans[f]++;
	if(fa[rid[u]]==f) ans[f]--;
	dfs(nt[u],f);
	return;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++){
		d[i][0]=read();
		for(int j=1;j<=d[i][0];j++){
			d[i][j]=read();
			id[i][j]=++tot;
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=d[i][0];j++){
			int rj=0,v=d[i][j];
			for(int k=1;k<=d[v][0];k++)
				if(d[v][k]==i) rj=k;
			nt[id[i][j]]=id[v][rj%d[v][0]+1];
			rid[id[i][j]]=id[v][rj];
		}
	for(int i=1;i<=tot;i++) if(!vis[i]) dfs(i,i);
	for(int i=1;i<=n;i++) cout<<ans[fa[id[i][1]]]<<endl;
	return 0;
}