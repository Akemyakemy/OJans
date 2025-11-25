// Problem: Field of Fire
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/F
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define pd push_back
#define pb emplace_back
#define ll long long
#define IOS ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
//#define int long long
#define pii pair<int,int>
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
using namespace std;
const int N=100005; 
int main(){IOS; 
    int T=1;
    cin>>T;
    while(T--){
        int n,t;
        string str;
        cin>>n>>t>>str;
        vector<int> one(n+5);
        int p=0;//前面0的个数
        int cnt=0;//当前是第cnt个1 
        int j=0,ma=0;
        For(i,0,n-1){
            if(str[i]=='1'){
                one[++cnt]=p;
                if(p>ma)ma=p,j=cnt;
                p=0;
            }else p++;
        }
        if(cnt>=1){one[1]+=p;if(one[1]>ma)ma=one[1],j=1;}
        //For(i,1,cnt)cout<<one[i].x<<" "<<one[i].l<<" "<<one[i].r<<"\n"; 
        int res=0;//记录未烧毁的最大数量 
        if(ma<=t+1){
            cout<<0<<"\n";
        }else{
            For(i,1,cnt){
                if(j==i)res+=ma-t-1;
                else res+=max(0,one[i]-2*t);
            }
            cout<<res<<'\n';
        }
        /*For(i,1,cnt){
            int k;
            k=one[i];
            if(i==j)res=max(res,k-t-1);
            else res=max(res,k-2*t);
        } */
    }
    return 0;
}