// Problem: G. Buratsuta 3
// Contest: Codeforces - Codeforces Round 1054 (Div. 3)
// URL: https://codeforces.com/contest/2149/problem/G
// Memory Limit: 256 MB
// Time Limit: 4500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int N=2e5+5;

// #define debug

// #define random   //随机化
// #define master_tree  //主席树
#define sqrt_div   //根号分治(目前有问题)
#define go_queue    //回滚莫队
void solve(){
	int n,q;cin>>n>>q;
	vector<int> a(n+1);
	for(int i=1;i<=n;i++) cin>>a[i];
	vector<int> l(q+1),r(q+1);
	for(int i=1;i<=q;i++) cin>>l[i]>>r[i];
	
	#ifdef random
	
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	auto rnd_=[&](int a,int b){
		return rnd()%(b-a+1)+a;
	};
	
	auto tmp=a;
	sort(tmp.begin()+1,tmp.end());
	vector pos(n+1,vector<int>());
	vector<int> b(n+1);
	for(int i=1;i<=n;i++){
		b[i]=a[i];
		a[i]=lower_bound(tmp.begin()+1,tmp.end(),a[i])-tmp.begin();
		pos[a[i]].push_back(i);
	}
	
	for(int i=1;i<=q;i++){
		set<int> st,res;
		for(int j=1;j<=100;j++){
			int p=rnd_(l[i],r[i]);
			int cnt=--upper_bound(pos[a[p]].begin(),pos[a[p]].end(),r[i]) - lower_bound(pos[a[p]].begin(),pos[a[p]].end(),l[i])+1;
			if(cnt>(r[i]-l[i]+1)/3 && !st.count(a[p])) st.insert(a[p]),res.insert(b[p]);
		}
		
		if(st.size()==0) cout<<-1<<endl;
		else{
			for(int x:res) cout<<x<<" ";
			cout<<endl;
		}
	}
	
	#elif defined(master_tree)
	
	#define lc(x) tr[x].l
	#define rc(x) tr[x].r
	
	class HJTree{
		public:
		struct node{
			int l,r,s;
		};
		vector<node> tr;
		vector<int> b,rt,ans;
		int tot,n,bn;
		HJTree(int n,const vector<int>& a):tot(0),n(n){
			// a 1-base
			rt.resize(n+5);
			tr.resize(50*n);
			b.resize(n);
			//空间是2*n+(ceil(log2(n))+1)*n
			b.assign(a.begin()+1,a.end());
			sort(b.begin(),b.end());
			b.erase(unique(b.begin(),b.end()),b.end());
			bn=b.size();
			bd(rt[0],1,bn);
			for(int i=1;i<=n;i++) ins(rt[i-1],rt[i],1,bn,getid(a[i]));
		};
		
		int getid(int x){return lower_bound(b.begin(),b.end(),x)-b.begin()+1;}
		
		void bd(int& x,int l,int r){
			x=++tot;tr[x].s=0;
			if(l==r) return ;
			int m=(l+r)>>1;
			bd(lc(x),1,m);
			bd(rc(x),m+1,r);
		}
		
		void ins(int x,int& y,int l,int r,int tar){
			y=++tot;tr[y]=tr[x];tr[y].s++;
			if(l==r) return ;
			int m=(l+r)>>1;
			if(tar<=m) ins(lc(x),lc(y),l,m,tar);
			else ins(rc(x),rc(y),m+1,r,tar);
		}
		
		void qry(int x,int y,int l,int r,int tar){
			if(tr[y].s-tr[x].s<=tar) return ;
			if(l==r){
				ans.push_back(b[l-1]);
				return ;
			}
			int m=(l+r)>>1;
			qry(lc(x),lc(y),l,m,tar);
			qry(rc(x),rc(y),m+1,r,tar);
		}
		
		void qry(int l,int r,int k){
			ans.clear();
			qry(rt[l-1],rt[r],1,bn,k);
		}
	};
	
	HJTree tr(n,a);
	for(int i=1;i<=q;i++){
		tr.qry(l[i],r[i],(r[i]-l[i]+1)/3);
		if(tr.ans.empty()) cout<<"-1\n";
		else{
			sort(tr.ans.begin(),tr.ans.end());
			for(auto x:tr.ans) cout<<x<<" ";
			cout<<"\n";
		}
	}
	#elif defined(sqrt_div)
	
	int vis[N],ct[N],pre[230][N];
	auto b=a;
	sort(b.begin()+1,b.end());
	b.erase(unique(b.begin()+1,b.end()),b.end());
	int k=b.size()-1;
	map<int,int> mp;
	vector<int> ts(k+1),cnt(k+1);
	
	for(int i=1;i<=k;i++){
		mp[b[i]]=i;
		ts[i]=b[i];
	}
	for(int i=1;i<=n;i++){
		a[i]=mp[a[i]];
		cnt[a[i]]++;
	}
	
	int lim=2*sqrt(n);
	int dis=lim*3;
	vector<int> big;
	for(int i=1;i<=k;i++){
		if(cnt[i]>=lim) big.push_back(i);
	}
	int mxk=big.size();
	for(int i=1;i<=n;i++){
		for(int j=0;j<mxk;j++){
			pre[j][i]=(a[i]==big[j]);
		}
	}
	for(int j=0;j<mxk;j++){
		for(int i=1;i<=n;i++){
			pre[j][i]+=pre[j][i-1];
		}
	}
	
	for(int _=1;_<=q;_++){
		int len=r[_]-l[_]+1;
		int need=len/3;
		vector<int> ans;
		if(len>=dis){
			for(int i=0;i<mxk;i++){
				int cur_cnt=pre[i][r[_]]-pre[i][l[_]];
				if(cur_cnt>need) ans.push_back(ts[big[i]]);
			}
		}else{
			for(int i=l[_];i<=r[_];i++){
				ct[a[i]]++;
				if(ct[a[i]]>need && !vis[a[i]]){
					vis[a[i]]=1;
					ans.push_back(ts[a[i]]);
				}
			}
			for(int i=l[_];i<=r[_];i++){
				vis[a[i]]=0;
				ct[a[i]]=0;
			}
		}
		
		if(ans.empty()) cout<<-1<<endl;
		else{
			sort(ans.begin(),ans.end());
			for(auto x:ans) cout<<x<<" ";
			cout<<endl;
		}
	}
	#elif defined(go_queue)
	#endif
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);cout.flush();
	int t;cin>>t;
	while(t--)
	solve();
	return 0;
}