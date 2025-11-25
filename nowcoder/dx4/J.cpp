// Problem: Journey Around the World
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/J
// Memory Limit: 2048 MB
// Time Limit: 16000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define eb emplace_back
const int N=210,M=610,dx[4]={0,1,0,-1},dy[4]={1,0,-1,0},inf=1e9;//RDLU
int n,w[N][M][4],dis[N][M],fl[M][3],fr[M][3],hh,tt,vis[N][M],tim,d[N][N][M];
struct node{
    int x,y;
}q[N*M<<3],tmp[N*M<<3];
inline void bfs(int bx,int by){
    ++tim;
    memset(dis,0x3f,sizeof dis);
    q[hh=tt=(N*M<<2)]=(node){bx,by};
    dis[bx][by]=0;
    while(hh<=tt){
        int sz=0,val=dis[q[hh].x][q[hh].y];
        while(hh<=tt&&val>=dis[q[hh].x][q[hh].y]) tmp[++sz]=q[hh++];
        while(sz){
            node u=tmp[sz--];
            if(vis[u.x][u.y]==tim) continue;
            vis[u.x][u.y]=tim;
            for(int i=0;i<4;++i){
                int x=u.x+dx[i],y=u.y+dy[i],t=val+w[u.x][u.y][i];
                if(!y) y=3*n;
                if(y>3*n) y=1;
                if(x>=1&&x<=n&&dis[x][y]>t){
                    dis[x][y]=t;
                    if(w[u.x][u.y][i]==1) q[--hh]=(node){x,y};
                    else q[++tt]=(node){x,y};
                }
            }
        }
    }
    if(bx==1&&by>n&&by<=2*n) for(int i=1;i<=n;++i) for(int j=1;j<=3*n;++j) d[by-n][i][j]=dis[i][j];
}
inline void sl(int x,int y){
    for(int i=x;i<=n;++i){
        for(int j=y;j<=y+n-1;++j){
            if(i==x&&j==y) dis[i][j]=0;
            else dis[i][j]=min(i>x?dis[i-1][j]+w[i][j][3]:inf,j>y?dis[i][j-1]+w[i][j][2]:inf);
        }
    }
}
inline void sr(int x,int y){
    for(int i=x;i<=n;++i){
        for(int j=y;j>=y-n+1;--j){
            if(i==x&&j==y) dis[i][j]=0;
            else dis[i][j]=min(i>x?dis[i-1][j]+w[i][j][3]:inf,j<y?dis[i][j+1]+w[i][j][0]:inf);
        }
    }
}
inline void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        for(int j=1,x;j<=n;++j){
            scanf("%d",&x);
            w[i][j][0]=w[i][j+n][0]=w[i][j+2*n][0]=x;
            w[i][j+1][2]=w[i][j+1+n][2]=w[i][j+1+2*n][2]=x;
        }
    }
    for(int i=1;i<n;++i){
        for(int j=1,x;j<=n;++j){
            scanf("%d",&x);
            w[i][j][1]=w[i][j+n][1]=w[i][j+2*n][1]=x;
            w[i+1][j][3]=w[i+1][j+n][3]=w[i+1][j+2*n][3]=x;
        }
    }
    for(int i=2;i<=n*2;++i){
        // (1,i) -> (n-1,i+n-1)
        // (1,i) -> (n,i+n-1)
        sl(1,i);
        fl[i][0]=dis[n-1][i+n-1];
        fl[i][1]=dis[n][i+n-1];
        // (2,i) -> (n,i+n-1)
        sl(2,i);
        fl[i][2]=dis[n][i+n-1];
    }
    for(int i=n+1;i<n*3;++i){
        // (1,i) -> (n-1,i-n+1)
        // (1,i) -> (n,i-n+1)
        sr(1,i);
        fr[i][0]=dis[n-1][i-n+1];
        fr[i][1]=dis[n][i-n+1];
        // (2,i) -> (n,i-n+1)
        sr(2,i);
        fr[i][2]=dis[n][i-n+1];
    }
    for(int i=n+1;i<=2*n;++i){
        bfs(1,i);
        int ans=min(d[i-n][n][i-n],d[i-n][n][i+n]);
        bfs(n,i);
        for(int j=i-n+1;j<=i;++j) ans=min({ans,d[i-n][1][j]+fl[j][0]+dis[n-1][j+n-1],d[i-n][1][j]+fl[j][1]+dis[n][j+n-1],d[i-n][2][j]+fl[j][2]+dis[n][j+n-1]});
        for(int j=i;j<=i+n-1;++j) ans=min({ans,d[i-n][1][j]+fr[j][0]+dis[n-1][j-n+1],d[i-n][1][j]+fr[j][1]+dis[n][j-n+1],d[i-n][2][j]+fr[j][2]+dis[n][j-n+1]});
        printf("%d\n",ans);
    }
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--) solve();
    return 0;
}