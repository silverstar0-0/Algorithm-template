#include<bits/stdc++.h>
using namespace std;
const int inf=1e9+10;
const int N=1e5+10;
int M;
struct SegmentTree{
	int mx,add;
	#define mx(x) tree[x].mx
	#define add(x) tree[x].add
}tree[N<<2];
void Build(int n){
	M=1;
    for(;M<=n+1;M<<=1);
    // cout<<M<<endl;
}
void Change(int s,int t,int c)
{
    // cout<<M<<endl;
    for(s=s+M-1,t=t+M+1;t^s^1;t>>=1,s>>=1)
    {
        // cout<<mx(s^1)<<' '<<s<<' '<<t<<endl;
        if(s<M) mx(s)=max(mx(s<<1|1),mx(s<<1))+add(s);
        if(t<M) mx(t)=max(mx(t<<1|1),mx(t<<1))+add(t);
        if(~s&1) add(s^1)+=c,mx(s^1)+=c;
        if(t&1) add(t^1)+=c,mx(t^1)+=c;
    }
    for(;s;s>>=1,t>>=1)
    {
        if(s<M) mx(s)=max(mx(s<<1|1),mx(s<<1))+add(s),mx(t)=max(mx(t<<1|1),mx(t<<1))+add(t);
    }
}
int ask(int s,int t)
{
    int lans=-inf,rans=-inf;
    for(s=s+M-1,t=t+M+1;t^s^1;t>>=1,s>>=1)
    {
        // cout<<mx(s^1)<<' '<<s<<' '<<t<<endl;
        if(add(s)) lans+=add(s);
        if(add(t)) rans+=add(t);
        if(~s&1) lans=max(lans,mx(s^1));
        if(t&1) rans=max(rans,mx(t^1));
    }
    for(;s;s>>=1,t>>=1)
    {
        if(add(s)) lans+=add(s);
        if(add(t)) rans+=add(t);
    }
    return max(lans,rans);
}
int main()
{
	
}
