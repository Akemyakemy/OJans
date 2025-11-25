// Problem: Identical Somehow
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108299/I
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int M = 2e5 + 20;
 
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
 
    int T;cin >> T;
    while(T--){
        int a,b;cin >> a>>b;
        if(a>1&&b>1)cout<<1<<'\n';
        else cout<<-1<<'\n';
    }
    return 0;
}//找规律