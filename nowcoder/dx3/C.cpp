// Problem: Capella
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/108300/C
// Memory Limit: 1024 MB
// Time Limit: 6000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
 
template<typename T>inline void re(T &x){
    T f=1;x=0;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=f;
}
 
template<typename T,typename ...OTH>
void re(T &x, OTH &...other){
    re(x);
    re(other...);
}
 
const int N=2e5+10;
int n,q,pre[N],nex[N],lst[26],siz;
char s[N];
set<int>pos[26];
 
struct SegTree{
    struct Node{
        int l,r,mx,pos;
        Node(){}
        Node(int _l,int _r,int _mx,int _pos):l(_l),r(_r),mx(_mx),pos(_pos){}
        Node operator+(const Node &b)const{
            Node c=b;
            c.l=l;
            if(c.mx<mx)
                c.mx=mx,c.pos=pos;
            return c;
        }
    }rt[N*4];
    int L,R;
    void build(int p,int l,int r)
    {
        if(l==r)
        {
            rt[p]=Node(l,r,l-pre[l],l);
            return;
        }
        int mid=l+r>>1;
        build(p<<1,l,mid);
        build(p<<1|1,mid+1,r);
        rt[p]=rt[p<<1]+rt[p<<1|1];
    }
    void change(int p,int x,int v)
    {
        if(rt[p].l==rt[p].r)
        {
            rt[p].mx=v;
            return;
        }
        int mid=rt[p].l+rt[p].r>>1;
        if(x<=mid) change(p<<1,x,v);
        else change(p<<1|1,x,v);
        rt[p]=rt[p<<1]+rt[p<<1|1];
    }
    void init(int _L,int _R)
    {
        L=_L,R=_R;
        build(1,_L,_R);
    }
    void change(int x)
    {
        change(1,x,x-pre[x]);
    }
    pair<int,int> result()
    {
        int r=rt[1].pos,l=pre[r];
        for(int i=0;i<26;++i)
            if(lst[i]&&n+1-lst[i]>r-l)
                r=n+1,l=lst[i];
        return {l+1,r-1};
    }
}ST;
 
int ans_odd(int l,int r)
{
    int len=r-l+1;
    if(len&1)
        return len;
    if(pre[r]>=l||nex[l]<=r)
        return len-1;
    int ll=l,rr=r,ans=0;
    while(ll<=r&&nex[ll]>r)
        ++ll;
    while(rr>=l&&pre[rr]<l)
        --rr;
    ans=max({1,r-ll-!(r-ll&1),rr-l-!(rr-l&1)});
    return ans;
}
 
int ans_even()
{
    auto [l,r]=ST.result();
    int len=r-l+1;
    if(len&1)
        return len;
    if(pre[r]>=l||nex[l]<=r)
        return len-1;
    for(int i=l-1;i;--i)
        if(nex[i]<=i+len-1||pre[i+len-1]>=i)
            return len-1;
    for(int i=r+1;i<=r;++i)
        if(pre[i]>=i-len+1||nex[i-len+1]<=i)
            return len-1;
    return max(ans_odd(1,len),ans_odd(n-len+1,n));
}
 
int main()
{
    re(n,q);
    scanf("%s",s+1);
    for(int i=1;i<=n;++i)
    {
        int c=s[i]-'a';
        pre[i]=lst[c];
        if(lst[c])
            nex[lst[c]]=i;
        else
            ++siz;
        lst[c]=i;
        pos[c].insert(i);
    }
    for(int i=0;i<26;++i)
        if(lst[i])
            nex[lst[i]]=n+1;
    ST.init(1,n);
    if(siz&1)
        printf("%d\n",ans_odd(1,n));
    else
        printf("%d\n",ans_even());
    while(q--)
    {
        int x;char c;
        scanf("%d %c",&x,&c);
        c-='a';
        int lc=s[x]-'a';
        if(lst[lc]==x)
        {
            lst[lc]=pre[x];
            if(!lst[lc])
                --siz;
        }
        if(pre[x])
            nex[pre[x]]=nex[x];
        if(nex[x]<=n)
        {
            pre[nex[x]]=pre[x];
            ST.change(nex[x]);
        }
        pos[lc].erase(x);
        auto it=pos[c].lower_bound(x);
        if(it==pos[c].end())
        {
            if(!lst[c])
            {
                lst[c]=x;
                ++siz;
                pre[x]=0;
                nex[x]=n+1;
            }
            else
            {
                nex[lst[c]]=x;
                pre[x]=lst[c];
                nex[x]=n+1;
                lst[c]=x;
            }
        }
        else
        {
            int nex_x=*it;
            if(pre[nex_x])
                nex[pre[nex_x]]=x;
            pre[x]=pre[nex_x];
            pre[nex_x]=x;
            ST.change(nex_x);
            nex[x]=nex_x;
        }
        ST.change(x);
        pos[c].insert(x);
        s[x]='a'+c;
        if(siz&1)
            printf("%d\n",ans_odd(1,n));
        else
            printf("%d\n",ans_even());
    }
    return 0;
}