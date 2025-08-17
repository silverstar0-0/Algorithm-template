#include<bits/stdc++.h>
using namespace std;
const int M=6e6,N=300000; 
int n,m,s,t;
struct stu
{
	int v,next;
	long long val;
}e[M];
int head[N],cnt=1,dep[N];
inline void add(int u,int v,long long w)
{
	e[++cnt].next=head[u];
	e[cnt].v=v;
	e[cnt].val=w;
	head[u]=cnt;
}
inline int bfs()
{
	queue<int> q;
	for(int i=1;i<=n;i++)
	{
		dep[i]=0;
	}
	q.push(s);
	dep[s]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].next)
		{
			int v=e[i].v;
			if(dep[v]==0&&e[i].val>0)
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	if(dep[t]!=0) return 1;
	else return 0;
}
inline int dfs(int u,long long in)
{
	long long out=0;
	if(t==u) return in;
	for(int i=head[u];i&&in;i=e[i].next)
	{
		int v=e[i].v;
		if(e[i].val==0||dep[v]!=dep[u]+1) continue;
		long long k=dfs(v,min(in,e[i].val));
		out=out+k;
		in=in-k;
		e[i].val-=k;
		e[i^1].val+=k;
	}
	if(out==0) dep[u]=0;
	return out;
}
int main()
{
	memset(head,0,sizeof(head));
	scanf("%d %d %d %d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		add(u,v,w);    
		add(v,u,0);
	}
	
	long long ans=0;
	while(bfs())
	{
		ans+=dfs(s,1234567890);
	}
	cout<<ans;
 } 
 
