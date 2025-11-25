// Problem: 井
// Contest: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1173&pid=1008
// Memory Limit: 512000 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define bll __int128
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define fi first
#define sec second
#define vii vector<int>
#define pll pair<ll,ll>
#define vll vector<ll>
#define pii pair<int,int>
#define pil pair<int,ll>
#define re register
#define puu pair<ull,ull>
#define clr clear
#define vpi vector<pii>
#define qii queue<int>
using namespace std;
namespace io{
	const int __SIZE=(1<<22)+1;
	char ibuf[__SIZE],*iS,*iT,obuf[__SIZE],*oS=obuf,*oT=oS+__SIZE-1,__c,qu[55];int __f,qr,_eof;
#define Gc()(iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,__SIZE,stdin),(iS==iT?EOF:*iS++)):*iS++)
	inline void flush(){fwrite(obuf,1,oS-obuf,stdout),oS=obuf;}
	inline void gc(char&x){x=Gc();}
	inline void pc(char x){*oS++=x;if(oS==oT)flush();}
	inline void pstr(const char*s){int __len=strlen(s);for(__f=0;__f<__len;++__f)pc(s[__f]);}
	inline void gstr(char*s){for(__c=Gc();__c<32||__c>126||__c==' ';)__c=Gc();
		for(;__c>31&&__c<127&&__c!=' ';++s,__c=Gc())*s=__c;*s=0;}
	template<class I>inline bool read(I&x){_eof=0;
		for(__f=1,__c=Gc();(__c<'0'||__c>'9')&&!_eof;__c=Gc()){if(__c=='-')__f=-1;_eof|=__c==EOF;}
		for(x=0;__c<='9'&&__c>='0'&&!_eof;__c=Gc())x=x*10+(__c&15),_eof|=__c==EOF;x*=__f;return!_eof;}
	template<class I>inline void write(I x){if(!x)pc('0');if(x<0)pc('-'),x=-x;
		while(x)qu[++qr]=x%10+'0',x/=10;while(qr)pc(qu[qr--]);}
	struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}using io::pc;using io::gc;using io::pstr;using io::gstr;using io::read;using io::write;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		double ans=1.0*n*3/2;
		printf("%.4lf\n",ans);
	}
}