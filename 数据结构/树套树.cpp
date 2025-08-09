#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
const int Maxn=1e8+10;
int n,m;
int a[maxn];
inline long long read()
{
    long long x=0;
    int f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
struct node
{
    int l,r,val;
}t[Maxn],e[maxn*4];
struct query
{
    int op,l,r,k,pos;
}q[maxn];
int lpre,lnxt,pre[maxn],nxt[maxn];
int tots=0,rt[maxn];
int len=0;
long long slen[maxn];
inline void pushup(int now)
{
    t[now].val=t[t[now].l].val+t[t[now].r].val;
}
inline void add_tree(int &now,int l,int r,int k,int v)
{
    if(!now) now=++tots;
    if(l==r)
    {
        t[now].val+=v;
        return ;
    }
    int mid=(l+r)>>1;
    if(mid>=k) add_tree(t[now].l,l,mid,k,v);
    else add_tree(t[now].r,mid+1,r,k,v);
    pushup(now);
}
inline void build(int now,int l,int r)
{
    if(l==r)
    {
        return ;
    }
    int mid=(l+r)>>1;
    e[now].l=now<<1;
    e[now].r=now<<1|1;
    build(e[now].l,l,mid);
    build(e[now].r,mid+1,r);
}
inline int add(int now,int l,int r,int ll,int rr,int k)
{
    if(l==r)
    {
        add_tree(e[now].val,1,len,k,r-l+1);
        return 1;
    }
    int mid=(l+r)>>1;
    int ans=0;
    if(mid>=ll) ans+=add(e[now].l,l,mid,ll,rr,k);
    if(mid<rr) ans+=add(e[now].r,mid+1,r,ll,rr,k);
    add_tree(e[now].val,1,len,k,ans);
    return ans;
}
inline int query_num(int l,int r,int k)
{
    if(l==r)
    {
        return l;
    }
    int sum=0;
    int mid=(l+r)>>1;
    for(int i=1;i<=lpre;i++) sum+=t[t[pre[i]].l].val;
    if(k<=sum)
    {
        for(int i=1;i<=lpre;i++) pre[i]=t[pre[i]].l;
        return query_num(l,mid,k);
    }
    else
    {
        for(int i=1;i<=lpre;i++) pre[i]=t[pre[i]].r;
        return query_num(mid+1,r,k-sum);
    }
}
inline void find_num(int now,int l,int r,int ll,int rr)
{
    if(ll<=l&&r<=rr)
    {
        pre[++lpre]=e[now].val;
        return ;
    }
    int mid=(l+r)>>1;
    if(mid>=ll) find_num(e[now].l,l,mid,ll,rr);
    if(mid<rr) find_num(e[now].r,mid+1,r,ll,rr);
}
signed main()
{
    memset(e,0,sizeof(e));
    memset(t,0,sizeof(t));
    n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        q[i].op=read();
        q[i].l=read();q[i].r=read();q[i].k=read();
        slen[++len]=q[i].k;
    }
    sort(slen+1,slen+len+1,greater<long long>());
    len=unique(slen+1,slen+len+1)-slen-1;
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int op=q[i].op;
        if(op==1)
        {
            int k=lower_bound(slen+1,slen+len+1,q[i].k,greater<long long>())-slen;
            add(1,1,n,q[i].l,q[i].r,k);
        }
        else
        {
            lpre=0;
            find_num(1,1,n,q[i].l,q[i].r);
            cout<<slen[query_num(1,len,q[i].k)]<<endl;
        }
    }
}
