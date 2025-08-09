#include<bits/stdc++.h>
#define fp(i,l,r) for(register int i=(l);i<=(r);i++)
#define fd(i,r,l) for(register int i=(r);i>=(l);i--)
#define int long long
typedef long long LL;
typedef long double LD;
using namespace std;//你在看我的代码对吧 
const int inf=1e18;
const LL N=1000100;
int M;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
LL T,n,w,h,C[N];
struct Segment{
	LL l,r,h;
	LL val;
	bool operator <(const Segment &a)const{
		return (h!=a.h)?h<a.h:val>a.val;
	}
}Seg[N<<2];
struct SegmentTree{
	LL mx,add;
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
signed main(){
    scanf("%lld",&T);
	while(T--){
        scanf("%lld%lld%lld",&n,&w,&h);
		for(LL i=1;i<=n;i++){
			LL x,y,l;
			scanf("%lld%lld%lld",&x,&y,&l);
			C[(i<<1)-1]=y;
			C[i<<1]=y+h-1;
			Seg[(i<<1)-1]=(Segment){y,y+h-1,x,l};
			Seg[i<<1]=(Segment){y,y+h-1,x+w-1,-l};
		}
		n<<=1;
		sort(C+1,C+n+1);
		sort(Seg+1,Seg+n+1);
		LL cnt=unique(C+1,C+n+1)-C-1;
		for(LL i=1;i<=n;i++){
            LL pos1=lower_bound(C+1,C+cnt+1,Seg[i].l)-C;
			LL pos2=lower_bound(C+1,C+cnt+1,Seg[i].r)-C;
			Seg[i].l=pos1;
			Seg[i].r=pos2;
		}
		Build(cnt);
        // cout<<1<<endl;
        // cout<<cnt<<endl;
		LL ans=0;
		for(LL i=1;i<=n;i++){
            // cout<<tree[1].mx<<' '<<Seg[i].val<<endl;
			Change(Seg[i].l,Seg[i].r,Seg[i].val);
			ans=max(ans,mx(1));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
