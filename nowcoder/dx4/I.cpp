// Problem: I, Box
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/I
// Memory Limit: 2048 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
const int MAXN=55,gx[4]={1,-1,0,0},gy[4]={0,0,1,-1},MAXQ=5e5;
const char direct[4]={'D','U','R','L'};
 
int ba[MAXN][MAXN],opque[MAXQ][3],cnt=0;
bool cvis[MAXN][MAXN];
 
void solve(){
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;++i){
        string ch;cin>>ch;
        for(int j=0;j<m;++j){
            if(ch[j]=='#') ba[i][j+1]=4;
            else if(ch[j]=='.') ba[i][j+1]=0;
            else if(ch[j]=='@') ba[i][j+1]=2;
            else if(ch[j]=='*') ba[i][j+1]=1;
            else ba[i][j+1]=3;
        }
    }
    auto outrange=[&](int x,int y){ return x>n||x<1||y>m||y<1; };
    auto check1=[&](int x,int y)->bool{
        int box=0,tar=0;
        queue <array<int,2>> que;
        que.push({x,y});
        while(!que.empty()){
            auto [cux,cuy]=que.front();que.pop();
            if(cvis[cux][cuy]) continue;
            cvis[cux][cuy]=true;
            box+=(ba[cux][cuy]&2)/2;
            tar+=ba[cux][cuy]&1;
            for(int i=0,nx,ny;i<4;++i){
                nx=cux+gx[i];ny=cuy+gy[i];
                if(outrange(nx,ny)||cvis[nx][ny]||ba[nx][ny]&4) continue;
                que.push({nx,ny});
            }
        }
        return box==tar;
    };
     
    auto bfs=[&](int stx,int sty)->void{
        queue <array<int,2>> que;
        stack <array<int,3>> sta;
        vector <vector <int>> di(n+1,vector <int>(m+1,0));
        vector <vector <bool>> vis(n+1,vector <bool>(m+1,0));
        que.push({stx,sty});
        int enx,eny;
        while(!que.empty()){
            auto [cux,cuy]=que.front();que.pop();
            if(vis[cux][cuy]) continue;
            vis[cux][cuy]=1;
            if(ba[cux][cuy]==1){ enx=cux,eny=cuy;break; }
            for(int i=0,nx,ny;i<4;++i){
                nx=cux+gx[i],ny=cuy+gy[i];
                if(outrange(nx,ny)||vis[nx][ny]||ba[nx][ny]&4) continue;
                que.push({nx,ny});
                di[nx][ny]=i^1;
            }
        }
        while(enx!=stx||eny!=sty){
            sta.push({enx,eny,di[enx][eny]^1});
            int gxx=gx[di[enx][eny]],gyy=gy[di[enx][eny]];
            enx+=gxx;eny+=gyy;
        }
        bool f=false;
        while(!sta.empty()){
            auto [nex,ney,dip]=sta.top();sta.pop();
            // cout<<nex<<" "<<ney<<"\n";
            opque[++cnt][0]=stx;opque[cnt][1]=sty;opque[cnt][2]=dip;
            if(ba[nex][ney]&2){
                if(f){
                   for(int i=cnt,kcnt=0;i>=2;--i){
                        if(ba[opque[i-1][0]][opque[i-1][1]]&2){
                            swap(opque[i],opque[i-1]);
                        }else{
                            if(kcnt++) break;
                            swap(opque[i],opque[i-1]);
                        }
                    }
                }
                if(!f){ f=true;ba[stx][sty]^=2; }
            }else{
                if(f){
                    for(int i=cnt,kcnt=0;i>=2;--i){
                        if(ba[opque[i-1][0]][opque[i-1][1]]&2){
                            swap(opque[i],opque[i-1]);
                        }else{
                            if(kcnt++) break;
                            swap(opque[i],opque[i-1]);
                        }
                    }
                    f=false; 
                }
                else{ ba[stx][sty]^=2; }
                ba[nex][ney]^=2;
            }
            stx=nex;sty=ney;
        }
    };
     
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(!(ba[i][j]&4)&&!cvis[i][j]){
                if(!check1(i,j)){
                    cout<<-1<<"\n";
                    return ;
                }
            }
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(ba[i][j]==2){
                bfs(i,j);
            }
        }
    }
    cout<<cnt<<"\n";
    for(int i=1;i<=cnt;i++){
        cout<<opque[i][0]<<" "<<opque[i][1]<<" "<<direct[opque[i][2]]<<"\n";
    }
}
 
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int _=1;while(_--) solve();
    return 0;
}