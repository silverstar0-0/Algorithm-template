#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const double P=acos(-1);
const int maxn=1e7+10;
inline int read()
{
	int x=0,f=1;
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
struct com
{
    double x,y;
    com (double xx=0,double yy=0){x=xx,y=yy;}
};
com a[maxn],b[maxn];
com operator + (com a,com b){ return com(a.x+b.x , a.y+b.y);}
com operator - (com a,com b){ return com(a.x-b.x , a.y-b.y);}
com operator * (com a,com b){ return com(a.x*b.x-a.y*b.y , a.x*b.y+a.y*b.x);}
int r[maxn];
int limit=1,l;
inline void fft(com *A,int j)
{
	for(int i=0;i<limit;i++) if(i<r[i]) swap(A[i],A[r[i]]);
	for(int mid=1;mid<limit;mid<<=1)
	{
		com W(cos(P/mid),j*sin(P/mid));
		for(int R=mid<<1,l=0;l<limit;l+=R)
		{
			com w(1,0);
			for(int k=0;k<mid;k++,w=w*W)
			{
				com x=A[k+l];com y=w*A[k+l+mid];
				A[l+k]=x+y;
				A[l+mid+k]=x-y;
			}
		}
	}
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<=n;i++) a[i].x=read();
	for(int i=0;i<=m;i++) b[i].x=read();
	for(l=0;limit<=n+m;limit=limit<<1,l++);
	for(int i=0;i<limit;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fft(a,1);
	fft(b,1);
	for(int i=0;i<limit;i++) a[i]=a[i]*b[i];
	fft(a,-1);
	for(int i=0;i<=n+m;i++)
	{
		printf("%d ",(int)(a[i].x/limit+0.5));
	}
}
