#include<bits/stdc++.h>
using namespace std;
int n;
const int ma=103;
struct tree
{
    int v,next,u;
}e[10030],ed[10030];
int su=0,hh=0,head[ma],cnt=0,dfn[ma],low[ma],sd[ma],t=0,sta[ma],vis[ma],h[ma],in[ma],out[ma];
inline void add(int u,int v)
{
    e[++cnt].v=v;
    e[cnt].u=u;
    e[cnt].next=head[u];
    head[u]=cnt;
}
inline void tarjan(int x)
{
    low[x]=dfn[x]=++t;
    sta[++hh]=x;vis[x]=1;
    for(int i=head[x];i;i=e[i].next)
    {
        int v=e[i].v;
        if(!dfn[v])
        {
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(vis[v])
        {
            low[x]=min(low[x],low[v]);
        }
    }
    if(dfn[x]==low[x])
    {
        int y;
        while(y=sta[hh--])
        {
            sd[y]=x;
            vis[y]=0;
            if(x==y) break;
        }
    }
}
int main()
{
    int v;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        while(1)
        {
            scanf("%d",&v);
            if(v==0) break;
            add(i,v);
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i]) tarjan(i);
    }
    for(int i=1;i<=cnt;i++)
    {
        int x=sd[e[i].u],y=sd[e[i].v];
        if(x!=y)
        {
            in[y]++;
            out[x]++;
        }
    }
    int a=0,b=0;
    int vv[ma];
    for(int i=1;i<=n;i++)
    {
        int x=sd[i];
        if(vv[x]==1) continue;
        vv[x]=1;
        if(in[x]==0) a++;
        if(out[x]==0) b++;
    }
    printf("%d\n%d",a,max(a,b));
}
