// Problem: Museum Construction
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108298/J
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define M 200005
using namespace std;
int n,d[M][4];
bool vis[M][4],in[M][4];
struct cpp{
    int x,now;
};
queue<cpp>Q;
int find(int x,int y){
    for(int i=1;i<=3;i++)if(d[x][i]==y)return i;
    return 0;
}
void dfs(int x,int now){
//  cout<<x<<' '<<now<<'\n';
    if(vis[x][now])return ;
    vis[x][now]=1;
    int ne=find(d[x][now],x);
    in[d[x][now]][ne]=1;
    ne=ne%d[d[x][now]][0]+1;
    Q.push((cpp){d[x][now],ne});
    dfs(d[x][now],ne);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>d[i][0];
        for(int j=1;j<=d[i][0];j++){
            cin>>d[i][j];
        }
    }
    Q.push((cpp){1,1});
//  cout<<1<<"___\n";
    dfs(1,1);
    while(Q.size()){
        int x=Q.front().x,now=Q.front().now;
        Q.pop();
        if(d[x][0]<3){
            if(d[x][0]==2){
                if(now==2){
                    swap(d[x][1],d[x][2]);
                    swap(vis[x][1],vis[x][2]);
                }
            }
            continue;
        }
        if(vis[x][1]&&(vis[x][2]|vis[x][3]))continue;
        if(now==1){
            if(in[x][2]){
                swap(d[x][3],d[x][2]);
                swap(vis[x][3],vis[x][2]);
                swap(in[x][3],in[x][2]);
                dfs(x,2);
            }
            else {
                swap(d[x][3],d[x][2]);
                swap(vis[x][3],vis[x][2]);
                swap(in[x][3],in[x][2]);
                dfs(x,3);
            }
        }
        else {
            if(vis[x][2]&&vis[x][3]){
                swap(d[x][3],d[x][1]);
                swap(vis[x][3],vis[x][1]);
                swap(in[x][3],in[x][1]);
                 
                swap(d[x][1],d[x][2]);
                swap(vis[x][1],vis[x][2]);
                swap(in[x][1],in[x][2]);
            }
            else {
                int to=5-now;
                if(in[x][1]){
                    swap(d[x][to],d[x][1]);
                    swap(vis[x][to],vis[x][1]);
                    swap(in[x][to],in[x][1]);
                    dfs(x,1);
                }
                else {
                    swap(d[x][to],d[x][1]);
                    swap(vis[x][to],vis[x][1]);
                    swap(in[x][to],in[x][12]);
                    dfs(x,to);
                }
            }
        }
//      if(now!=1){
//          swap(d[x][3],d[x][2]);
//          swap(vis[x][3],vis[x][2]);
//          swap(in[x][3],in[x][2]);
//          swap(d[x][1],d[x][now]);
//          swap(vis[x][1],vis[x][now]);
//          swap(in[x][1],in[x][now]);
//          now=1;
//      }
//      if(in[x][2]){
//          swap(d[x][3],d[x][2]);
//          swap(vis[x][3],vis[x][2]);
//          swap(in[x][3],in[x][2]);
//          dfs(x,2);
//      }
//      else {
//          
//          swap(d[x][3],d[x][2]);
//          swap(vis[x][3],vis[x][2]);
//          swap(in[x][3],in[x][2]);
//          dfs(x,3);
//      }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=d[i][0];j++){
            cout<<d[i][j]<<' ';
        }cout<<'\n';
    }
}