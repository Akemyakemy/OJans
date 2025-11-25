// Problem: Determinant of 01-Matrix
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108301/D
// Memory Limit: 2048 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <algorithm>
#include <vector>
#include <utility>
#include <cstring>
#include <map>
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#define ll long long
#define PII pair<int,int>
 
//#define int long long
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
#pragma GCC optimize optimize ("unroll-loops")
using namespace std;
 
const int N=1e6+50;
const int INF=1e9;
const int Mod=1e9+7;
int n,m;
int a[125][125]={};
void solve(){
    cin>>n;
    cout<<125<<'\n';
    for (int i = 1; i <= 124; i++) {
        a[i][i]=a[i][i-1]=1;
    }
    for (int i = 0; i <= 124; i+=4) {
        a[i+3][i]=1;//1 2 4
        a[0][i]=(n>>(i/4))&1;
    }
    for (int i = 0; i <= 124; i++) {
        for (int j = 0; j <=124 ; j++) {
            cout<<a[i][j]<<" ";
        }
        cout<<'\n';
    }
}
signed main(){
   ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
   int t=1;
   //cin>>t;
   while(t--){
       solve();
   }
}