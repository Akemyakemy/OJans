#include<bits/stdc++.h>
using namespace std;
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        vector<int> a(n+1);
        for(int i=1;i<=n;i++) cin>>a[i];
        int ans=*max_element(a.begin(),a.end());
        cout<<ans<<endl;
    }
}