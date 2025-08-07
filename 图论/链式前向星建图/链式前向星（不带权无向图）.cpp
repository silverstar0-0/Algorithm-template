#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5; 
int n,m,point[maxn],nextx[2*maxn],to[2*maxn],cnt=1;
void create(void){
	int from,togo;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>from>>togo;
		nextx[cnt]=point[from];
		nextx[cnt+1]=point[togo];
		point[from]=cnt;
		point[togo]=cnt+1;
		to[cnt]=togo;
		to[cnt+1]=from;
		cnt+=2;
	}
}
//n为节点数量，m为边数量
//本程序适用于不带权无向图的建图
